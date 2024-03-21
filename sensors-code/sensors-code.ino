#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>
#include "config.h"

#define DHTPIN 4
#define DHTTYPE DHT11

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

const char* serverUrl = "http://192.168.129.7:8081/measurements";

const int ledPin = 2;
const int greenLedPin = 18;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  delay(100);

  pinMode(ledPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  dht.begin();

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(greenLedPin, HIGH);
    delay(100);
    digitalWrite(greenLedPin, LOW);
    delay(100);
  }

  Serial.println("");
  digitalWrite(greenLedPin, HIGH);
  Serial.println("Connexion WiFi établie");
  Serial.println("Adresse IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
      delay(2000);
      return;
    }

    HTTPClient http;

    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    String requestBody = "{\"sensorId\": 1, \"value\": \"{temp: " + String(temperature) + ", hum: " + String(humidity) + "}\"}";

    int httpResponseCode = http.POST(requestBody);

    if (httpResponseCode > 0) {
      digitalWrite(ledPin, HIGH);
      delay(1000);
      digitalWrite(ledPin, LOW);
    }

    http.end();
  } else {
    Serial.println("Erreur de connexion WiFi");
  }

  delay(5000);
}
