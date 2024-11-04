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

void setup() {
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
}

void loop() {

  moveForward(48);

  delay(1500);
} 

int convertInchToStep(int inches){
  //1 rotation of 97mm wheel is ~12 inches. 200 steps per rotation, 12/200 = 0.06 inches per step. ~17 steps per inch.
  int steps = inches * 17;
  return steps
}

int convertDegreesToSteps(int degrees){
  int steps = degress * 17;
  return steps;
}
//FORWARD----------------------------------------------------------------------------------------------------------
void moveForward(int inches){
  int steps = convertInchToStep(inches);
  
  digitalWrite(DIRFL, LOW);
  digitalWrite(DIRRL, LOW);
  digitalWrite(DIRFR, HIGH);
  digitalWrite(DIRRR, HIGH);

  for (int i = 0; i < 35; i++) // 1 rotation
  {
    
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

  for (int i = 0; i < 25; i++) // 1 rotation
  {
    
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(2200);
  }

  for (int i = 0; i < 25; i++) // 1 rotation
  {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(1900);
  }

  for (int i = 0; i < steps + 2 - 170; i++) // 1 rotation
  {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(1700);
  }

  for (int i = 0; i < 25; i++) // 1 rotation
  {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(1900);
  }

  for (int i = 0; i < 25; i++) // 1 rotation
  {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(2200);
  }

  for (int i = 0; i < 35; i++) // 1 rotation
  {
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
//BACKWARD----------------------------------------------------------------------------------------------------------
void moveBackward(int inches){
  int steps = convertInchToStep(inches);
  
  digitalWrite(DIRFL, HIGH);
  digitalWrite(DIRRL, HIGH);
  digitalWrite(DIRFR, LOW);
  digitalWrite(DIRRR, LOW);

  for (int i = 0; i < 35; i++) // 1 rotation
  {
    
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

  for (int i = 0; i < 25; i++) // 1 rotation
  {
    
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(2200);
  }

  for (int i = 0; i < 25; i++) // 1 rotation
  {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(1900);
  }

  for (int i = 0; i < steps + 2 - 170; i++) // 1 rotation
  {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(1700);
  }

  for (int i = 0; i < 25; i++) // 1 rotation
  {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(1900);
  }

  for (int i = 0; i < 25; i++) // 1 rotation
  {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(2200);
  }

  for (int i = 0; i < 35; i++) // 1 rotation
  {
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
//LEFT----------------------------------------------------------------------------------------------------------
void translateLeft(int inches){
  int steps = convertInchToStep(inches);
  
  digitalWrite(DIRFL, HIGH);
  digitalWrite(DIRRL, LOW);
  digitalWrite(DIRFR, HIGH);
  digitalWrite(DIRRR, LOW);

  for (int i = 0; i < 35; i++) // 1 rotation
  {
    
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

  for (int i = 0; i < 25; i++) // 1 rotation
  {
    
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(2200);
  }

  for (int i = 0; i < 25; i++) // 1 rotation
  {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(1900);
  }

  for (int i = 0; i < steps + 2 - 170; i++) // 1 rotation
  {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(1700);
  }

  for (int i = 0; i < 25; i++) // 1 rotation
  {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(1900);
  }

  for (int i = 0; i < 25; i++) // 1 rotation
  {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(2200);
  }

  for (int i = 0; i < 35; i++) // 1 rotation
  {
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
//RIGHT----------------------------------------------------------------------------------------------------------
void translateRight(int inches){
  int steps = convertInchToStep(inches);
  
  digitalWrite(DIRFL, LOW);
  digitalWrite(DIRRL, HIGH);
  digitalWrite(DIRFR, LOW);
  digitalWrite(DIRRR, HIGH);

  for (int i = 0; i < 35; i++) // 1 rotation
  {
    
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

  for (int i = 0; i < 25; i++) // 1 rotation
  {
    
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(2200);
  }

  for (int i = 0; i < 25; i++) // 1 rotation
  {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(1900);
  }

  for (int i = 0; i < steps + 2 - 170; i++) // 1 rotation
  {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(1700);
  }

  for (int i = 0; i < 25; i++) // 1 rotation
  {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(1900);
  }

  for (int i = 0; i < 25; i++) // 1 rotation
  {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(2200);
  }

  for (int i = 0; i < 35; i++) // 1 rotation
  {
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
//ROTATION COUNTER-CLOCKWISE----------------------------------------------------------------------------------------------------------
void rotateCounterClockwise(int degrees){
  int steps = convertDegreesToSteps(degrees);
  
  digitalWrite(DIRFL, HIGH);
  digitalWrite(DIRRL, HIGH);
  digitalWrite(DIRFR, HIGH);
  digitalWrite(DIRRR, HIGH);

  for (int i = 0; i < 35; i++) // 1 rotation
  {
    
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

  for (int i = 0; i < 25; i++) // 1 rotation
  {
    
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(2200);
  }

  for (int i = 0; i < 25; i++) // 1 rotation
  {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(1900);
  }

  for (int i = 0; i < steps + 2 - 170; i++) // 1 rotation
  {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(1700);
  }

  for (int i = 0; i < 25; i++) // 1 rotation
  {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(1900);
  }

  for (int i = 0; i < 25; i++) // 1 rotation
  {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(2200);
  }

  for (int i = 0; i < 35; i++) // 1 rotation
  {
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

//ROTATION CLOCKWISE----------------------------------------------------------------------------------------------------------
void rotateClockwise(int degrees){
  int steps = convertDegreesToSteps(degrees);
  
  digitalWrite(DIRFL, LOW);
  digitalWrite(DIRRL, LOW);
  digitalWrite(DIRFR, LOW);
  digitalWrite(DIRRR, LOW);

  for (int i = 0; i < 35; i++) // 1 rotation
  {
    
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

  for (int i = 0; i < 25; i++) // 1 rotation
  {
    
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(2200);
  }

  for (int i = 0; i < 25; i++) // 1 rotation
  {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(1900);
  }

  for (int i = 0; i < steps + 2 - 170; i++) // 1 rotation
  {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(1700);
  }

  for (int i = 0; i < 25; i++) // 1 rotation
  {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(1900);
  }

  for (int i = 0; i < 25; i++) // 1 rotation
  {
    digitalWrite(PULFL, HIGH);
    digitalWrite(PULRL, HIGH);
    digitalWrite(PULFR, HIGH);
    digitalWrite(PULRR, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    digitalWrite(PULRL, LOW);
    digitalWrite(PULFR, LOW);
    digitalWrite(PULRR, LOW);
    delayMicroseconds(2200);
  }

  for (int i = 0; i < 35; i++) // 1 rotation
  {
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