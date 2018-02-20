int buttonAccumulator = 0;
boolean actionButtonPressed() {
  int actionButtonState = digitalRead(PIN_ACTION_BUTTON);

  if (actionButtonState == HIGH) {
    return false;
  }

  digitalWrite(PIN_STATUS_LED, HIGH);
  int buttonAccumulator = 0;
  while(actionButtonState == LOW) {
    delay(100);
    buttonAccumulator += 1;
    actionButtonState = digitalRead(PIN_ACTION_BUTTON);
  }
  digitalWrite(PIN_STATUS_LED, LOW);

  return buttonAccumulator >= 5;
}
