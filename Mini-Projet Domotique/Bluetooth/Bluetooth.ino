
void setup() {
  Serial.begin(38400);

    for(int i = 2; i <= 13; i++)
    {
    pinMode(i, OUTPUT);
    }

}

void loop() {
  while ( Serial.available() > 0)
  {
    byte c = Serial.read();
   // Serial.println(c);

    if (c >= 32 && c <= 61 )
    {
      // Il s'agit d'allumage
      digitalWrite(c - 30, HIGH);

      Serial.print(c - 30 );//, DEC);
      Serial.println(" >> ON");

    }
    else if (c >= 62 && c <= 73 )
    {
      // Il s'agit d'eteindre le pin (c - 60)
      digitalWrite(c - 60, LOW);
      Serial.print(c - 60 );//, DEC);
      Serial.println(" >> OFF");

    }
  }

}
