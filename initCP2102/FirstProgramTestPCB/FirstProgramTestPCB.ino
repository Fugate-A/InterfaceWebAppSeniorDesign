const int ledPin = 27;

void setup() {
  // put your setup code here, to run once:
    pinMode(ledPin, OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly:

  // Turn the LED on
  digitalWrite(ledPin, HIGH);
  delay(1000); // Wait for 1 second

  // Turn the LED off
  digitalWrite(ledPin, LOW);
  delay(1000); // Wait for 1 second

}