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

void handleLight() {
  if (currentEffect == NULL) {
    clearColor();
    return;
  }

  strip.setBrightness(100); // LOAD from somwhere
  currentEffect->update();

  for(byte i=0; i<strip.numPixels(); i++) {
    RGB color = currentEffect->get(i);
    strip.setPixelColor(i, strip.Color(color.r, color.g, color.b));
  }
  strip.show();
}
