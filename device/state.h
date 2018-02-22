char * currentState = "loading";
void switchToState(char * rawState) {
  String state = String(rawState);
  if (state == "success") {
    Serial.println("Color to success");
  } else if (state == "running") {
    Serial.println("Color for runnign");
  } else if (state == "failed") {
    Serial.println("Color for failed");
  } else {
    Serial.print("Undefined state: ");
    Serial.println(state);
  }
}

void turnOnOff(char * action) {
  if (String(action) == "online") {
    Serial.println("Turn on lamp");
  } else {
    Serial.println("Turn off lamp");
  }
}
