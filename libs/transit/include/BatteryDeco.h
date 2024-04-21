#ifndef BATTERY_DECO_H_
#define BATTERY_DECO_H_



#include "Drone.h"
// #include "Package.h"

#include "math/vector3.h"
#include "util/json.h"
#include <vector>
#include "IStrategy.h"
#include "BeelineStrategy.h"


/**
 * @class BatteryDeco
 * @brief Decorator class to add battery feature to drones.
 */
class BatteryDeco : public IEntity{
 public:
    /**
     * @brief Constructor that takes an Drone pointer to decorate.
     */
    BatteryDeco(Drone* drone);
    /**
     * @brief Destructor for BatteryDeco.
     */
    ~BatteryDeco();


   /**
   * @brief Get the battery of drone.
   * @return The batter power
   */
   float getBattery() const { return batteryLevel; }


   /**
     * @brief Overrides the update function to handle battery-related logic.
     * @param battery_ sets the battery.
     */

   void setBattery(float batteryLevel_) { batteryLevel= batteryLevel_; }

    /**
     * @brief Overrides the update function to handle battery-related logic.
     * @param dt Delta time.
     */
    void update(double dt);

    /**
     * @brief  gets the Id of th entity
     * @return the ID of the entity 
     */


    int getId() const{return drone->getId();}

    /**
     * @brief Gets the position of the entity.
     * @return The position of the entity.
     */
    Vector3 getPosition() const{return drone->getPosition();}

    /**
     * @brief Gets the direction of the entity.
     * @return The direction of the entity.
     */
    Vector3 getDirection() const{ return drone->getDirection();}

    /**
     * @brief Gets the details of the entity.
     * @return The details of the entity.
     */
    const JsonObject& getDetails() const {return drone->getDetails();}

    /**
     * @brief Gets the color of the entity
     * @return The color of the entity
     */
    std::string getColor() const{return drone->getColor();}

    /**
     * @brief Gets the name of the entity
     * @return The name of the entity
     */
    std::string getName() const{return drone->getName();}

    /**
     * @brief Gets the speed of the entity.
     * @return The speed of the entity.
     */
    double getSpeed() const{return drone->getSpeed();}


    /**
     * @brief Calls the getNextDelivery function of the drone
     */

    void getNextDelivery(){drone->getNextDelivery();}

    /**
   * @brief Set the battery power of drone
   * @param battery The Amount of battery power going to be set
   */

    void setBatteryLevel(double batteryLevel_){batteryLevel = batteryLevel_;}

     /**
   * @brief charges the battery power of drone
   * @param dt speed of simulation/charge
   */

    void chargeBatteryLevel(double dt);


    /**
     * @brief Calls the linkModel function of the drone
     */

    void linkModel(SimulationModel* model){drone->linkModel(model);}


   /**
     * @brief checks if the drone will be able to make it with its batteryLevel to its next Destination 
     */

    void willreachDest();


   /**
     * @brief Set the canReach variable.
     * @param num Value to set canReach to.
     */


    void setcanReach(int num){canReach=num;}

    /**
     * @brief Find the nearest station to the drone.
     * @return The position of the nearest station.
     */

    Vector3 NearestStation();

    /**
     * @brief Get the toPackage strategy of the drone.
     * @return Pointer to the toPackage strategy.
     */

    IStrategy* getToPackageStrat(){return drone->getToPackageStrat();}

    /**
     * @brief Get the finalPackage strategy of the drone.
     * @return Pointer to the finalPackage strategy.
     */

    IStrategy* getFinalPackageStrat(){return drone->getFinalPackageStrat();}



    /**
     * @brief Get the package associated with the drone.
     * @return Pointer to the Package object.
     */

    Package* getPackage(){return drone->getPackage();}

    /**
     * @brief Set the toFinalDest strategy of the drone.
     * @param strat Pointer to the new strategy.
     */

    void setToFinalDest(IStrategy* strat){ 
      // delete drone->getFinalPackageStrat();
      drone->setToFinalDest(strat);
      }

      /**
     * @brief Set the toStation strategy of the drone.
     * @param strat Pointer to the new strategy.
     */

    void setToStation(IStrategy* strat){drone->setToStation(strat);}

    /**
     * @brief Get the toStation strategy of the drone.
     * @return Pointer to the toStation strategy.
     */

    IStrategy* getToStation(){return drone->getToStation();}

    /**
     * @brief Delete the toStation strategy of the drone.
     */

    // void deletetoStation(){drone->deletetoStation();}

    /**
     * @brief Notifies the observers of the drone.
     * 
     * @param msg The message to notify the observers with
     */
    void Notify(const std::string& msg) {drone->Notify(msg);}

    /**
     * @brief Attach an observer to BatteryDeco
     * 
     * @param observer The observer to attach
     */
    void Attach(IObserver* observer) {drone->Attach(observer);}

    /**
     * @brief Detach an observer from BatteryDeco
     * 
     * @param observer The observer to detach
     */
    void Detach(IObserver* observer) {drone->Detach(observer);}
    

 private:
    Drone* drone;           //Pointer to the decorated Drone object
    double batteryLevel;    //Current battery level 
    bool isCharging;        //indicates whether the drone is currently charging.
    int canReach = 0;       //indicates whether the drone can reach its next destination.
};

#endif
