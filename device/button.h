int buttonAccumulator = 0;
boolean actionButtonPressed() {
  int actionButtonState = digitalRead(PIN_ACTION_BUTTON);
  
  if (actionButtonState == HIGH) {
    return false;
  }

  analogWrite(PIN_STATUS_LED, 255);
  int buttonAccumulator = 0;
  while(actionButtonState == LOW) {
    delay(20);
    buttonAccumulator += 1;
    actionButtonState = digitalRead(PIN_ACTION_BUTTON);
  }
  analogWrite(PIN_STATUS_LED, 0);

  return buttonAccumulator >= 5;
}

int buttonLedBrightness = 0;
int buttonLedFadeAmount = 10;

void handleButton() {
  buttonLedBrightness += buttonLedFadeAmount;
  if (buttonLedBrightness < 0) buttonLedBrightness = 0;
  if (buttonLedBrightness > 1023) buttonLedBrightness = 1023;

  if (buttonLedBrightness == 0 || buttonLedBrightness == 1023) {
    buttonLedFadeAmount = -buttonLedFadeAmount;
  }
  analogWrite(PIN_STATUS_LED, buttonLedBrightness);

  if (actionButtonPressed()) {
    Serial.println("Sending message");
    buttonLedBrightness = 0;
    client.publish(MQTT_TOPIC_BUTTON, "");
  }
}
