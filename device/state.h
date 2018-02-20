String * currentState = "loading";
void switchToState(String * state) {
  if (state == "success") {
    Serial.println("Color to success");
  } else if (state == "running") {
    Serial.println("Color for runnign");
  } else if (state == "failed") {
    Serial.println("Color for failed");
  }
}

void turnOnOff(String * action) {
  if (action == "online") {
    Serial.println("Turn on lamp");
  } else {
    Serial.println("Turn off lamp");
  }
}
