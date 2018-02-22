Effect * currentEffect;
String currentState = "";
int maxBrightness = LIGHT_BRIGHTNESS;
int currentBrightness = 0;
bool teamOnline;

void setBrightness(byte brightness) {
  currentBrightness = maxBrightness = brightness;
  strip.setBrightness(currentBrightness);
  strip.show();
}

void handleBrightness() {
  if (teamOnline) {
    currentBrightness += 1;
  } else {
    currentBrightness -= 1;
  }

  if (currentBrightness < 0) {
    currentBrightness = 0;
  }

  if (currentBrightness > maxBrightness) {
    currentBrightness = maxBrightness;
  }

  strip.setBrightness(currentBrightness);
  strip.show();
}

void switchToState(char * rawState) {
  String nextState = String(rawState);

  if (nextState.equals(currentState)) {
    Serial.print("Still the same state: ");
    Serial.print(currentState);
    Serial.print(" ");
    Serial.println(nextState);
    return;
  }

  currentState = rawState;

  Effect * nextEffect;

  if (nextState == "success") {
    nextEffect = new SuccessEffect();
  } else if (nextState == "running") {
    nextEffect = new RunningEffect();
  } else if (nextState == "failed") {
    nextEffect = new FailedEffect();
  } else {
    Serial.print("Undefined nextState: ");
    Serial.println(nextState);
  }

  if (currentEffect == NULL || nextEffect == NULL) {
    currentEffect = nextEffect;
    return;
  }

  handleBrightness();
  float step = (TICK_DELAY/TRANSITION_TIME);
  for (float alpha = 0; alpha < 1.0; alpha+=step) {
    currentEffect->update();
    nextEffect->update();

    for(byte i=0; i<strip.numPixels(); i++) {
      RGB currentColor = currentEffect->get(i);
      RGB nextColor = nextEffect->get(i);

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
    delay(TICK_DELAY);
  }
  delete currentEffect;
  currentEffect = nextEffect;
}

void turnOnOff(char * action) {
  if (String(action) == "online") {
    teamOnline = true;
    Serial.println("Turn on lamp");
  } else {
    teamOnline = false;
    Serial.println("Turn off lamp");
  }
}

void handleLight() {
  if (currentEffect == NULL) {
    clearColor();
    return;
  }

  handleBrightness();
  currentEffect->update();

  for(byte i=0; i<strip.numPixels(); i++) {
    RGB color = currentEffect->get(i);
    strip.setPixelColor(i, strip.Color(color.r, color.g, color.b));
  }
  strip.show();
}
