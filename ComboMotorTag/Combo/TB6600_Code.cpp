#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include "TB6600_Code.h"

// Define motor pins
const int PULFL = 16;
const int DIRFL = 2;
const int ENAFL = 15;
const int PULRL = 5;
const int DIRRL = 17;
const int ENARL = 15;
const int PULFR = 22;
const int DIRFR = 21;
const int ENAFR = 15;
const int PULRR = 14;
const int DIRRR = 12;
const int ENARR = 15;

//1 step = 0.001525 Meters
//655 steps per meter.

void moveForward(int steps) {
  Serial.print("Moving forward for ");
  Serial.print(steps);
  Serial.println(" steps");

  digitalWrite(DIRFL, LOW);
  digitalWrite(DIRRL, LOW);
  digitalWrite(DIRFR, HIGH);
  digitalWrite(DIRRR, HIGH);


  if(steps < 61){
    for (int i = 0; i < steps; i++) {
      digitalWrite(PULFL, HIGH);
      digitalWrite(PULRL, HIGH);
      digitalWrite(PULFR, HIGH);
      digitalWrite(PULRR, HIGH);
      delayMicroseconds(20);  // Normal delay for full speed
      digitalWrite(PULFL, LOW);
      digitalWrite(PULRL, LOW);
      digitalWrite(PULFR, LOW);
      digitalWrite(PULRR, LOW);
      delayMicroseconds(6000);
    }

    delay(1500);
  }
  else{
    for (int i = 0; i < 15; i++) {
      digitalWrite(PULFL, HIGH);
      digitalWrite(PULRL, HIGH);
      digitalWrite(PULFR, HIGH);
      digitalWrite(PULRR, HIGH);
      delayMicroseconds(20);  // Normal delay for full speed
      digitalWrite(PULFL, LOW);
      digitalWrite(PULRL, LOW);
      digitalWrite(PULFR, LOW);
      digitalWrite(PULRR, LOW);
      delayMicroseconds(6000);
    }

    for (int i = 0; i < 15; i++) {
      digitalWrite(PULFL, HIGH);
      digitalWrite(PULRL, HIGH);
      digitalWrite(PULFR, HIGH);
      digitalWrite(PULRR, HIGH);
      delayMicroseconds(20);  // Normal delay for full speed
      digitalWrite(PULFL, LOW);
      digitalWrite(PULRL, LOW);
      digitalWrite(PULFR, LOW);
      digitalWrite(PULRR, LOW);
      delayMicroseconds(5500);
    }
    // Constant speed phase
    for (int i = 0; i < steps - 60; i++) {
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

    for (int i = 0; i < 15; i++) {
      digitalWrite(PULFL, HIGH);
      digitalWrite(PULRL, HIGH);
      digitalWrite(PULFR, HIGH);
      digitalWrite(PULRR, HIGH);
      delayMicroseconds(20);  // Normal delay for full speed
      digitalWrite(PULFL, LOW);
      digitalWrite(PULRL, LOW);
      digitalWrite(PULFR, LOW);
      digitalWrite(PULRR, LOW);
      delayMicroseconds(5500);
    }

    for (int i = 0; i < 15; i++) {
      digitalWrite(PULFL, HIGH);
      digitalWrite(PULRL, HIGH);
      digitalWrite(PULFR, HIGH);
      digitalWrite(PULRR, HIGH);
      delayMicroseconds(20);  // Normal delay for full speed
      digitalWrite(PULFL, LOW);
      digitalWrite(PULRL, LOW);
      digitalWrite(PULFR, LOW);
      digitalWrite(PULRR, LOW);
      delayMicroseconds(6000);
    }
  }

  delay(1500);
}

void moveBackward(int steps) {
  Serial.print("Moving backward for ");
  Serial.print(steps);
  Serial.println(" steps");

  digitalWrite(DIRFL, HIGH);
  digitalWrite(DIRRL, HIGH);
  digitalWrite(DIRFR, LOW);
  digitalWrite(DIRRR, LOW);

  // Acceleration phase
  if(steps < 61){
    for (int i = 0; i < steps; i++) {
      digitalWrite(PULFL, HIGH);
      digitalWrite(PULRL, HIGH);
      digitalWrite(PULFR, HIGH);
      digitalWrite(PULRR, HIGH);
      delayMicroseconds(20);  // Normal delay for full speed
      digitalWrite(PULFL, LOW);
      digitalWrite(PULRL, LOW);
      digitalWrite(PULFR, LOW);
      digitalWrite(PULRR, LOW);
      delayMicroseconds(6000);
    }

    delay(1500);
  }
  else{
    for (int i = 0; i < 15; i++) {
      digitalWrite(PULFL, HIGH);
      digitalWrite(PULRL, HIGH);
      digitalWrite(PULFR, HIGH);
      digitalWrite(PULRR, HIGH);
      delayMicroseconds(20);  // Normal delay for full speed
      digitalWrite(PULFL, LOW);
      digitalWrite(PULRL, LOW);
      digitalWrite(PULFR, LOW);
      digitalWrite(PULRR, LOW);
      delayMicroseconds(6000);
    }

    for (int i = 0; i < 15; i++) {
      digitalWrite(PULFL, HIGH);
      digitalWrite(PULRL, HIGH);
      digitalWrite(PULFR, HIGH);
      digitalWrite(PULRR, HIGH);
      delayMicroseconds(20);  // Normal delay for full speed
      digitalWrite(PULFL, LOW);
      digitalWrite(PULRL, LOW);
      digitalWrite(PULFR, LOW);
      digitalWrite(PULRR, LOW);
      delayMicroseconds(5500);
    }
    // Constant speed phase
    for (int i = 0; i < steps - 60; i++) {
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

    for (int i = 0; i < 15; i++) {
      digitalWrite(PULFL, HIGH);
      digitalWrite(PULRL, HIGH);
      digitalWrite(PULFR, HIGH);
      digitalWrite(PULRR, HIGH);
      delayMicroseconds(20);  // Normal delay for full speed
      digitalWrite(PULFL, LOW);
      digitalWrite(PULRL, LOW);
      digitalWrite(PULFR, LOW);
      digitalWrite(PULRR, LOW);
      delayMicroseconds(5500);
    }

    for (int i = 0; i < 15; i++) {
      digitalWrite(PULFL, HIGH);
      digitalWrite(PULRL, HIGH);
      digitalWrite(PULFR, HIGH);
      digitalWrite(PULRR, HIGH);
      delayMicroseconds(20);  // Normal delay for full speed
      digitalWrite(PULFL, LOW);
      digitalWrite(PULRL, LOW);
      digitalWrite(PULFR, LOW);
      digitalWrite(PULRR, LOW);
      delayMicroseconds(6000);
    }
  }

  delay(1500);
}

void translateRight(int steps) {
  
  Serial.print("Translating right for ");
  Serial.print(steps);
  Serial.println(" steps");

  digitalWrite(DIRFL, LOW);
  digitalWrite(DIRRL, HIGH);
  digitalWrite(DIRFR, LOW);
  digitalWrite(DIRRR, HIGH);

  if(steps < 61){
    for (int i = 0; i < steps; i++) {
      digitalWrite(PULFL, HIGH);
      digitalWrite(PULRL, HIGH);
      digitalWrite(PULFR, HIGH);
      digitalWrite(PULRR, HIGH);
      delayMicroseconds(20);  // Normal delay for full speed
      digitalWrite(PULFL, LOW);
      digitalWrite(PULRL, LOW);
      digitalWrite(PULFR, LOW);
      digitalWrite(PULRR, LOW);
      delayMicroseconds(6000);
    }

    delay(1500);
  }
  else{
    for (int i = 0; i < 15; i++) {
      digitalWrite(PULFL, HIGH);
      digitalWrite(PULRL, HIGH);
      digitalWrite(PULFR, HIGH);
      digitalWrite(PULRR, HIGH);
      delayMicroseconds(20);  // Normal delay for full speed
      digitalWrite(PULFL, LOW);
      digitalWrite(PULRL, LOW);
      digitalWrite(PULFR, LOW);
      digitalWrite(PULRR, LOW);
      delayMicroseconds(6000);
    }

    for (int i = 0; i < 15; i++) {
      digitalWrite(PULFL, HIGH);
      digitalWrite(PULRL, HIGH);
      digitalWrite(PULFR, HIGH);
      digitalWrite(PULRR, HIGH);
      delayMicroseconds(20);  // Normal delay for full speed
      digitalWrite(PULFL, LOW);
      digitalWrite(PULRL, LOW);
      digitalWrite(PULFR, LOW);
      digitalWrite(PULRR, LOW);
      delayMicroseconds(5500);
    }
    // Constant speed phase
    for (int i = 0; i < steps - 60; i++) {
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

    for (int i = 0; i < 15; i++) {
      digitalWrite(PULFL, HIGH);
      digitalWrite(PULRL, HIGH);
      digitalWrite(PULFR, HIGH);
      digitalWrite(PULRR, HIGH);
      delayMicroseconds(20);  // Normal delay for full speed
      digitalWrite(PULFL, LOW);
      digitalWrite(PULRL, LOW);
      digitalWrite(PULFR, LOW);
      digitalWrite(PULRR, LOW);
      delayMicroseconds(5500);
    }

    for (int i = 0; i < 15; i++) {
      digitalWrite(PULFL, HIGH);
      digitalWrite(PULRL, HIGH);
      digitalWrite(PULFR, HIGH);
      digitalWrite(PULRR, HIGH);
      delayMicroseconds(20);  // Normal delay for full speed
      digitalWrite(PULFL, LOW);
      digitalWrite(PULRL, LOW);
      digitalWrite(PULFR, LOW);
      digitalWrite(PULRR, LOW);
      delayMicroseconds(6000);
    }
  }

  delay(1500);
}

void translateLeft(int steps) {
  
  Serial.print("Translating right for ");
  Serial.print(steps);
  Serial.println(" steps");

  digitalWrite(DIRFL, HIGH);
  digitalWrite(DIRRL, LOW);
  digitalWrite(DIRFR, HIGH;
  digitalWrite(DIRRR, LOW);

  if(steps < 61){
    for (int i = 0; i < steps; i++) {
      digitalWrite(PULFL, HIGH);
      digitalWrite(PULRL, HIGH);
      digitalWrite(PULFR, HIGH);
      digitalWrite(PULRR, HIGH);
      delayMicroseconds(20);  // Normal delay for full speed
      digitalWrite(PULFL, LOW);
      digitalWrite(PULRL, LOW);
      digitalWrite(PULFR, LOW);
      digitalWrite(PULRR, LOW);
      delayMicroseconds(6000);
    }

    delay(1500);
  }
  else{
    for (int i = 0; i < 15; i++) {
      digitalWrite(PULFL, HIGH);
      digitalWrite(PULRL, HIGH);
      digitalWrite(PULFR, HIGH);
      digitalWrite(PULRR, HIGH);
      delayMicroseconds(20);  // Normal delay for full speed
      digitalWrite(PULFL, LOW);
      digitalWrite(PULRL, LOW);
      digitalWrite(PULFR, LOW);
      digitalWrite(PULRR, LOW);
      delayMicroseconds(6000);
    }

    for (int i = 0; i < 15; i++) {
      digitalWrite(PULFL, HIGH);
      digitalWrite(PULRL, HIGH);
      digitalWrite(PULFR, HIGH);
      digitalWrite(PULRR, HIGH);
      delayMicroseconds(20);  // Normal delay for full speed
      digitalWrite(PULFL, LOW);
      digitalWrite(PULRL, LOW);
      digitalWrite(PULFR, LOW);
      digitalWrite(PULRR, LOW);
      delayMicroseconds(5500);
    }
    // Constant speed phase
    for (int i = 0; i < steps - 60; i++) {
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

    for (int i = 0; i < 15; i++) {
      digitalWrite(PULFL, HIGH);
      digitalWrite(PULRL, HIGH);
      digitalWrite(PULFR, HIGH);
      digitalWrite(PULRR, HIGH);
      delayMicroseconds(20);  // Normal delay for full speed
      digitalWrite(PULFL, LOW);
      digitalWrite(PULRL, LOW);
      digitalWrite(PULFR, LOW);
      digitalWrite(PULRR, LOW);
      delayMicroseconds(5500);
    }

    for (int i = 0; i < 15; i++) {
      digitalWrite(PULFL, HIGH);
      digitalWrite(PULRL, HIGH);
      digitalWrite(PULFR, HIGH);
      digitalWrite(PULRR, HIGH);
      delayMicroseconds(20);  // Normal delay for full speed
      digitalWrite(PULFL, LOW);
      digitalWrite(PULRL, LOW);
      digitalWrite(PULFR, LOW);
      digitalWrite(PULRR, LOW);
      delayMicroseconds(6000);
    }
  }

  delay(1500);
}

void rotateClockwise(int steps) {
  Serial.print("Rotating clockwise for ");
  Serial.print(steps);
  Serial.println(" steps");

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
    delayMicroseconds(6000);
  }

  delay(1500);
}

void rotateCounterClockwise(int steps) {
  Serial.print("Rotating counter-clockwise for ");
  Serial.print(steps);
  Serial.println(" steps");

  digitalWrite(DIRFL, HIGH);
  digitalWrite(DIRRL, HIGH);
  digitalWrite(DIRFR, HIGH);
  digitalWrite(DIRRR, HIGH);

  for (int i = 0; i < steps; i++) {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);  // Normal delay for full speed
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(6000);
  }


  delay(1500);
}


// In motor.cpp
void setupMotor() {
  // Your motor initialization code here
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

  Serial.println("Motor setup complete");
}
