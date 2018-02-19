#include <ArduinoHttpClient.h>
#include <ESP8266WiFi.h>
#include "credentials.h"

WiFiClient wifi;
HttpClient client = HttpClient(wifi, ENDPOINT_HOST, 80);

//https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/examples/WiFiClient/WiFiClient.ino

int accumulator = 0;
boolean actionButtonPressed() {
  int actionButtonState = digitalRead(PIN_ACTION_BUTTON);

  if (actionButtonState == HIGH) {
    return false;
  }

  digitalWrite(PIN_STATUS_LED, HIGH);
  int accumulator = 0;
  while(actionButtonState == LOW) {
    delay(100);
    accumulator += 1;
    actionButtonState = digitalRead(PIN_ACTION_BUTTON);
  }
  digitalWrite(PIN_STATUS_LED, LOW);

  return accumulator >= 5;
}

void setup() {
  pinMode(PIN_STATUS_LED, OUTPUT);
  pinMode(PIN_ACTION_BUTTON, INPUT);
  digitalWrite(PIN_STATUS_LED, LOW);

  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_NAME);

  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (actionButtonPressed()) {
    Serial.println("Pressed a button!");
  }

  Serial.println("Performing request");
  client.beginRequest();
  client.get("/");
  client.sendBasicAuth(ENDPOINT_USER, ENDPOINT_PASSWORD);
  client.endRequest();
  Serial.println("Ending request");

  Serial.println("available: ");
  Serial.println(client.available());
  while(client.available() > 0) {
    Serial.println("Left: ");
    Serial.println(client.available());
  }
}
