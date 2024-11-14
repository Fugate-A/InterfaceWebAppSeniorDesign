#include <SPI.h>
#include <DW1000Ranging.h>
#include "link.h"

// Pin definitions
#define SPI_SCK 18
#define SPI_MISO 19
#define SPI_MOSI 23
#define DW_CS 4
#define PIN_RST 27
#define PIN_IRQ 34

// Global variables
struct MyLink *uwb_data;
long runtime = 0;

// Function declarations
void newRange();
void newDevice(DW1000Device *device);
void inactiveDevice(DW1000Device *device);

// Setup function for UWB tag
void setupTag() {
    Serial.println("Initializing UWB Tag...");

    // Initialize SPI and DW1000 communication
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
    DW1000Ranging.initCommunication(PIN_RST, DW_CS, PIN_IRQ);
    DW1000Ranging.attachNewRange(newRange);
    DW1000Ranging.attachNewDevice(newDevice);
    DW1000Ranging.attachInactiveDevice(inactiveDevice);

    // Start DW1000 as a tag
    DW1000Ranging.startAsTag("7D:00:22:EA:82:60:3B:9C", DW1000.MODE_LONGDATA_RANGE_LOWPOWER);

    // Initialize UWB data structure
    uwb_data = init_link();
    Serial.println("UWB Tag initialized.");
}

// Loop function for UWB tag
void loopTag() {
    DW1000Ranging.loop();

    // Print location data periodically
    if ((millis() - runtime) > 3000) {
        Serial.println("Updating UWB location data...");
        // Generate and print JSON for location data
        String jsonPayload;
        make_link_json(uwb_data, &jsonPayload);
        Serial.println(jsonPayload);

        runtime = millis();
    }
}

void newRange() {
    DW1000Device* device = DW1000Ranging.getDistantDevice();
    if (device != nullptr) {
        Serial.print("New range data from: ");
        Serial.print(device->getShortAddress(), HEX);
        Serial.print(", Range: ");
        Serial.print(device->getRange());
        Serial.print(" m, RX Power: ");
        Serial.println(device->getRXPower());

        // Update the link structure
        fresh_link(uwb_data, device->getShortAddress(), device->getRange(), device->getRXPower());
    } else {
        Serial.println("No distant device found in newRange.");
    }
}


// Callback for new device detection
void newDevice(DW1000Device *device) {
    Serial.print("Device added: ");
    Serial.println(device->getShortAddress(), HEX);
    add_link(uwb_data, device->getShortAddress());
}

// Callback for inactive device removal
void inactiveDevice(DW1000Device *device) {
    Serial.print("Device removed: ");
    Serial.println(device->getShortAddress(), HEX);
    delete_link(uwb_data, device->getShortAddress());
}
