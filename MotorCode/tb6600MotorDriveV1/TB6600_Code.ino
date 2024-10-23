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
