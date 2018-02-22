#ifndef SuccessEffect_H
#define SuccessEffect_H
#include "Effect.h"

class SuccessEffect : public Effect {
  public:
    virtual void update() {
      for (byte i = 0; i < size(); i++) {
        matrix[i] = { 30, 161, 255 };
      }
    }
};

#endif