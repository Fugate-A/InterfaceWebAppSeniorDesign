int PULFL = 3; //define Pulse pin
int DIRFL = 1; //define Direction pin
int ENAFL = 0; //define Enable Pin
int PULRL = 5;
int DIRRL = 4;
int ENARL = 0;
int PULFR = 17;
int DIRFR = 16;
int ENAFR = 0;
int PULRR = 22;
int DIRRR = 21;
int ENARR = 0;
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

  moveForward(400);

  delay(1000);
}


void moveFLForward(int steps){
  digitalWrite(DIRFL, LOW);

  for (int i = 0; i < 35; i++) // 1 rotation
  {
    
    digitalWrite(PULFL, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    delayMicroseconds(2200);
  }

  for (int i = 0; i < 25; i++) // 1 rotation
  {
    
    digitalWrite(PULFL, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    delayMicroseconds(1800);
  }

  for (int i = 0; i < 25; i++) // 1 rotation
  {
    
    digitalWrite(PULFL, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    delayMicroseconds(1400);
  }

  for (int i = 0; i < steps + 2 - 170; i++) // 1 rotation
  {
    digitalWrite(PULFL, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    delayMicroseconds(800);
  }

  for (int i = 0; i < 25; i++) // 1 rotation
  {
    
    digitalWrite(PULFL, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    delayMicroseconds(1400);
  }

  for (int i = 0; i < 25; i++) // 1 rotation
  {
    
    digitalWrite(PULFL, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    delayMicroseconds(1800);
  }

  for (int i = 0; i < 35; i++) // 1 rotation
  {
    
    digitalWrite(PULFL, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    delayMicroseconds(2200);
  }
}

void moveFLBackward(int steps){
  digitalWrite(DIRFL, HIGH);
  for (int i = 0; i < 35; i++) // 1 rotation
  {
    
    digitalWrite(PULFL, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    delayMicroseconds(2200);
  }

  for (int i = 0; i < 25; i++) // 1 rotation
  {
    
    digitalWrite(PULFL, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    delayMicroseconds(1800);
  }

  for (int i = 0; i < 25; i++) // 1 rotation
  {
    
    digitalWrite(PULFL, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    delayMicroseconds(1400);
  }


  for (int i = 0; i < steps - 170; i++) // 1 rotation
  {
    
    digitalWrite(PULFL, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    delayMicroseconds(800);
  }

  for (int i = 0; i < 25; i++) // 1 rotation
  {
    
    digitalWrite(PULFL, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    delayMicroseconds(1400);
  }

  for (int i = 0; i < 25; i++) // 1 rotation
  {
    
    digitalWrite(PULFL, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    delayMicroseconds(1800);
  }

  for (int i = 0; i < 35; i++) // 1 rotation
  {
    
    digitalWrite(PULFL, HIGH);
    delayMicroseconds(20);
    digitalWrite(PULFL, LOW);
    delayMicroseconds(2200);
  }
}

void moveForward(int steps){
  digitalWrite(DIRRL, LOW);
  digitalWrite(DIRFL, LOW);
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
    delayMicroseconds(1800);
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
    delayMicroseconds(1400);
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
    delayMicroseconds(800);
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
    delayMicroseconds(1400);
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
    delayMicroseconds(1800);
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
    delayMicroseconds(2200);
  }
}
