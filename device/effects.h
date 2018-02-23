#include "effect/effect.h"

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

RGB lerpColor(float progress, RGB fromColor, RGB toColor) {
  return {
    lerp(progress, fromColor.r, toColor.r),
    lerp(progress, fromColor.g, toColor.g),
    lerp(progress, fromColor.b, toColor.b)
  };
}

#include "effect/failed.h"
#include "effect/success.h"
#include "effect/running.h"
