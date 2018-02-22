String currentState = "";
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
  if (currentEffect != NULL) {
    delete currentEffect;
  }

  currentEffect = NULL;

  if (nextState == "success") {
    currentEffect = new SuccessEffect();
  } else if (nextState == "running") {
    currentEffect = new RunningEffect();
  } else if (nextState == "failed") {
    currentEffect = new FailedEffect();
  } else {
    Serial.print("Undefined nextState: ");
    Serial.println(nextState);
  }
}

void turnOnOff(char * action) {
  if (String(action) == "online") {
    Serial.println("Turn on lamp");
  } else {
    Serial.println("Turn off lamp");
  }
}
