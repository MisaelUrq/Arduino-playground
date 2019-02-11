byte analogo = 3;       // potentiometer wiper (middle terminal) connected to analog pin 3
byte val = 0;           // variable to store the value read
float voltaje=0;
float voltajeTem=0;
float temperatura=0;

byte ventilador_pin = 4;
byte foco_pin       = 3;

void setup()
{
  Serial.begin(9600);
  pinMode (foco_pin,OUTPUT);
  pinMode (ventilador_pin,OUTPUT);//  setup serial
}

void loop()
{
  val = analogRead(analogo);     // read the input pin
  voltaje=val*0.0048;
  voltajeTem=voltaje-0.75;
  temperatura=(voltaje/0.010);
  Serial.print("Temperatura: ");
  Serial.print(temperatura);

  if(temperatura>=50)
  {
    digitalWrite(foco_pin,HIGH);
    digitalWrite(ventilador_pin,HIGH);  //Ventilador
    Serial.print(", ");
    Serial.println("Alta");
  }
  else if(temperatura<=35)
  {
    Serial.print(", ");
    Serial.println("Baja");
    digitalWrite(foco_pin,HIGH);
    digitalWrite(ventilador_pin,LOW);
  }
  else
  {
    Serial.print(", ");
    Serial.println("Normal");
    digitalWrite(foco_pin,LOW);
    digitalWrite(ventilador_pin,LOW);
  }
  delay(5000);
}
