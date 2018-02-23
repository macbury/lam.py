#ifndef FailedEffect_H
#define FailedEffect_H
#include "Effect.h"

const int ringWidth = 6;
const RGB failedMinColor = { 255, 60, 30 };
const RGB failedMaxColor = { 226, 54, 2 };
const RGB emptyColor = { 0, 0, 0 };

typedef struct {
  byte level;
  byte power;
  float step;
  float alpha;
} FailLine;

class FailedEffect : public Effect {
  public:
    virtual void update() {
      _time += 0.01f;
      for (byte i = 0; i < size(); i++) {
        float alpha = 0.5 + sin(i + _time) * 0.5f;
        matrix[i] = lerpColor(alpha, failedMinColor, failedMaxColor);
      }
    }
  private:
    float _time;
};

#endif
