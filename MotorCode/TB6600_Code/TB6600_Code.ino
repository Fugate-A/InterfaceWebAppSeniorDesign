#include <WiFi.h>
#include <WebServer.h>

// Motor Controller WiFi Credentials
const char* ssid = "ESP32-Access-Point";
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

// Define other pins as needed
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

// Function to execute the move forward command
void moveForward(int inches) {
  Serial.print("Executing move forward for ");
  Serial.print(inches);
  Serial.println(" inches");

  int steps = inches * 17;
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
    delayMicroseconds(2500);
  }
}

// Handle incoming HTTP requests
void handleMoveRequest() {
  if (server.hasArg("plain")) {
    String command = server.arg("plain");
    Serial.print("Received command: ");
    Serial.println(command);

    if (command == "{\"command\":\"moveForward\"}") {
      moveForward(12);  // Execute move forward with example distance
      server.send(200, "application/json", "{\"status\":\"success\"}");
    } else {
      Serial.println("Unknown command");
      server.send(400, "application/json", "{\"error\":\"Unknown command\"}");
    }
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
