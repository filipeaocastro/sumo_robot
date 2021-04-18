void setup() {
  pinMode(5, INPUT);
  pinMode(13, OUTPUT);
}

void loop() {
if(digitalRead(5) == HIGH)
{
  digitalWrite(13, HIGH);
}
else
{
  digitalWrite(13, LOW);
}
 
}
