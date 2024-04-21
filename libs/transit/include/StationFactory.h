#ifndef Station_FACTORY_H_
#define Station_FACTORY_H_

#include <vector>

#include "IEntityFactory.h"
#include "Station.h"

/**
 *@brief Station Factory to produce Station class.
 **/
class StationFactory : public IEntityFactory {
 public:
  /**
   * @brief Destructor for StationFactory class.
   **/
  virtual ~StationFactory() {}

  /**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully, or a
   *nullpointer if creation failed.
   **/
  IEntity* CreateEntity(JsonObject& entity);
};

#endif
