#include "DuckFactory.h"

IEntity* DuckFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("duck") == 0) {
    std::cout << "Duck Created" << std::endl;
    return new Duck(entity);
  }
  return nullptr;
}
