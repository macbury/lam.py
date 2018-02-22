#ifndef FailedEffect_H
#define FailedEffect_H
#include "Effect.h"

class FailedEffect : public Effect {
  public:
    virtual void update() {
      for (byte i = 0; i < size(); i++) {
        matrix[i] = { 255, 60, 30 };
      }
    }
};

#endif
