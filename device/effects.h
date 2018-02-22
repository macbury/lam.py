#include "effect/failed.h"
#include "effect/success.h"
#include "effect/running.h"

Effect * currentEffect;

void clearColor() {
  strip.setBrightness(0);
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, 0);
  }
  strip.show();
}

byte lerp(float progress, float fromValue, float toValue){
  return (int)(fromValue + (toValue - fromValue) * progress);
}
