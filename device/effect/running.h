#ifndef RunningEffect_H
#define RunningEffect_H
#include "Effect.h"

RGB runningMainColor = { 255, 176, 30 };
RGB runningSecondColor = { 255, 255, 0 };

class RunningEffect : public Effect {
  public:
    virtual void update() {
      _time += 0.1f;
      for (byte i = 0; i < size(); i++) {
        float alpha = 0.5f + sin(i + _time) * 0.5f;
        matrix[i] = lerpColor(alpha, runningMainColor, runningSecondColor);
      }
    }
  private:
    float _time;
};

#endif
