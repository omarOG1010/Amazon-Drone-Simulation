#include "DroneFactory.h"

#include "BatteryDeco.h"

IEntity* DroneFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("drone") == 0) {
    std::cout << "Drone Created" << std::endl;

    Drone* Dronefr = new Drone(entity);

    BatteryDeco* battery = new BatteryDeco(Dronefr);

    return battery;

  }

  return nullptr;
}


