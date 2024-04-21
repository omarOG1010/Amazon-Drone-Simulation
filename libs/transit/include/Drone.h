#ifndef DRONE_H_
#define DRONE_H_

#include <vector>

#include "IEntity.h"
#include "ISubject.h"
#include "IStrategy.h"
#include "math/vector3.h"


class Package;

// Represents a drone in a physical system.
// Drones move using euler integration based on a specified
// velocity and direction.
/**
 * @class Drone
 * @brief Represents a drone in a physical system. Drones move using euler
 * integration based on a specified velocity and direction.
 */
class Drone : public IEntity, public ISubject {
 public:
  /**
   * @brief Drones are created with a name
   * @param obj JSON object containing the drone's information
   */
  Drone(JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~Drone();


  /**
   * @brief Gets the next delivery in the scheduler
   */
  void getNextDelivery();

  /**
   * @brief Updates the drone's position
   * @param dt Delta time
   */
  void update(double dt);

  /**
   * @brief Removing the copy constructor operator
   * so that drones cannot be copied.
   */
  Drone(const Drone& drone) = delete;

  /**
   * @brief Removing the assignment operator
   * so that drones cannot be copied.
   */
  Drone& operator=(const Drone& drone) = delete;

  /**
   * @brief Notifies all observers of the drone
   */
  void Notify(const std::string& msg);

  /**
     * @brief Attaches an observer to the entity
     * 
     * @param observer The observer to attach
    */
  void Attach(IObserver* observer);

  /**
   * @brief Detach an observer from the entity
   * 
   * @param observer The observer to detach
  */
  void Detach(IObserver* observer);

  /**
   * @brief Get the drone availability.
   * @return The drone availability.
   */
  bool GetAvailability() const { return available; }

  /**
   * @brief Get the drone Package.
   * @return toPackage strat.
   */

  // Package* getPackage()const{return package;}

  // Vector3 getPackagePos(){ return package->getPosition();}

  IStrategy* getToPackageStrat(){return toPackage;}

  IStrategy* getFinalPackageStrat(){return toFinalDestination;}

  Package* getPackage(){return package;}

  // std::vector<IEntity*> getStations();


  void setToFinalDest(IStrategy* strat){
    delete toFinalDestination;
    toFinalDestination = strat; }

  void setToStation(IStrategy* strat){ toStation = strat;}

  IStrategy* getToStation(){return toStation;}


 private:
  bool available = false;
  bool pickedUp = false;
  Package* package = nullptr;
  IStrategy* toPackage = nullptr;
  IStrategy* toFinalDestination = nullptr;
  std::vector<bool> droneNotis = {false, false, false, false, false};
  IStrategy* toStation = nullptr;


};

#endif
