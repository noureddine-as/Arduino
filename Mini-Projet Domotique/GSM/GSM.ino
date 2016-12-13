// Objectif: Recevoir un SMS qui contient #cmd1#cmd2# ... #cmdn*

#include <SoftwareSerial.h>

SoftwareSerial gsm(2, 3); // RX, TX
int commandes[13] = {0};

void setup() {
  pinMode(0, INPUT);
  pinMode(1, INPUT);

  Serial.begin(9600);
  gsm.begin(9600);

  /*
     NE PAS UTILISER LES PINS 0, 1, 2, 3, 9
     Pin 9 EST ATTACHE A PWRKEY (utilisé pour l'alimentation)
  */

  // ALLUMER LE MODULE
  /* pinMode(9, OUTPUT);
    digitalWrite(9, HIGH);
    delay(1000);// sur le datasheet 400µS est suffisante, mais par experience c pas le cas *_*
    digitalWrite(9, LOW);
  */
}

void loop() {
  gsm.write("AT+CMGL=\"ALL\"\r\n");
  String str = getMessage();
  //Serial.println(str);

  if (str != "no_cmd") // dans ce cas il y a des commandes à executer
  {
    extractCMD(str);
    doCMD();
    // Supprimer tout les messages
    gsm.write("AT+CMGDA=\"DEL ALL\"\r\n");
  }
  else
    Serial.println("Pas de commande a extraire");

  delay(1000);
}

void doCMD() {

  for (int i = 0; i < 13; i++)
  {
    if (commandes[i] == 0)
    {
      Serial.print("Fin de commandes\n");
      break;
    }
    else
    {
      if (commandes[i] >= 30 && commandes[i] < 60)
      {
        // On doit élliminer 0, 1, 2 , 3, 9
        //il s'agit d'allumer
        int pin = commandes[i] - 30;
        if (pin != 0 && pin != 1 && pin != 2 && pin != 3 && pin != 9)
        {
          digitalWrite(pin, HIGH);
          Serial.print(pin);
          Serial.println("    >>    ON");
        }
        else
        {
          Serial.println("Impossible d'allumer ce pin!!");
        }
      }
      else if (commandes[i] >= 60)
      {
        int pin = commandes[i] - 60;
        if (pin != 0 && pin != 1 && pin != 2 && pin != 3 && pin != 9)
        {
          digitalWrite(pin, LOW);
          Serial.print(pin);
          Serial.println("    >>    OFF");
        }
        else
        {
          Serial.println("Impossible d'éteindre ce pin!!");
        }
      }
    }
  }
}

void extractCMD(String msg) //2ème solution
{
  for (int k = 0; k < 13; k++)
    commandes[k] = 0;

  int dizaine, unitee;

  int i = 0; int j = 0;
  for (int i = 0; i < msg.length() ; i++)
  {
    dizaine = (int)msg.charAt(i) - 48;
    unitee = (int)msg.charAt(i + 1) - 48;
    // char '1' --> 49 en ascii on doit retrancher 48
    commandes[j] =  10 * dizaine + unitee;
    j++;
    i += 2;
  }
}

String getMessage()
{
  if (gsm.find("#") == true)
  {
    boolean b = true;
    String msg = "";
    while (b)
    {
      if (gsm.available()) {
        char c = gsm.read();
        if (c == '*')
          b = false;
        else
          msg += c;
      }
    }
    return msg;
  }
  else
  {
    return "no_cmd";
  }
}

