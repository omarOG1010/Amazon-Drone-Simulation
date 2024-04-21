#define _USE_MATH_DEFINES
#include "Drone.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "DfsStrategy.h"
#include "BfsStrategy.h"
#include "DijkstraStrategy.h"
#include "JumpDecorator.h"
#include "SpinDecorator.h"

#include "Package.h"
#include "SimulationModel.h"

Drone::Drone(JsonObject& obj) : IEntity(obj) {
  available = true;
}

Drone::~Drone() {
  if (toPackage) delete toPackage;
  if (toFinalDestination) delete toFinalDestination;
  if (toStation) delete toStation;
}

void Drone::getNextDelivery() {
  if (model && model->scheduledDeliveries.size() > 0) {
    package = model->scheduledDeliveries.front();
    model->scheduledDeliveries.pop_front();

    if (package) {
      available = false;
      pickedUp = false;

      Vector3 packagePosition = package->getPosition();
      Vector3 finalDestination = package->getDestination();


      toPackage = new BeelineStrategy(position, packagePosition);

      std::string strat = package->getStrategyName();
      if (strat == "astar") {
        toFinalDestination =
          new JumpDecorator(
            new AstarStrategy(
              packagePosition,
              finalDestination,
              model->getGraph()));
      } else if (strat == "dfs") {
        toFinalDestination =
          new SpinDecorator(
            new JumpDecorator(
              new DfsStrategy(
                packagePosition,
                finalDestination,
                model->getGraph())));
      } else if (strat == "bfs") {
        toFinalDestination =
          new SpinDecorator(
            new SpinDecorator(
              new BfsStrategy(
                packagePosition,
                finalDestination,
                model->getGraph())));
      } else if (strat == "dijkstra") {
        toFinalDestination =
          new JumpDecorator(
            new SpinDecorator(
              new DijkstraStrategy(
                packagePosition,
                finalDestination,
                model->getGraph())));
      } else {
        toFinalDestination = new BeelineStrategy(
          packagePosition,
          finalDestination);
      }
    }
  }
}

void Drone::Notify(const std::string& msg) {
  for (int i = 0; i < observers.size(); i++) {
      observers[i]->updateMsg(msg);
  }
}

void Drone::Attach(IObserver* observer) {
    observers.push_back(observer);
}

void Drone::Detach(IObserver* observer) {
    for (int i = 0; i < observers.size(); i++) {
        if (observers[i] == observer) {
            observers.erase(observers.begin() + i);
        }
    }
}

void Drone::update(double dt) {
  if (available) {
    getNextDelivery();
  }
  if(toStation) {
    if(!(droneNotis[6])){
      droneNotis[6] = true;
      this->Notify(this->name + " is on the way to Charging Station.");
    }
    if(toStation->isCompleted()){
      delete toStation;
      toStation = nullptr;
      if (!(droneNotis[5])) {
        droneNotis[5] = true;
        this->Notify(this->name + " has arrived at Charging Station.");
      }
    }
    if(toStation) {
      toStation->move(this,dt);
    }
   } else if (toPackage) {
    toPackage->move(this, dt);
    if (!(droneNotis[0]) && !(droneNotis[1])) {
      droneNotis[0] = true;
      droneNotis[1] = true;
      this->Notify(this->name + " has accepted the delivery!");
      this->Notify(this->name + " is on the way to Package.");
    }
    if (toPackage->isCompleted()) {
      delete toPackage;
      toPackage = nullptr;
      pickedUp = true;
      if (!(droneNotis[2]) && !(droneNotis[3])) {
        droneNotis[2] = true;
        droneNotis[3] = true;
        this->Notify(this->name + " has picked up the package.");
        this->Notify(this->name + " is on the way to final destination.");
    }
    }
  } else if (toFinalDestination) {
    toFinalDestination->move(this, dt);

    if (package && pickedUp) {
      package->setPosition(position);
      package->setDirection(direction);
    }

    if (toFinalDestination->isCompleted()) {
      if (!(droneNotis[4])) {
        this->Notify(this->name + " has delivered the package.");
        droneNotis = {false, false, false, false, false, false, false};
      }
      delete toFinalDestination;
      toFinalDestination = nullptr;
      package->handOff();
      package = nullptr;
      available = true;
      pickedUp = false;
    }
  }
}
