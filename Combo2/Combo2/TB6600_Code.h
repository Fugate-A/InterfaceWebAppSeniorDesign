#ifndef TB6600_CODE_H
#define TB6600_CODE_H

// Function declarations for motor control
void setupMotor();
void loopMotor();
void moveForward(int steps);
void moveBackward(int steps);
void translateLeft(int steps);
void translateRight(int steps);
void rotateClockwise(int steps);
void rotateCounterClockwise(int steps);
void setupMotor();

#endif