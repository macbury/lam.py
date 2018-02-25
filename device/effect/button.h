#ifndef ButtonEffect_H
#define ButtonEffect_H
#include "Effect.h"

const RGB buttonMinColor = { 0, 0, 0 };
const RGB buttonMaxColor = { 5, 255, 71 };

class ButtonEffect : public Effect {
  public:
    virtual void update() {
      _time += 0.1f;
      for (int i = 0; i < size(); i++) {
        int level = i / RING_WIDTH;
        float alpha = (0.5f + sin(level + _time) * 0.5f);

        matrix[i] = lerpColor(alpha, buttonMinColor, buttonMaxColor);
      }
    }
  private:
    float _time;
};

#endif
