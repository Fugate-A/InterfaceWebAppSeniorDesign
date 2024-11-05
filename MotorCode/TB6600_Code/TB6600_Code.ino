// Include necessary libraries
#include <esp_now.h>
#include <WiFi.h>

int PULFL = 16; //define Pulse pin
int DIRFL = 2;  //define Direction pin
int ENAFL = 35; //define Enable Pin

int PULRL = 5;
int DIRRL = 17;
int ENARL = 35;

int PULFR = 22;
int DIRFR = 21;
int ENAFR = 35;

int PULRR = 14;
int DIRRR = 12;
int ENARR = 35;


// Function prototypes for movement commands
void moveForward(int inches);
void moveBackward(int inches);
void translateLeft(int inches);
void translateRight(int inches);
void rotateClockwise(int degrees);
void rotateCounterClockwise(int degrees);

// ESP-NOW callback for receiving commands
void onDataRecv(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len);

void setup() {
  Serial.begin(115200);

  // Set up motor pins
  pinMode (PULFL, OUTPUT);
  pinMode (DIRFL, OUTPUT);
  pinMode (ENAFL, OUTPUT);
  pinMode (PULRL, OUTPUT);
  pinMode (DIRRL, OUTPUT);
  pinMode (ENARL, OUTPUT);
  pinMode (PULFR, OUTPUT);
  pinMode (DIRFR, OUTPUT);
  pinMode (ENAFR, OUTPUT);
  pinMode (PULRR, OUTPUT);
  pinMode (DIRRR, OUTPUT);
  pinMode (ENARR, OUTPUT);

  // Initialize WiFi and ESP-NOW
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(onDataRecv);
}

// ESP-NOW data receive callback
void onDataRecv(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len) {
  String command = String((char*)incomingData).substring(0, len);
  Serial.print("Received command: ");
  Serial.println(command);

  if (command == "moveForward") {
    moveForward(12);  // Example to move forward 12 inches
  } else if (command == "moveBackward") {
    moveBackward(12);
  } else if (command == "translateLeft") {
    translateLeft(12);
  } else if (command == "translateRight") {
    translateRight(12);
  } else if (command == "rotateClockwise") {
    rotateClockwise(90);
  } else if (command == "rotateCounterClockwise") {
    rotateCounterClockwise(90);
  }
}

void loop() {
  // No need for any code in loop()
}

// Utility functions for motor control
int convertInchToStep(int inches) {
  return inches * 17;  // Adjust for your wheel and stepper setup
}

int convertDegreesToSteps(int degrees) {
  return degrees * 17;  // Adjust for your specific rotation and stepper setup
}

// FORWARD MOVEMENT
void moveForward(int inches) {
  int steps = convertInchToStep(inches);

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

// BACKWARD MOVEMENT
void moveBackward(int inches) {
  int steps = convertInchToStep(inches);

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
    delayMicroseconds(2500);
  }
}

// LEFT TRANSLATION
void translateLeft(int inches) {
  int steps = convertInchToStep(inches);

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
    delayMicroseconds(2500);
  }
}

// RIGHT TRANSLATION
void translateRight(int inches) {
  int steps = convertInchToStep(inches);

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
    delayMicroseconds(2500);
  }
}

// COUNTERCLOCKWISE ROTATION
void rotateCounterClockwise(int degrees) {
  int steps = convertDegreesToSteps(degrees);

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
    delayMicroseconds(2500);
  }
}

// CLOCKWISE ROTATION
void rotateClockwise(int degrees) {
  int steps = convertDegreesToSteps(degrees);

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
    delayMicroseconds(2500);
  }
}
