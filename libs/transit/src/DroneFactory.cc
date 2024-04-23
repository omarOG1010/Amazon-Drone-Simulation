IEntity* DroneFactory::CreateEntity(JsonObject& entity) {
  // Get the type of the entity from the JSON object
  std::string type = entity["type"];
  // Check if the type is "drone"
  if (type.compare("drone") == 0) {
    // Print message indicating that a drone is created
    std::cout << "Drone Created" << std::endl;
    // Create a new Drone object with the provided entity details
    Drone* Dronefr = new Drone(entity);
    // Create a BatteryDeco decorator for the Drone
    BatteryDeco* battery = new BatteryDeco(Dronefr);
    // Return the decorated Drone entity
    return battery;
  }
  // Return nullptr if the entity type is not "drone"
  return nullptr;
}
