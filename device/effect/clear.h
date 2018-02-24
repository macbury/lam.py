#ifndef ClearEffect_H
#define ClearEffect_H
#include "Effect.h"

class ClearEffect : public Effect {
  public:
    virtual void update() {
      for (int i = 0; i < size(); i++) {
        matrix[i] = { 0, 0, 0 };
      }
    }
};

#endif
