#include "Robot.h"

Robot::Robot(JsonObject &obj) : IEntity(obj) {}

void Robot::update(double dt) {}

void Robot::receive(Package* p) {
  package = p;
}
