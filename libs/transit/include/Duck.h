#ifndef Duck_H_
#define Duck_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "BeelineStrategy.h"
#include "BfsStrategy.h"
#include "math/vector3.h"


// Represents a Duck in a physical system.
// Ducks move using euler integration based on a specified
// velocity and direction.
/**
 * @class Duck
 * @brief Represents a Duck in a physical system. Ducks move using euler
 * integration based on a specified velocity and direction.
 */
class Duck : public IEntity {
 public:
  /**
   * @brief Ducks are created with a name
   * @param obj JSON object containing the Duck's information
   */
  Duck(JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~Duck(){}


  /**
   * @brief Gets the next delivery in the scheduler
   */

  void update(double dt);

  /**
   * @brief Removing the copy constructor operator
   * so that Ducks cannot be copied.
   */
  Duck(const Duck& Duck) = delete;

  /**
   * @brief Removing the assignment operator
   * so that Ducks cannot be copied.
   */
  Duck& operator=(const Duck& Duck) = delete;

  private:
    IStrategy* toFinalDestination = nullptr;
};

#endif
