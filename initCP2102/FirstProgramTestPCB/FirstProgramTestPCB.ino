const int ledPin = 2;

void setup() {
  // put your setup code here, to run once:
    pinMode(ledPin, OUTPUT);

    Serial.begin( 115200 );


}

void loop() {
  // put your main code here, to run repeatedly:

  // Turn the LED on
  digitalWrite(ledPin, HIGH);
  delay(1000); // Wait for 1 second

  // Turn the LED off
  digitalWrite(ledPin, LOW);
  delay(1000); // Wait for 1 second
  
  Serial.println("We are here");

}