#include "Duck.h"

#include <cmath>
#include <limits>

#include "SimulationModel.h"
#include "SpinDecorator.h"

Duck::Duck(JsonObject& obj) : IEntity(obj) {
  Vector3 dest;
  dest.x = (std::rand() % 2900) - 1400;
  dest.y = (std::rand() % 600);
  dest.z = (std::rand() % 1600) - 800;
  if (dest.y <= 240) {
    dest.y = 240;
    toFinalDestination = new SpinDecorator(
        new BfsStrategy(this->position, dest, model->getGraph()));
  } else {
    toFinalDestination = (new BeelineStrategy(this->position, dest));
  }
}

void Duck::update(double dt) {
  if (toFinalDestination == nullptr) {
    Vector3 dest;
    dest.x = (std::rand() % 2900) - 1400;
    dest.y = (std::rand() % 600);
    dest.z = (std::rand() % 1600) - 800;
    if (dest.y <= 240) {
      dest.y = 240;
      toFinalDestination =

          new SpinDecorator(
              new BfsStrategy(this->position, dest, model->getGraph()));
    } else {
      toFinalDestination = (new BeelineStrategy(this->position, dest));
    }
  }
  if (toFinalDestination) {
    toFinalDestination->move(this, dt);
    if (toFinalDestination->isCompleted()) {
      delete toFinalDestination;
      toFinalDestination = nullptr;
    }
  }
}