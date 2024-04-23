#include "BatteryDeco.h"

#include "Package.h"
#include "SimulationModel.h"


BatteryDeco::BatteryDeco(Drone* drone_) {
    drone = drone_;
    batteryLevel = 85;
    isCharging = false;
}

BatteryDeco::~BatteryDeco() {}

void BatteryDeco::chargeBatteryLevel(double dt){
  if(batteryLevel < 85 ){
      double newBattery = batteryLevel + dt;
      if (newBattery >= 85) {
        setBatteryLevel(85);
        isCharging = false;
    } else {
        setBatteryLevel(newBattery);
    }
  }else{
    isCharging = false;
  }
}

void BatteryDeco::willreachDest(){

  double dBetweenDroneNPackage = drone->getPosition().dist(drone->getPackage()->getPosition());

  double dBetweenPackageNDest = drone->getPackage()->getPosition().dist(drone->getPackage()->getDestination()); // extend IStratgey 

  double dBetweenDestNStation = drone->getPackage()->getDestination().dist(NearestStation());

  double totalDist = dBetweenDroneNPackage + dBetweenPackageNDest + dBetweenDestNStation;

  // IStrategy* strat = drone->getPackage()->getStrategyName();

  


  // std::cout << "Battery: "<< 100*batteryLevel<< std::endl;

  // std::cout << "total: "<< totalDist << std::endl;


  if(totalDist<90*batteryLevel && batteryLevel>30.0){
    setcanReach(1);
  
  }else{
    setcanReach(2);
  }
}

Vector3 BatteryDeco::NearestStation(){
  // Define a vector to store station positions
  std::vector<Vector3> stations;

  // Add station positions to the vector
  stations.push_back(Vector3(-800,280,230));
  stations.push_back(Vector3(777,275,406));
  stations.push_back(Vector3(75,282,-400));
  
  // Calculate the distance to the first station as the initial minimum distance
  double finalStation = stations.at(0).dist(drone->getPosition());
  // Initialize the index of the nearest station as the index of the first station
  int index = 0;
  // Iterate through the remaining stations to find the nearest one
  for(int i = 1; i < stations.size(); i++){
    // Calculate the distance between the drone and the current station
    Vector3 stationA = stations.at(i);
    Vector3 dronePos = drone->getPosition();
    double result = stationA.dist(dronePos);
    // Update the nearest station if a closer one is found
    if(result < finalStation){
      finalStation = result;
      index = i;
    }
  }

  // Return the position of the nearest station
  return stations.at(index);
}



bool local = true;
void BatteryDeco::update(double dt) {
    if (isCharging) {  // calls charge which sets is charge to false once fully charged
      chargeBatteryLevel(dt);

      // std::cout << "charging"<< batteryLevel << std::endl;
  
    }else{

      if(batteryLevel<0){ // default case if battery runs out
        if(local){
            this->Notify("Drone has Died");
            local = false;
          }
          // std::cout << "dead"<< batteryLevel << std::endl;
      }else{
        
        if (!drone->GetAvailability()){ // if drone is scheduled do all of this 
      
          if(canReach == 0){ // check if drone can reach package n destination n charging station 
            willreachDest(); // if it can it will equal 1 if not 2
          }

          if(canReach==1){ // delivers package 

            // std::cout << "Delivers Battery: "<< batteryLevel << std::endl;

            drone->update(dt);
            setBatteryLevel(batteryLevel - dt * drone->getSpeed()*0.01);

            if(drone->getFinalPackageStrat() == nullptr){
              setcanReach(0); // restarts the check 
            }

            // std::cout << "can num:" << canReach<< std::endl;

          }else{ //goes to charging station cant reach package ladadada etc 


            

            Vector3 closeStation = NearestStation(); // gets nearest station

            // IStrategy* toFinalDestination = new BeelineStrategy(drone->getPosition(),closeStation);

            if(!drone->getToStation()){ // if strat to station doesnt exist make one 
              drone->setToStation(new BeelineStrategy(drone->getPosition(),closeStation));
            }

            if(drone->getToStation()->isCompleted()){ // if drone at station start charging procces 
              isCharging = true;
            }

            willreachDest(); // check if drone can go to previously scheudled package and destination 
            

            drone->update(dt);
            setBatteryLevel(batteryLevel - dt * drone->getSpeed()*0.01);

            // if(drone->getToStation()->isCompleted()){
            //   isCharging = true;
            // }


            // std::cout << "Can't deliver:  "<< batteryLevel << std::endl;
          }

        }else{
          // std::cout << "nothing"<< batteryLevel << std::endl;

          drone->update(dt); // if nothing is scheudled schdule something 

        }
      }
    }
}
