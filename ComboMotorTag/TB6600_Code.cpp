#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>

// Declare shared variables from Combo.ino
extern const char* ssid;
extern const char* password;
extern WebServer server;

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

// Function implementations remain unchanged
// (Refer to your provided TB6600_Code.cpp for the full content)


// Web server on port 80
//WebServer server(80);

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











void handleMoveRequest() {
    if (server.hasArg("plain")) {
        String command = server.arg("plain");
        Serial.print("Received command: ");
        Serial.println(command);

        DynamicJsonDocument doc(1024);
        DeserializationError error = deserializeJson(doc, command);
        if (error) {
            Serial.print("JSON parse error: ");
            Serial.println(error.c_str());
            server.send(400, "application/json", "{\"error\":\"Invalid JSON format\"}");
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
            Serial.println("Unknown command");
            server.send(400, "application/json", "{\"error\":\"Unknown command\"}");
            return;
        }
        server.send(200, "application/json", "{\"status\":\"success\"}");
    } else {
        Serial.println("No command received");
        server.send(400, "application/json", "{\"error\":\"No command received\"}");
    }
}

void setupMotor() {
    Serial.println("Initializing Motor Pins...");
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

    // Set up HTTP routes for motor commands
    server.on("/move", HTTP_POST, handleMoveRequest);
    Serial.println("Motor HTTP routes initialized.");
}

void loopMotor() {
    server.handleClient();
}