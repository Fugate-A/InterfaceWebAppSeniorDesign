//#include "TagOG.h" // UWB Tag functionality
#include "TB6600_Code.h" // Motor control functionality
#include <WiFi.h>
#include <WebServer.h> // For ESP32, ensure this library is available
#include <ArduinoJson.h>

// Wi-Fi credentials
const char* ssid = "ChairGuru";
const char* password = "123456789";

// Static IP configuration
IPAddress motorIP(192, 168, 4, 4);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

// Web server for motor control
WebServer server(80);

// Function to handle motor move requests
void handleMotorControl() {
    if (server.hasArg("plain")) {
        String command = server.arg("plain");
        DynamicJsonDocument doc(1024);

        DeserializationError error = deserializeJson(doc, command);
        if (error) {
            server.send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
            return;
        }

        String action = doc["command"];
        int value = doc["value"];

        if (action == "moveForward") {
            moveForward(value);
        } else if (action == "moveBackward") {
            moveBackward(value);
        } else if (action == "translateLeft") {
            translateLeft(value);
        } else if (action == "translateRight") {
            translateRight(value);
        } else if (action == "rotateClockwise") {
            rotateClockwise(value);
        } else if (action == "rotateCounterClockwise") {
            rotateCounterClockwise(value);
        } else {
            server.send(400, "application/json", "{\"error\":\"Unknown command\"}");
            return;
        }

        server.send(200, "application/json", "{\"status\":\"success\"}");
    } else {
        server.send(400, "application/json", "{\"error\":\"No command received\"}");
    }
}

// Setup function
void setup() {
    Serial.begin(115200);

    // Configure Wi-Fi
    WiFi.config(motorIP, gateway, subnet);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWi-Fi Connected.");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // Initialize motor and Tag functionality
    setupMotor();
    //setupTag();

    // Define POST route for motor commands
    server.on("/move", HTTP_POST, handleMotorControl);
    server.begin();
    Serial.println("Server started on port 80.");
}

// Main loop
void loop() {
    // Handle HTTP client requests
    server.handleClient();

    // Execute UWB Tag operations
    //loopTag();

    // Periodically print location data (no JSON generation)
   /* static unsigned long lastPrintTime = 0;
    if (millis() - lastPrintTime > 5000) { // Print every 5 seconds
        Serial.println("UWB Tag data updated.");
        //print_link(uwb_data); // Print tag data directly
        lastPrintTime = millis();
    }*/
}
