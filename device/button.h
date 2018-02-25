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

void handleButton() {
  if (actionButtonPressed()) {
    Serial.println("Sending message");
    buttonLedBrightness = 0;
    client.publish(MQTT_TOPIC_BUTTON, "");

    ButtonEffect * buttonEffect = new ButtonEffect();
    runEffect(buttonEffect, currentEffect, 1000);
    delete buttonEffect;
  }
}
