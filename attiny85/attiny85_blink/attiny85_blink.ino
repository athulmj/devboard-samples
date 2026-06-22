// ATtiny85 onboard led Blink Program

void setup() {
  pinMode(1, OUTPUT); // Set Pin 0 as Output
}

void loop() {
  digitalWrite(1, HIGH); // Turn LED on
  delay(100);            // Wait 500ms
  digitalWrite(1, LOW);  // Turn LED off
  delay(100);            // Wait 500ms
}
