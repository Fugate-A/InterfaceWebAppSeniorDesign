#include <SPI.h>
#include <DW1000Ranging.h>
#include <WiFi.h>
#include "link.h"
#include <WebServer.h>

// Pin definitions
#define SPI_SCK 18
#define SPI_MISO 19
#define SPI_MOSI 23
#define DW_CS 4
#define PIN_RST 27
#define PIN_IRQ 34

// WiFi credentials
const char *ssid = "ChairGuru";
const char *password = "123456789";
const char *host = "192.168.4.1";

WiFiClient client;
WebServer server(80); // HTTP server on port 80

struct MyLink *uwb_data;
int index_num = 0;
long runtime = 0;
String all_json = "";

// Hardcoded short address (mutable)
char hardcodedShortAddress[] = "7D00";

// Function declarations
void newRange();
void newDevice(DW1000Device *device);
void inactiveDevice(DW1000Device *device);
void send_uwb_data();
String create_json_payload();

// Setup function
void setup() {
    Serial.begin(115200);

    // Initialize WiFi
    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    delay(4000);

    // Initialize SPI and DW1000
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
    DW1000Ranging.initCommunication(PIN_RST, DW_CS, PIN_IRQ);
    DW1000Ranging.attachNewRange(newRange);
    DW1000Ranging.attachNewDevice(newDevice);
    DW1000Ranging.attachInactiveDevice(inactiveDevice);

    // Start the DW1000 as a tag with a hardcoded short address
    DW1000Ranging.startAsTag(hardcodedShortAddress, DW1000.MODE_LONGDATA_RANGE_LOWPOWER);

    // Set up HTTP routes
    server.on("/getUWBData", HTTP_GET, send_uwb_data);
    server.on("/hello", HTTP_GET, []() {
        server.send(200, "text/plain", "Hello World!");
    });
    server.begin();
    uwb_data = init_link();
}

// Main loop function
void loop() {
    DW1000Ranging.loop();
    server.handleClient();

    if ((millis() - runtime) > 3000) {
        make_link_json(uwb_data, &all_json);
        runtime = millis();
    }
}

// Callback for a new range event
void newRange() {
    String shortAddress = String(hardcodedShortAddress);
    float range = DW1000Ranging.getDistantDevice()->getRange();
    float rxPower = DW1000Ranging.getDistantDevice()->getRXPower();

    Serial.print("from: ");
    Serial.print(shortAddress);
    Serial.print("\t Range: ");
    Serial.print(range);
    Serial.print(" m");
    Serial.print("\t RX power: ");
    Serial.print(rxPower);
    Serial.println(" dBm");

    fresh_link(uwb_data, DW1000Ranging.getDistantDevice()->getShortAddress(), range, rxPower);
}

// Callback for a new device
void newDevice(DW1000Device *device) {
    Serial.print("Ranging init; 1 device added! -> ");
    Serial.print("short: ");
    Serial.println(device->getShortAddress(), HEX);
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    add_link(uwb_data, device->getShortAddress());
}

// Callback for inactive device
void inactiveDevice(DW1000Device *device) {
    Serial.print("Delete inactive device: ");
    Serial.println(device->getShortAddress(), HEX);
    delete_link(uwb_data, device->getShortAddress());
}

// Send UWB data via HTTP
void send_uwb_data() {
    String jsonPayload = create_json_payload();
    server.send(200, "application/json", jsonPayload);
}

// Create JSON payload for UWB data
String create_json_payload() {
    String jsonPayload = "{";

    DW1000Device *device = DW1000Ranging.getDistantDevice();
    if (device == NULL) {
        Serial.println("No device in range");
        return "{\"error\": \"No device in range\"}";
    }

    uint64_t shortAddress = DW1000Ranging.getDistantDevice()->getShortAddress();
    float range = DW1000Ranging.getDistantDevice()->getRange();
    float rxPower = DW1000Ranging.getDistantDevice()->getRXPower();

    jsonPayload += "\"shortAddress\": \"" + String(shortAddress, HEX) + "\",";
    jsonPayload += "\"range\": " + String(range, 3) + ",";
    jsonPayload += "\"rxPower\": " + String(rxPower, 1);
    jsonPayload += "}";

    return jsonPayload;
}
