
each action generates effect

each effect is have array of colors
to update this array we use update function that runs every n time
every loop we apply all colors to led strip

Effect:
  colorMatrix;
  update()


currentEffect =
targetEffect = new Effect()

``` C
void interpolateBetweenEffects() {
  for(float alpha = 0.0f; alpha <= 1f; alpha+=0.01f) {
    currentEffect->update();
    targetEffect->update();

    for (size_t i = 0; i < pixcount; i++) {
      int prevColor = currentEffect->getColor(i);
      int targetColor = currentEffect->getColor(i);

      int finalColor = lerp(prevColor, targetColor, alpha);
      strip->setColor(finalColor);
    }
    strip->show();
    delay(33);
  }

  delete currentEffect;
  currentEffect = targetEffect;
}

void updateEffect() {
  if (turnedOff) {
    strip->setBrightness(0);
    return;
  } else {
    strip->setBrightness(targetBrightness);
  }

  if (effect == null) {
    return;
  }

  effect->update();
  for (size_t i = 0; i < pixcount; i++) {
    int color = effect->getColor(i);
    strip->setColor(color);
  }
  strip->show();
}
```
