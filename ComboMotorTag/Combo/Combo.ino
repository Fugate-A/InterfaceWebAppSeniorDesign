//#include "TagOG.h"
//#include "TB6600_Code.h"
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

// WiFi credentials
const char* ssid = "ChairGuru";
const char* password = "123456789";

// Static IP configuration
IPAddress local_IP(192, 168, 4, 3);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

// WebSocket server
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// Global flag for message processing
volatile bool messageReceived = false;
String receivedMessage;
//---------------------------------------------------------------------------

const int enablePinOut = 15;

// Motor control pins
int PULFL = 16;  // Pulse pin for Front-Left motor
int DIRFL = 2;   // Direction pin for Front-Left motor
int ENAFL = enablePinOut;

int PULRL = 5;
int DIRRL = 17;
int ENARL = enablePinOut;

int PULFR = 22;
int DIRFR = 21;
int ENAFR = enablePinOut;

int PULRR = 14;
int DIRRR = 12;
int ENARR = enablePinOut;
// Convert inches or degrees to steps for the motors
int convertToSteps(int units) {
    return units * 17;  // Adjust the conversion factor as needed
}

void moveForward(int inches) {
    int steps = convertToSteps(inches);
    Serial.print("Moving forward for ");
    Serial.print(inches);
    Serial.println(" inches");

    digitalWrite(DIRFL, LOW);
    digitalWrite(DIRRL, LOW);
    digitalWrite(DIRFR, HIGH);
    digitalWrite(DIRRR, HIGH);

    for (int i = 0; i < steps; i++) {
        digitalWrite(PULFL, HIGH);
        digitalWrite(PULRL, HIGH);
        digitalWrite(PULFR, HIGH);
        digitalWrite(PULRR, HIGH);
        delayMicroseconds(20);
        digitalWrite(PULFL, LOW);
        digitalWrite(PULRL, LOW);
        digitalWrite(PULFR, LOW);
        digitalWrite(PULRR, LOW);
        delayMicroseconds(5000);
    }

    delay(1500);
}

void moveBackward(int inches) {
    int steps = convertToSteps(inches);
    Serial.print("Moving backward for ");
    Serial.print(inches);
    Serial.println(" inches");

    digitalWrite(DIRFL, HIGH);
    digitalWrite(DIRRL, HIGH);
    digitalWrite(DIRFR, LOW);
    digitalWrite(DIRRR, LOW);

    for (int i = 0; i < steps; i++) {
        digitalWrite(PULFL, HIGH);
        digitalWrite(PULRL, HIGH);
        digitalWrite(PULFR, HIGH);
        digitalWrite(PULRR, HIGH);
        delayMicroseconds(20);
        digitalWrite(PULFL, LOW);
        digitalWrite(PULRL, LOW);
        digitalWrite(PULFR, LOW);
        digitalWrite(PULRR, LOW);
        delayMicroseconds(5000);
    }

    delay(1500);
}

void translateRight(int inches) {
    int steps = convertToSteps(inches);
    Serial.print("Translating right for ");
    Serial.print(inches);
    Serial.println(" inches");

    digitalWrite(DIRFL, LOW);
    digitalWrite(DIRRL, HIGH);
    digitalWrite(DIRFR, LOW);
    digitalWrite(DIRRR, HIGH);

    for (int i = 0; i < steps; i++) {
        digitalWrite(PULFL, HIGH);
        digitalWrite(PULRL, HIGH);
        digitalWrite(PULFR, HIGH);
        digitalWrite(PULRR, HIGH);
        delayMicroseconds(20);
        digitalWrite(PULFL, LOW);
        digitalWrite(PULRL, LOW);
        digitalWrite(PULFR, LOW);
        digitalWrite(PULRR, LOW);
        delayMicroseconds(5000);
    }

    delay(1500);
}

void translateLeft(int inches) {
    int steps = convertToSteps(inches);
    Serial.print("Translating left for ");
    Serial.print(inches);
    Serial.println(" inches");

    digitalWrite(DIRFL, HIGH);
    digitalWrite(DIRRL, LOW);
    digitalWrite(DIRFR, HIGH);
    digitalWrite(DIRRR, LOW);

    for (int i = 0; i < steps; i++) {
        digitalWrite(PULFL, HIGH);
        digitalWrite(PULRL, HIGH);
        digitalWrite(PULFR, HIGH);
        digitalWrite(PULRR, HIGH);
        delayMicroseconds(20);
        digitalWrite(PULFL, LOW);
        digitalWrite(PULRL, LOW);
        digitalWrite(PULFR, LOW);
        digitalWrite(PULRR, LOW);
        delayMicroseconds(5000);
    }

    delay(1500);
}

void rotateClockwise(int degrees) {
    int steps = convertToSteps(degrees);
    Serial.print("Rotating clockwise for ");
    Serial.print(degrees);
    Serial.println(" degrees");

    digitalWrite(DIRFL, LOW);
    digitalWrite(DIRRL, LOW);
    digitalWrite(DIRFR, LOW);
    digitalWrite(DIRRR, LOW);

    for (int i = 0; i < steps; i++) {
        digitalWrite(PULFL, HIGH);
        digitalWrite(PULRL, HIGH);
        digitalWrite(PULFR, HIGH);
        digitalWrite(PULRR, HIGH);
        delayMicroseconds(20);
        digitalWrite(PULFL, LOW);
        digitalWrite(PULRL, LOW);
        digitalWrite(PULFR, LOW);
        digitalWrite(PULRR, LOW);
        delayMicroseconds(5000);
    }

    delay(1500);
}

void rotateCounterClockwise(int degrees) {
    int steps = convertToSteps(degrees);
    Serial.print("Rotating counter-clockwise for ");
    Serial.print(degrees);
    Serial.println(" degrees");

    digitalWrite(DIRFL, HIGH);
    digitalWrite(DIRRL, HIGH);
    digitalWrite(DIRFR, HIGH);
    digitalWrite(DIRRR, HIGH);

    for (int i = 0; i < steps; i++) {
        digitalWrite(PULFL, HIGH);
        digitalWrite(PULRL, HIGH);
        digitalWrite(PULFR, HIGH);
        digitalWrite(PULRR, HIGH);
        delayMicroseconds(20);
        digitalWrite(PULFL, LOW);
        digitalWrite(PULRL, LOW);
        digitalWrite(PULFR, LOW);
        digitalWrite(PULRR, LOW);
        delayMicroseconds(5000);
    }

    delay(1500);
}
//---------------------------------------------------------------------

// WebSocket event handler
void onWebSocketMessage(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
    if (type == WS_EVT_DATA) {
        // Parse the received message
        String message = String((char *)data);
        Serial.print("Message received: ");
        Serial.println(message);

        if (message.indexOf(",") == -1) {
            Serial.println("Malformed message received");
            return;
        }

        // Store the message for processing
        receivedMessage = message;
        messageReceived = true;
    }
}

// Setup function
void setup() {
    Serial.begin(115200);

    // Configure static IP and connect to WiFi
    WiFi.config(local_IP, gateway, subnet);
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

    // Initialize WebSocket
    ws.onEvent(onWebSocketMessage);
    server.addHandler(&ws);

    // Start the server
    server.begin();
    Serial.println("WebSocket server started");

      // Set up motor pins as outputs
  pinMode(PULFL, OUTPUT);
  pinMode(DIRFL, OUTPUT);
  pinMode(ENAFL, OUTPUT);

  pinMode(PULRL, OUTPUT);
  pinMode(DIRRL, OUTPUT);
  pinMode(ENARL, OUTPUT);

  pinMode(PULFR, OUTPUT);
  pinMode(DIRFR, OUTPUT);
  pinMode(ENAFR, OUTPUT);

  pinMode(PULRR, OUTPUT);
  pinMode(DIRRR, OUTPUT);
  pinMode(ENARR, OUTPUT);

  Serial.println("Dummy forgor his setup pin mode");
}

// Function to process WebSocket messages
void processMessage(const String &message) {
    if (message.startsWith("pos")) {
        // Parse and execute position sampling
        int samples = message.substring(message.indexOf(",") + 1).toInt();
        Serial.printf("Running tag code with %d samples\n", samples);
        setupTag();
        for (int i = 0; i < samples; i++) {
            loopTag();
        }
    } else if (message.startsWith("motors")) {
        // Parse and execute motor command
        String command = message.substring(message.indexOf(",") + 1, message.lastIndexOf(","));
        int steps = message.substring(message.lastIndexOf(",") + 1).toInt();
        Serial.printf("Running motor code: %s with %d steps\n", command.c_str(), steps);

        if (command == "moveForward") moveForward(steps);
        else if (command == "moveBackward") moveBackward(steps);
        else if (command == "translateLeft") translateLeft(steps);
        else if (command == "translateRight") translateRight(steps);
        else if (command == "rotateClockwise") rotateClockwise(steps);
        else if (command == "rotateCounterClockwise") rotateCounterClockwise(steps);
        else Serial.println("Unknown motor command");
    } else if (message.indexOf("estop") != -1) {
        // Handle emergency stop command
        Serial.println("E-Stop received! Restarting the system...");
        ESP.restart();
    } else {
        Serial.println("Unknown message type");
    }
}

// Main loop
void loop() {
    // Handle WebSocket messages
    if (messageReceived) {
        processMessage(receivedMessage);
        messageReceived = false; // Reset the flag after processing
    }

    // Maintain WebSocket connection
    ws.cleanupClients();

    // Small delay to prevent excessive CPU usage
    delay(100);
}