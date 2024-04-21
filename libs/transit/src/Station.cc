#include "Station.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "BeelineStrategy.h"

#include "SimulationModel.h"

Station::Station(JsonObject& obj) : IEntity(obj) {
} 

Station::~Station() {
 
}


void Station::update(double dt) {}
