int PULFL = 4; //define Pulse pin
int DIRFL = 5; //define Direction pin
int ENAFL = 1; //define Enable Pin
void setup() {
  pinMode (PULFL, OUTPUT);
  pinMode (DIRFL, OUTPUT);
  pinMode (ENAFL, OUTPUT);
}

void loop() {
  moveFLForward(200);

  delay(1000);

  moveFLBackward(200);

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