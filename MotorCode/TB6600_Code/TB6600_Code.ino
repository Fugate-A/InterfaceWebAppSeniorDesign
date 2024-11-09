#include <WiFi.h>
#include <WebServer.h>

// Motor Controller WiFi Credentials
const char* ssid = "ChairGuru";
const char* password = "123456789";

const int enablePinOut = 15;

// Motor Controller IP Configuration
IPAddress local_IP(192, 168, 4, 3);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

// Motor control pins
int PULFL = 16;  // Pulse pin for Front-Left motor
int DIRFL = 2;   // Direction pin for Front-Left motor
int ENAFL = enablePinOut;  // Enable pin for Front-Left motor

int PULRL = 5;
int DIRRL = 17;
int ENARL = enablePinOut;

int PULFR = 22;
int DIRFR = 21;
int ENAFR = enablePinOut;

int PULRR = 14;
int DIRRR = 12;
int ENARR = enablePinOut;

// Web server on port 80
WebServer server(80);

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

    // First and last 10% of steps for acceleration and deceleration
  int normalSteps = steps;  // Remaining 80% of steps at normal speed

  for (int i = 0; i < 35; i++) {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);  // Normal delay for full speed
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(5000);
  }

  for (int i = 0; i < 35; i++) {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);  // Normal delay for full speed
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(4500);
  }
  // Constant speed phase
  for (int i = 0; i < normalSteps; i++) {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);  // Normal delay for full speed
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(4000);
  }

  
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

  int slowSteps = steps * 0.1;
  int normalSteps = steps;

  // Acceleration phase
  for (int i = 0; i < 35; i++) {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);  // Normal delay for full speed
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(5000);
  }

  for (int i = 0; i < 35; i++) {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);  // Normal delay for full speed
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(4500);
  }
  // Constant speed phase
  for (int i = 0; i < normalSteps; i++) {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(4000);
  }

  
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

  for (int i = 0; i < 35; i++) {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);  // Normal delay for full speed
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(5000);
  }

  for (int i = 0; i < 35; i++) {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);  // Normal delay for full speed
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(4500);
  }

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
    delayMicroseconds(4000);
  }
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

  for (int i = 0; i < 35; i++) {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);  // Normal delay for full speed
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(5000);
  }

  for (int i = 0; i < 35; i++) {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);  // Normal delay for full speed
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(4500);
  }

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
    delayMicroseconds(4000);
    //delayMicroseconds(2500);
  }
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

  for (int i = 0; i < 35; i++) {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);  // Normal delay for full speed
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(5000);
  }

  for (int i = 0; i < 35; i++) {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);  // Normal delay for full speed
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(4500);
  }

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
    delayMicroseconds(4000);
  }
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

  for (int i = 0; i < 35; i++) {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);  // Normal delay for full speed
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(5000);
  }

  for (int i = 0; i < 35; i++) {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);  // Normal delay for full speed
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(4500);
  }

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
    delayMicroseconds(4000);
  }
}

#include <ArduinoJson.h> // Ensure you have the ArduinoJson library installed

// Handle incoming HTTP requests with JSON parsing
void handleMoveRequest() {
  if (server.hasArg("plain")) {
    String command = server.arg("plain");
    Serial.print("Received command: ");
    Serial.println(command);

    // Parse JSON command
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, command);
    if (error) {
      Serial.print("JSON parse error: ");
      Serial.println(error.c_str());
      server.send(400, "application/json", "{\"error\":\"Invalid JSON format\"}");
      return;
    }

    // Extract command and value from JSON
    String action = doc["command"];
    int value = doc["value"];

    // Execute the appropriate function based on the command
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


void setup() {
  Serial.begin(115200);

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

  // Configure static IP for the motor ESP32
  WiFi.config(local_IP, gateway, subnet);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to ");
  Serial.print(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected!");
  Serial.print("Motor ESP IP Address: ");
  Serial.println(WiFi.localIP());

  // Set up HTTP server routes
  server.on("/move", HTTP_POST, handleMoveRequest);
  server.begin();
  Serial.println("HTTP server started, waiting for commands...");
}

void loop() {
  server.handleClient();
}
