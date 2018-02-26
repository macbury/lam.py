
int buttonLedBrightness = 0;
int buttonLedFadeAmount = 20;

void updateButtonLed() {
  buttonLedBrightness += buttonLedFadeAmount;
  if (buttonLedBrightness < 0) buttonLedBrightness = 0;
  if (buttonLedBrightness > 1023) buttonLedBrightness = 1023;

  if (buttonLedBrightness == 0 || buttonLedBrightness == 1023) {
    buttonLedFadeAmount = -buttonLedFadeAmount;
  }
  analogWrite(PIN_STATUS_LED, buttonLedBrightness);
}

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

void transitToEffect(Effect * fromEffect, Effect * toEffect, float transitionTime) {
  float step = (TICK_DELAY/transitionTime);
  for (float alpha = 0; alpha <= 1.0; alpha+=step) {
    fromEffect->update();
    toEffect->update();

    for(byte i=0; i<strip.numPixels(); i++) {
      RGB currentColor = fromEffect->get(i);
      RGB nextColor = toEffect->get(i);

      strip.setPixelColor(
        i,
        strip.Color(
          lerp(alpha, currentColor.r, nextColor.r),
          lerp(alpha, currentColor.g, nextColor.g),
          lerp(alpha, currentColor.b, nextColor.b)
        )
      );
    }

    strip.show();
    yield();
    delay(TICK_DELAY);
  }
}
