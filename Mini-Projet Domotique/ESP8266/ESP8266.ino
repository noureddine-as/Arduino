#include <SoftwareSerial.h>

SoftwareSerial esp(2,3);

void setup() {
 esp.begin(112500);
 Serial.begin(112500);
 pinMode(10, OUTPUT);
 delay(10000);
}

void loop() {
  delay(5000);
  digitalWrite(10, LOW);

  // Etablir une connexion TCP
  startTCP();
  clear_serial();
  
  // Envoyer une demande d'envoi
  sendReq();
  clear_serial();

  // Génération de nombres aléatoires et de la température
  int x,y,z;
  x = getTemp();
  y = 1 + (rand()%30);
  z = 1 + (rand()%30);

  // Envoi des nombres générés
  sendCMD(x, y, z);

  Serial.print("Temperature : ");
  Serial.print(x);
  Serial.println(" °C");
  Serial.println("-------------------------------------");

  clear_serial();
  // Fermer la connexion TCP
  closeTCP();
  clear_serial();
  
  digitalWrite(10, HIGH);
  // Attente pendant 5 secondes
  delay(5000); 
}


int getTemp()
{
  // Calcul de la température
  int val = analogRead(0);
  // Pour le LM35:  10mV --->> 1°C
  float mv = (val / 1024.0) * 5000;
  return int(mv / 10);
}


void clear_serial()
{
  while(esp.available())
    esp.read();
}

void startTCP()
{
  esp.print("AT+CIPSTART=\"TCP\",\"184.106.153.149\",80\r\n");
}

void closeTCP()
{
  esp.print("AT+CIPCLOSE\r\n");
}

void sendReq()
{
    esp.print("AT+CIPSEND=100\r\n");
}

void sendCMD(int val, int val1, int val2)
{
    String cmd = "GET https://api.thingspeak.com/update?api_key=90AQPXEAO4B70153&field1=";
    cmd += val;
    cmd += "&field2=";
    cmd += val1;
    cmd += "&field3=";
    cmd += val2;
    cmd += "\r\n\r\n";
    esp.print(cmd);
}


