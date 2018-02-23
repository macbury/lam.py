#ifndef FailedEffect_H
#define FailedEffect_H
#include "Effect.h"

const int ringWidth = 6;
const RGB failedMinColor = { 255, 60, 30 };
const RGB failedMaxColor = { 188, 47, 2 };

class FailedEffect : public Effect {
  public:
    virtual void update() {
      _time += 0.05f;
      for (int i = 0; i < size(); i++) {
        int level = i / ringWidth;
        float alpha = 0.5f + sin(level + _time) * 0.5f;

        matrix[i] = lerpColor(alpha, failedMinColor, failedMaxColor);
      }
    }
  private:
    float _time;
};

#endif
