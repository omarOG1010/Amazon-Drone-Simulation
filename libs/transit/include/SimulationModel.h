#ifndef SIMULATION_MODEL_H_
#define SIMULATION_MODEL_H_

#include "CompositeFactory.h"
#include "Drone.h"
#include "IController.h"
#include "IEntity.h"
#include "Robot.h"
#include "IObserver.h"
#include "graph.h"
#include <deque>
#include <map>
#include <set>


//--------------------  Model ----------------------------

/// Simulation Model handling the transit simulation.  The model can communicate
/// with the controller.
/**
 * @brief Class SimulationModel handling the transit simulation. it can
 * communicate with the controller
 **/
class SimulationModel : public IObserver{
 public:
  /**
   * @brief Default constructor that create the SimulationModel object
   **/
  SimulationModel(IController& controller);

  /**
   * @brief Destructor
   */
  ~SimulationModel();

  /**
   * @brief Set the Graph for the SimulationModel
   * @param graph Type IGraph* contain the new graph for SimulationModel
   **/
  void setGraph(const routing::IGraph* graph) { this->graph = graph; }

  /**
   * @brief Creates a new simulation entity
   * @param entity Type JsonObject contain the entity's reference to decide
   *which entity to create
   **/
  IEntity* createEntity(JsonObject& entity);

  /**
   * @brief Removes entity with given ID from the simulation
   * 
   * @param id of the entity to be removed
  */
  void removeEntity(int id);

  /**
   * @brief Schedule a trip for an object in the scene
   * @param detail Type JsonObject contain the entity's reference to schedule
   *the detail of the trip being scheduled
   **/
  void scheduleTrip(JsonObject& details);

  /**
   * @brief Update the simulation
   * @param dt Type double contain the time since update was last called.
   **/
  void update(double dt);

  /**
   * @brief Stops the simulation
   * @return Void
   **/
  void stop();

  /**
   * @brief Returns the graph of the map
   *
   * @returns IGraph* graph pointer
  */
  const routing::IGraph* getGraph();
  /**
   * @brief subscribes the simulation to notifications
   * @return Void
   **/
  void subscribe();

  /**
   * @brief unsubscribes the simulation to notifications
   * @return Void
   **/
  void unsubscribe(void);

  /**
   * @brief updates the message that is received from the subject and sends it to the
   * front end text box
   * 
   * @param message a dereferenced message string that 
   **/
  void updateMsg(const std::string &message);
  std::deque<Package*> scheduledDeliveries;
  std::vector<IEntity*> stations;


 protected:
  IController& controller;
  std::map<int, IEntity*> entities;
  std::set<int> removed;
  void removeFromSim(int id);
  const routing::IGraph* graph;
  CompositeFactory entityFactory;
};

#endif
