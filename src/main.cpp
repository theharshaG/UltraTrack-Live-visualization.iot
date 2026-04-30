#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

// WiFi
const char* ssid = "your wifi";
const char* password = "your pass";

// Server your pc ip
const char* serverName = "http://10.53.110.123:5000/distance";

// Pins
#define TRIG 4
#define ECHO 2

void setup() {
  Serial.begin(115200);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  WiFi.begin(ssid, password);

  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
}

void loop() {

  // 🔹 Trigger pulse
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  // Read echo time
  long duration = pulseIn(ECHO, HIGH);

  // Convert to distance
  float distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  // Send to Flask
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    String json = "{\"distance\": " + String(distance) + "}";

    int code = http.POST(json);

    Serial.print("Response: ");
    Serial.println(code);

    http.end();
  }

  delay(3000);
}
