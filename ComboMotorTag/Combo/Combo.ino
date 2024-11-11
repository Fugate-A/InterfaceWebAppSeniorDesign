#include "TagOG.h"
#include "TB6600_Code.h"
#include <WebServer.h>
#include <WiFi.h>

// Shared WiFi credentials and server declaration
const char* ssid = "ChairGuru";
const char* password = "123456789";
WebServer server(80);

// Motor-specific network configuration
IPAddress motorIP(192, 168, 4, 3);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

// Setup function to initialize Tag and Motor functionalities
void setup() {
    Serial.begin(115200);

    // Initialize Tag functionality (connects to WiFi)
    setupTag();

    // Configure static IP for Motor functionality
    if (!WiFi.config(motorIP, gateway, subnet)) {
        Serial.println("Failed to configure motor IP address!");
    }

    // Initialize Motor functionality
    setupMotor();
}

// Main loop to handle Tag and Motor logic
void loop() {
    // Handle Tag logic
    loopTag();

    // Handle Motor logic
    loopMotor();
}
