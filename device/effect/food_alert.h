#ifndef FoodAlertEffect_H
#define FoodAlertEffect_H
#include "Effect.h"

class FoodAlertEffect : public Effect {
  public:
    virtual void update() {
      _time += 1.0f;
      int step = 255 / size();
      for (int i = 0; i < size(); i++) {
        matrix[i] = wheel(i*step+_time);
      }
    }
  private:
    float _time;

    RGB wheel(byte wheelPos) {
      if(wheelPos < 85) {
        return { wheelPos * 3, 255 - wheelPos * 3, 0 };
      } else if(wheelPos < 170) {
        wheelPos -= 85;
        return { 255 - wheelPos * 3, 0, wheelPos * 3 };
      } else {
        wheelPos -= 170;
        return { 0, wheelPos * 3, 255 - wheelPos * 3 };
      }
    }
};

#endif
