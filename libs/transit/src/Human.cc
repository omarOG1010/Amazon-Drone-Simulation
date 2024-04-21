#include "Human.h"
#include <cmath>
#include <limits>
#include "AstarStrategy.h"
#include "SimulationModel.h"

Human::Human(JsonObject& obj) : IEntity(obj) {
    // Vector3 dest;
    // dest.x = (std::rand() % 2900) - 1400;
    // dest.y = 0;
    // dest.z = (std::rand() % 1600) - 800;
    // toFinalDestination = 
    // new AstarStrategy(this->position, dest, model->getGraph());
    }

void Human::setFinalDestination() {
    Vector3 dest;
    dest.x = (std::rand() % 2900) - 1400;
    dest.y = 240;
    dest.z = (std::rand() % 1600) -
    800;
    toFinalDestination =
    new AstarStrategy (this->position, dest, model->getGraph());
}

Human::~Human() {
    if (toFinalDestination) delete toFinalDestination;
}
void Human::update(double dt) {
    if (toFinalDestination) {
        toFinalDestination->move(this, dt);
        if (toFinalDestination->isCompleted()) {
            delete toFinalDestination;
            setFinalDestination();
    }
    } else {
        setFinalDestination();
    }
}
