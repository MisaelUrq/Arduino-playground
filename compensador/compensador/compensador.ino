int analogo = 3;     // potentiometer wiper (middle terminal) connected to analog pin 3

void setup()
{
  Serial.begin(9600);
  pinMode (2, OUTPUT);
  pinMode (4, OUTPUT); //  setup serial
}
void loop()
{
  int val = analogRead(analogo);     // read the input pin
  float voltaje = val * 0.0048;
  Serial.print("voltaje");
  Serial.print(voltaje);
  
  if (voltaje >= 3.6)
  {
    digitalWrite(2, LOW);
    digitalWrite(4, HIGH);
    Serial.println(", resta");
  }
  else if (voltaje <= 2.8)
  {
    Serial.println(", suma");
    digitalWrite(2, HIGH);
    digitalWrite(4, LOW);
  }
  else // if (voltaje >= 2.8 && voltaje <= 3.6)
  {
    Serial.println(", Nada");
    digitalWrite(2, LOW);
    digitalWrite(4, LOW);
  }
}
