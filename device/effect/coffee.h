#ifndef CoffeeEffect_H
#define CoffeeEffect_H
#include "Effect.h"

const RGB coffeeMinColor = { 0, 0, 0 };
const RGB coffeeMaxColor = { 255, 255, 0 };

class CoffeeEffect : public Effect {
  public:
    virtual void update() {
      _time += 0.1f;
      for (int i = 0; i < size(); i++) {
        int level = i / RING_WIDTH;
        float alpha = (0.5f + sin(level - _time) * 0.5f);

        matrix[i] = lerpColor(alpha, coffeeMinColor, coffeeMaxColor);
      }
    }
  private:
    float _time;
};

#endif
