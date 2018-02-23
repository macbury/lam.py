#ifndef SuccessEffect_H
#define SuccessEffect_H
#include "Effect.h"

typedef struct {
  byte index;
  byte power;
  float step;
  float alpha;
} Sparkle;

const byte numOfSparkles = 5;
const RGB successColor = { 30, 161, 255 };

class SuccessEffect : public Effect {
  public:
    virtual void update() {
      for (byte i = 0; i < size(); i++) {
        matrix[i] = successColor;
      }

      //updateSparkles();
    }
  private:
    Sparkle sparkles[numOfSparkles];

    void updateSparkles() {
      for (byte i = 0; i < numOfSparkles; i++) {
        Sparkle sparkle = sparkles[i];

        sparkle.alpha += sparkle.step;
        if (sparkle.alpha <= 0) {
          sparkle.alpha = 0;
          sparkle.power = 255;
          sparkle.index = random(0, size()-1);
          sparkle.step = random(0.001, 0.007);
        } else if (sparkle.alpha >= 1.0) {
          sparkle.alpha = 1.0;
          sparkle.step = -random(0.01, 0.07);
        }

        sparkles[i] = sparkle;

        RGB currentColor = matrix[sparkle.index];
        matrix[sparkle.index] = {
          lerp(sparkle.alpha, currentColor.r, sparkle.power),
          lerp(sparkle.alpha, currentColor.g, sparkle.power),
          lerp(sparkle.alpha, currentColor.b, sparkle.power)
        };
      }
    }
};

#endif
