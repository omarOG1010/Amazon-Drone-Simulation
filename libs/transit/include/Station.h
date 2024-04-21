#ifndef Station_H_
#define Station_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

class Drone;

// Represents a Station in a physical system.
// Stations move using euler integration based on a specified
// velocity and direction.
/**
 * @class Station
 * @brief Represents a Station in a physical system. Stations move using euler
 * integration based on a specified velocity and direction.
 */
class Station : public IEntity {
 public:
  /**
   * @brief Stations are created with a name
   * @param obj JSON object containing the Station's information
   */
  Station(JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~Station();




//   /**
//    * @brief Updates the Station's position not really station doesn't move
//    * @param dt Delta time
//    */
  void update(double dt);



};

#endif
