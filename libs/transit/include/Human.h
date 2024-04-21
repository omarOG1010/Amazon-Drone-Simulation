#ifndef DRONE_H_
#define DRONE_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"


// Represents a human in a physical system.

/**
 * @class Drone
 * @brief Represents a drone in a physical system. Drones move using euler
 * integration based on a specified velocity and direction.
 */
class Human: public IEntity {
 public:
  /**
   * @brief humans are created with a name
   * @param obj JSON object containing the human's information
   */
  Human(JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~Human();
  /**
   * @brief updates the position of the Human
   * @param dt Delta time
   */
  void update(double dt);

  void setFinalDestination();

 private:
    IStrategy* toFinalDestination = nullptr;
};
#endif
