#ifndef RunningEffect_H
#define RunningEffect_H
#include "Effect.h"

class RunningEffect : public Effect {
  public:
    virtual void update() {
      for (byte i = 0; i < size(); i++) {
        matrix[i] = { 255, 176, 30 };
      }
    }
};

#endif
