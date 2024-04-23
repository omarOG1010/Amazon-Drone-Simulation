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
  // If the drone is available, check for the next delivery
  if (available) {
    getNextDelivery();
  }
  
  // If moving towards the charging station
  if(toStation) {
    // Notify observers if not already notified about moving to the charging station
    if(!(droneNotis[6])){
      droneNotis[6] = true;
      this->Notify(this->name + " is on the way to Charging Station.");
    }
    
    // Check if the movement to the charging station is completed
    if(toStation->isCompleted()){
      delete toStation;
      toStation = nullptr;
      // Notify observers upon arrival at the charging station if not already notified
      if (!(droneNotis[5])) {
        droneNotis[5] = true;
        this->Notify(this->name + " has arrived at Charging Station.");
      }
    }
    
    // Move towards the charging station
    if(toStation) {
      toStation->move(this,dt);
    }
   } 
   // If moving towards the package
   else if (toPackage) {
    // Move towards the package
    toPackage->move(this, dt);
    
    // Notify observers upon accepting the delivery and moving towards the package if not already notified
    if (!(droneNotis[0]) && !(droneNotis[1])) {
      droneNotis[0] = true;
      droneNotis[1] = true;
      this->Notify(this->name + " has accepted the delivery!");
      this->Notify(this->name + " is on the way to Package.");
    }
    
    // Check if the movement to the package is completed
    if (toPackage->isCompleted()) {
      delete toPackage;
      toPackage = nullptr;
      pickedUp = true;
      // Notify observers upon picking up the package and moving towards the final destination if not already notified
      if (!(droneNotis[2]) && !(droneNotis[3])) {
        droneNotis[2] = true;
        droneNotis[3] = true;
        this->Notify(this->name + " has picked up the package.");
        this->Notify(this->name + " is on the way to final destination.");
    }
    }
  } 
  // If moving towards the final destination
  else if (toFinalDestination) {
    // Move towards the final destination
    toFinalDestination->move(this, dt);

    // If a package is picked up, update its position and direction
    if (package && pickedUp) {
      package->setPosition(position);
      package->setDirection(direction);
    }

    // Check if the movement to the final destination is completed
    if (toFinalDestination->isCompleted()) {
      // Notify observers upon delivering the package if not already notified
      if (!(droneNotis[4])) {
        this->Notify(this->name + " has delivered the package.");
        // Reset the notification flags
        droneNotis = {false, false, false, false, false, false, false};
      }
      delete toFinalDestination;
      toFinalDestination = nullptr;
      // Hand off the package and reset status
      package->handOff();
      package = nullptr;
      available = true;
      pickedUp = false;
    }
  }
}
