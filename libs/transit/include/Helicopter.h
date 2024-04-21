#ifndef Helicopter_H_
#define Helicopter_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "BeelineStrategy.h"
#include "math/vector3.h"


// Represents a Helicopter in a physical system.
// Helicopters move using euler integration based on a specified
// velocity and direction.
/**
 * @class Helicopter
 * @brief Represents a Helicopter in a physical system. Helicopters move using euler
 * integration based on a specified velocity and direction.
 */
class Helicopter : public IEntity {
 public:
  /**
   * @brief Helicopters are created with a name
   * @param obj JSON object containing the Helicopter's information
   */
  Helicopter(JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~Helicopter() {}


  /**
   * @brief Gets the next delivery in the scheduler
   */

  void update(double dt);

  /**
   * @brief Removing the copy constructor operator
   * so that Helicopters cannot be copied.
   */

  Helicopter(const Helicopter& Helicopter) = delete;

  /**
   * @brief Removing the assignment operator
   * so that Helicopters cannot be copied.
   */
  Helicopter& operator=(const Helicopter& Helicopter) = delete;

 private:
    IStrategy* toFinalDestination = nullptr;
};

#endif
