#include <SPI.h>
#include "DW1000Ranging.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define ANCHOR_ADD "82:17:5B:D5:A9:9A:E2:9C"

#define SPI_SCK 18
#define SPI_MISO 19
#define SPI_MOSI 23
#define DW_CS 4

// Wi-Fi credentials
const char* ssid = "ChairGuru";
const char* password = "123456789";

// Server configuration
const char* serverUrl = "http://192.168.4.2:5000/api/store-current-chair-poss";

// connection pins
const uint8_t PIN_RST = 27; // reset pin
const uint8_t PIN_IRQ = 34; // irq pin
const uint8_t PIN_SS = 4;   // spi select pin

void setupWiFi() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWi-Fi Connected.");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

// Function to send data to the server
void sendDataToServer(const String& jsonPayload) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    Serial.println("Sending data to server:");
    Serial.println(jsonPayload); // Debug payload

    int httpResponseCode = http.POST(jsonPayload);

    if (httpResponseCode > 0) {
        Serial.print("Server response code: ");
        Serial.println(httpResponseCode);
        Serial.println(http.getString()); // Print server response
    } else {
        Serial.print("Error sending data to server: ");
        Serial.println(httpResponseCode);
    }

    http.end(); // Close connection
}

void newRange() {
    DW1000Device* device = DW1000Ranging.getDistantDevice();
    if (device) {
        // Manually set a unique anchor ID
        String anchorId = "Anchor2"; // Change this to "Anchor2" for the second anchor

        String jsonPayload = "{\"links\":["; 
        jsonPayload += "{\"A\":\"" + anchorId + // Use manually set anchor ID
                       "\",\"R\":\"" + String(device->getRange(), 2) +
                       "\",\"dBm\":\"" + String(device->getRXPower(), 2) + "\"}";
        jsonPayload += "]}";

        sendDataToServer(jsonPayload);

        // Debug print
        Serial.print("from: ");
        Serial.print(anchorId); // Print manually set anchor ID
        Serial.print("\t Range: ");
        Serial.print(device->getRange());
        Serial.print(" m");
        Serial.print("\t RX power: ");
        Serial.println(device->getRXPower());
    } else {
        Serial.println("No distant device found.");
    }
}

void newBlink(DW1000Device *device) {
    Serial.print("blink; 1 device added! -> ");
    Serial.print(" short:");
    Serial.println(device->getShortAddress(), HEX);
}

void inactiveDevice(DW1000Device *device) {
    Serial.print("delete inactive device: ");
    Serial.println(device->getShortAddress(), HEX);
}

void setup() {
    Serial.begin(115200);
    setupWiFi();

    delay(1000);

    // Init configuration
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
    DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); // Reset, CS, IRQ pin

    // Attach handlers
    DW1000Ranging.attachNewRange(newRange);
    DW1000Ranging.attachBlinkDevice(newBlink);
    DW1000Ranging.attachInactiveDevice(inactiveDevice);

    // Start as anchor
    DW1000Ranging.startAsAnchor(ANCHOR_ADD, DW1000.MODE_LONGDATA_RANGE_LOWPOWER, false);
}

void loop() {
    DW1000Ranging.loop();
}
