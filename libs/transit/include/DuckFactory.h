#ifndef Duck_FACTORY_H_
#define Duck_FACTORY_H_

#include <vector>

#include "IEntityFactory.h"
#include "Duck.h"

/**
 *@brief Duck Factory to produce Ducks class.
 **/
class DuckFactory : public IEntityFactory {
 public:
  /**
   * @brief Destructor for DuckFactory class.
   **/
  virtual ~DuckFactory() {}

  /**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully, or a
   *nullpointer if creation failed.
   **/
  IEntity* CreateEntity(JsonObject& entity);
};

#endif
