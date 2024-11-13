#include <SPI.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "DW1000Ranging.h"

#define ANCHOR_ADD "82:17:5B:D5:A9:9A:E2:9C"

#define SPI_SCK 18
#define SPI_MISO 19
#define SPI_MOSI 23
#define DW_CS 4

const char *anchorId = "1";

// WiFi credentials
const char *ssid = "ChairGuru";
const char *password = "123456789";

// Server settings
const char *serverUrl = "http://192.168.4.2:5000/api/store-current-chair-poss";

// Connection pins
const uint8_t PIN_RST = 27; // Reset pin
const uint8_t PIN_IRQ = 34; // IRQ pin
const uint8_t PIN_SS = 4;   // SPI select pin

void setup()
{
    Serial.begin(115200);
    delay(1000);

    // Initialize WiFi
    connectToWiFi();

    // Initialize SPI
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
    DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); // Reset, CS, IRQ pin

    // Define the sketch as an anchor
    DW1000Ranging.attachNewRange(newRange);
    DW1000Ranging.attachBlinkDevice(newBlink);
    DW1000Ranging.attachInactiveDevice(inactiveDevice);

    // Start the module as an anchor
    DW1000Ranging.startAsAnchor(ANCHOR_ADD, DW1000.MODE_LONGDATA_RANGE_LOWPOWER, false);
}

void loop()
{
    DW1000Ranging.loop();
}

// Function to connect to WiFi
void connectToWiFi()
{
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

// Function to send data to the server
void sendPositionToServer(const String &shortAddress, float range, float rxPower)
{
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("WiFi not connected. Retrying...");
        connectToWiFi();
        return;
    }

    HTTPClient http;
    http.begin(serverUrl);

    http.addHeader("Content-Type", "application/json");

    // Construct the payload
    String payload = "{\"shortAddress\": \"" + shortAddress + "\", \"range\": " + String(range) + ", \"rxPower\": " + String(rxPower) + ", \"anchorId\": \"" + String(anchorId) + "\"}";

    int httpResponseCode = http.POST(payload);

    if (httpResponseCode > 0)
    {
        Serial.print("Server response: ");
        Serial.println(httpResponseCode);
    }
    else
    {
        Serial.print("Error sending data: ");
        Serial.println(http.errorToString(httpResponseCode).c_str());
    }

    http.end();
}

// Callback when a new range is received
void newRange()
{
    // Get the tag's short address
    String tagShortAddress = String(DW1000Ranging.getDistantDevice()->getShortAddress(), HEX);

    // Construct the full short address for the anchor-tag pair
    String fullShortAddress = "Anchor" + String(anchorId) + "-Tag" + tagShortAddress;

    // Get range and RX power
    float range = DW1000Ranging.getDistantDevice()->getRange();
    float rxPower = DW1000Ranging.getDistantDevice()->getRXPower();

    // Log to Serial Monitor
    Serial.print("From: ");
    Serial.print(fullShortAddress);
    Serial.print("\tRange: ");
    Serial.print(range);
    Serial.print(" m");
    Serial.print("\tRX Power: ");
    Serial.print(rxPower);
    Serial.println(" dBm");

    // Send the data to the server
    sendPositionToServer(fullShortAddress, range, rxPower);
}

// Callback for new blinking device
void newBlink(DW1000Device *device)
{
    Serial.print("Blink; 1 device added -> short: ");
    Serial.println(device->getShortAddress(), HEX);
}

// Callback for inactive devices
void inactiveDevice(DW1000Device *device)
{
    Serial.print("Delete inactive device: ");
    Serial.println(device->getShortAddress(), HEX);
}
