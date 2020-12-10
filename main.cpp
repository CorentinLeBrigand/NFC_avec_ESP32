/*///////////////////////////////////////////////////////////////////
* NFC avec ESP32
* Lecture de UID du badge NFC avec un module MFRC522 et un ESP32
* Le Brigand Corentin
* 10-12-2020
///////////////////////////////////////////////////////////////////*/

/*ajout des bibliotheques*/
#include <SPI.h>
#include <MFRC522.h>
#include <Arduino.h>

/*definition des constantes*/
#define pinRST 5  // pin RST du module RC522
#define pinSDA 4 // pin SDA du module RC522
#define VITESSE_TRANSMISSION 9600
#define TEMPS_ATTENTE 2000 //Temps d attente en ms

/*création des objets*/
MFRC522 rfid(pinSDA, pinRST);

void setup()
{
  Serial.begin(VITESSE_TRANSMISSION);

  /*Initialisation*/
  SPI.begin();
  rfid.PCD_Init();
}

void loop()
{
  /*Si carte detecte*/
  if (rfid.PICC_IsNewCardPresent())
  {
    /*On lit le contenu*/
    if (rfid.PICC_ReadCardSerial())
    {

      Serial.println("Voici l'UID de ce tag:");
      /*Affichage IDU*/
      for (byte i = 0; i < rfid.uid.size; i++)
      {
        Serial.print(rfid.uid.uidByte[i]);
      }
      Serial.println();
      delay(TEMPS_ATTENTE); //attente avant de relire
    }
  }
}