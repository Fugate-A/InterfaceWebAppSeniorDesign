#include "TagOG.h" // Include your Tag library when it's needed
#include "TB6600_Code.h"
#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h> // Include ArduinoJson for POST request processing

// WiFi credentials
const char* ssid = "ChairGuru";
const char* password = "123456789";

// Static IP configuration for the motor controller
IPAddress motorIP(192, 168, 4, 3);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

// Web server declaration
WebServer server(80);  // HTTP server on port 80

// Function to handle the motor move request
void handleMotorControl() {
    if (server.hasArg("plain")) {
        String command = server.arg("plain");
        Serial.print("Received command: ");
        Serial.println(command);

        // Parse the received JSON command
        DynamicJsonDocument doc(1024);
        DeserializationError error = deserializeJson(doc, command);
        if (error) {
            Serial.print("JSON parse error: ");
            Serial.println(error.c_str());
            server.send(400, "application/json", "{\"error\":\"Invalid JSON format\"}");
            return;
        }

        // Get action (command) and value (steps or distance)
        String action = doc["command"];
        int value = doc["value"];

        // Handle motor commands
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
            Serial.println("Unknown command");
            server.send(400, "application/json", "{\"error\":\"Unknown command\"}");
            return;
        }

        // Send a success response after executing the motor command
        server.send(200, "application/json", "{\"status\":\"success\"}");
    } else {
        Serial.println("No command received");
        server.send(400, "application/json", "{\"error\":\"No command received\"}");
    }
}

// Setup function to initialize motor and network settings
void setup() {
    Serial.begin(115200);

    // Connect to Wi-Fi
    WiFi.config(motorIP, gateway, subnet);
    WiFi.begin(ssid, password);

    int retryCount = 0;
    while (WiFi.status() != WL_CONNECTED && retryCount < 20) {
        delay(500);
        Serial.print(".");
        retryCount++;
    }
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("\nFailed to connect to WiFi. Restarting...");
        ESP.restart();
    }
    Serial.println("\nConnected to WiFi");

    // Set up motor pins
    setupMotor();

    // Initialize motor control and define HTTP POST route for motor movements
    server.on("/move", HTTP_POST, handleMotorControl);
    server.begin();
    Serial.println("Server started and listening on port 80");
}

// Main loop to handle client requests and motor logic
void loop() {
    // Handle HTTP client requests
    server.handleClient();
}
