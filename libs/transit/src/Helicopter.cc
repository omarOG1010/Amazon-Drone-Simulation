#include "Helicopter.h"

Helicopter::Helicopter(JsonObject& obj) : IEntity(obj) {
    Vector3 dest;
    dest.x = (std::rand() % 2900) - 1400;
    dest.y = (std::rand() % 360) + 240;
    dest.z = (std::rand() % 1600) - 800;
    toFinalDestination = new BeelineStrategy(
          this->getPosition(),
          dest);
}


void Helicopter::update(double dt) {
    if (toFinalDestination == nullptr) {
    Vector3 dest;
    dest.x = (std::rand() % 2900) - 1400;
    dest.y = (std::rand() % 360) + 240;
    dest.z = (std::rand() % 1600) - 800;
    toFinalDestination = new BeelineStrategy(
          this->getPosition(),
          dest);
    }
    if (toFinalDestination) {
    toFinalDestination->move(this, dt);
        if (toFinalDestination->isCompleted()) {
            delete toFinalDestination;
            toFinalDestination = nullptr;
        }
    }
}
