#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Attempt Wi-Fi connection to trigger network module initialization
  WiFi.mode(WIFI_STA);    // Set WiFi mode to Station
  WiFi.begin("TestSSID", "TestPassword");  // Use any dummy SSID/password
  delay(10000);  // Give time for Wi-Fi to initialize

  // Print the MAC address
  Serial.print("ESP32 MAC Address: ");
  Serial.println(WiFi.macAddress());
}

void loop() {
  // No operation here
}
