#include "SimulationModel.h"

#include "DroneFactory.h"
#include "PackageFactory.h"
#include "RobotFactory.h"
#include "HumanFactory.h"
#include "HelicopterFactory.h"
#include "DuckFactory.h"
#include "StationFactory.h"
#include "BatteryDeco.h"

SimulationModel::SimulationModel(IController& controller)
    : controller(controller) {
  // Add factories for creating entities
  entityFactory.AddFactory(new DroneFactory());
  entityFactory.AddFactory(new PackageFactory());
  entityFactory.AddFactory(new RobotFactory());
  entityFactory.AddFactory(new HumanFactory());
  entityFactory.AddFactory(new HelicopterFactory());
  entityFactory.AddFactory(new DuckFactory());
  entityFactory.AddFactory(new StationFactory());
}

SimulationModel::~SimulationModel() {
  // Delete dynamically allocated entities
  for (auto& [id, entity] : entities) {
    delete entity;
  }
  delete graph;
}

IEntity* SimulationModel::createEntity(JsonObject& entity) {
  // Extract entity information from JSON object
  std::string name = entity["name"];
  JsonArray position = entity["position"];
  std::cout << name << ": " << position << std::endl;

  // Create a new entity using the factory
  IEntity* myNewEntity = nullptr;
  if (myNewEntity = entityFactory.CreateEntity(entity)) {
    // Link the entity to the model and add it to the controller
    myNewEntity->linkModel(this);
    controller.addEntity(*myNewEntity);
    entities[myNewEntity->getId()] = myNewEntity;

    // If the entity is a station, add it to the stations vector
    std::string type = entity["type"];
    if (type.compare("station") == 0) {
      stations.push_back(myNewEntity);
    }
  }

  return myNewEntity;
}

void SimulationModel::removeEntity(int id) {
  // Add the ID of the entity to the set of removed entities
  removed.insert(id);
}

void SimulationModel::scheduleTrip(JsonObject& details) {
  // Extract trip details from JSON object
  std::string name = details["name"];
  JsonArray start = details["start"];
  JsonArray end = details["end"];
  std::cout << name << ": " << start << " --> " << end << std::endl;

  // Find the receiver (robot) and package entities based on their names
  Robot* receiver = nullptr;
  for (auto& [id, entity] : entities) {
    if (name == entity->getName()) {
      if (Robot* r = dynamic_cast<Robot*>(entity)) {
        if  (r->requestedDelivery) {
          receiver = r;
          break;
        }
      }
    }
  }

  Package* package = nullptr;
  for (auto& [id, entity] : entities) {
    if (name + "_package" == entity->getName()) {
      if (Package* p = dynamic_cast<Package*>(entity)) {
        if  (p->requiresDelivery) {
          package = p;
          break;
        }
      }
    }
  }

  // If both receiver and package are found, initiate the delivery
  if (receiver && package) {
    package->initDelivery(receiver);
    std::string strategyName = details["search"];
    package->setStrategyName(strategyName);
    scheduledDeliveries.push_back(package);
    controller.sendEventToView("DeliveryScheduled", details);
  }
}

const routing::IGraph* SimulationModel::getGraph() {
  return graph;
}

void SimulationModel::update(double dt) {
  // Update all entities and notify the controller
  for (auto& [id, entity] : entities) {
    entity->update(dt);
    controller.updateEntity(*entity);
  }

  // Remove entities that have been marked for removal
  for (int id : removed) {
    removeFromSim(id);
  }
  removed.clear();
}

void SimulationModel::stop(void) {
  // Stop the controller
  controller.stop();
}

void SimulationModel::subscribe(void){
  // Subscribe to entities with BatteryDeco decoration
  for (auto& [id, entity] : entities) {
    if (BatteryDeco* battery = dynamic_cast<BatteryDeco*>(entity)) {
        battery->Attach(this);
      }
  }
}

void SimulationModel::unsubscribe(void){
  // Unsubscribe from entities with BatteryDeco decoration
  for (auto& [id, entity] : entities) {
    if (BatteryDeco* battery = dynamic_cast<BatteryDeco*>(entity)) {
        battery->Detach(this);
      }
  }
}

void SimulationModel::removeFromSim(int id) {
  // Remove an entity from the simulation
  IEntity* entity = entities[id];
  if (entity) {
    // Remove from scheduled deliveries if applicable
    for (auto i = scheduledDeliveries.begin();
      i != scheduledDeliveries.end(); ++i) {
      if (*i == entity) {
        scheduledDeliveries.erase(i);
        break;
      }
    }
    // Remove from controller and entities map, then delete the entity
    controller.removeEntity(*entity);
    entities.erase(id);
    delete entity;
  }
}

void SimulationModel::updateMsg(const std::string &msg){
  // Update message and send notification to the view
  JsonObject info;
  info["message"] = msg;
  controller.sendEventToView("Notify", info);
}

