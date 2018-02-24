void setBrightness(byte brightness) {
  maxBrightness = brightness;
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

char * STATE_SUCCESS = "success";
char * STATE_RUNNING = "running";
char * STATE_FAILED = "failed";

void switchToState(char * nextState) {
  if (strcmp(currentState, nextState) == 0) {
    Serial.print("Still the same state: ");
    Serial.print(currentState);
    Serial.print(" ");
    Serial.println(nextState);
    return;
  }

  Effect * nextEffect = NULL;

  if (strcmp(nextState, STATE_SUCCESS) == 0) {
    nextEffect = new SuccessEffect();
    currentState = STATE_SUCCESS;
  } else if (strcmp(nextState, STATE_RUNNING) == 0) {
    nextEffect = new RunningEffect();
    currentState = STATE_RUNNING;
  } else if (strcmp(nextState, STATE_FAILED) == 0) {
    nextEffect = new FailedEffect();
    currentState = STATE_FAILED;
  } else {
    Serial.print("Undefined nextState: ");
    Serial.println(nextState);
    return;
  }

  if (currentEffect == NULL) {
    currentEffect = nextEffect;
    return;
  }

  handleBrightness();
  transitToEffect(currentEffect, nextEffect, TRANSITION_TIME);
  delete currentEffect;
  currentEffect = nextEffect;
}

const char * ONLINE_KEY = "online";
void turnOnOff(char * action) {
  if (strcmp(action, ONLINE_KEY) == 0) {
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

  if (currentBrightness == 0.0) {
    return;
  }

  currentEffect->update();

  for(byte i=0; i<strip.numPixels(); i++) {
    RGB color = currentEffect->get(i);
    strip.setPixelColor(i, strip.Color(color.r, color.g, color.b));
  }
  strip.show();
}
