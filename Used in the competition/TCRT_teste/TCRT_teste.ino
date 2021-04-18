#define FD1 A5


void setup()
{
    Serial.begin(9600); 
}

void loop()
{
    Serial.println(analogRead(FD1));
    delay(500);
}