#include "BeelineStrategy.h"

BeelineStrategy::BeelineStrategy(Vector3 pos, Vector3 des): PathStrategy({
    {
      static_cast<float>(pos[0]),
      static_cast<float>(pos[1]),
      static_cast<float>(pos[2])
    },
    {
      static_cast<float>(des[0]),
      static_cast<float>(des[1]),
      static_cast<float>(des[2])
    }
  }) {}
