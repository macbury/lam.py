void printWifiInfo() {
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setupOTA() {
  Serial.println("Configuring ArduinoOTA");
  ArduinoOTA.setPort(OTA_PORT);
  ArduinoOTA.setHostname(OTA_HOST);
  ArduinoOTA.setPassword(OTA_PASSWORD);

  ArduinoOTA.onStart([]() {
    Serial.println("Starting");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });

  ArduinoOTA.begin();
}

void setupWifi() {
  delay(1000);
  Serial.println("----------");
  Serial.println("Connecting to: ");
  Serial.println(WIFI_NAME);
  WiFi.mode(WIFI_STA);

  while (WiFi.waitForConnectResult() != WL_CONNECTED){
    Serial.print(".");
    WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

    delay(500);
  }
  Serial.println("OK!");
  randomSeed(micros());
  printWifiInfo();
  setupOTA();
}

void ensureWifiConnection() {
  if (WiFi.status() != WL_CONNECTED) {
    delay(1);
    Serial.print("WIFI Disconnected. Attempting reconnection.");
    setupWifi();
  }
}

bool ensureMqttConnection() {
  ensureWifiConnection();
  while (!client.connected()) {
    delay(1000);
    Serial.println("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "lam.py-";
    clientId += String(random(0xffff), HEX);
    Serial.print("Client id: ");
    Serial.println(clientId);
    if (client.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD)) {
      printWifiInfo();
      return true;
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }

  return false;
}

void onConnect() {
  Serial.print("Subscribing: ");
  Serial.println(MQTT_TOPIC_BUILD);
  client.subscribe(MQTT_TOPIC_BUILD);
  Serial.println(MQTT_TOPIC_PRESENCE);
  client.subscribe(MQTT_TOPIC_PRESENCE);
}
