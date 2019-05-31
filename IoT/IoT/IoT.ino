
short pin = 3;
 
void setup() {
  Serial.begin(9600);
  pinMode(pin, OUTPUT);
  Serial.print("Ready...");
}
 
void loop() {
  char c = Serial.read();
  if (c == 'O') {
    digitalWrite(pin, HIGH);
  }
  if (c == 'F') {
    digitalWrite(pin, LOW);
  }
}
