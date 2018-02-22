#ifndef SuccessEffect_H
#define SuccessEffect_H
#include "Effect.h"

class SuccessEffect : public Effect {
  public:
    virtual void update() {
      for (byte i = 0; i < size(); i++) {
        matrix[i] = { 0, 255, 0 };
      }
    }
};

#endif
