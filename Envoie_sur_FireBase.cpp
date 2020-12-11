/*/////////////////////////////////////////////////////////////////////////////////////////////////
* NFC avec ESP32 et FireBase
* Envoie de UID du badge NFC sur une base de donnée FireBase avec un module MFRC522 et un ESP32
* Connection en Wifi
* Le Brigand Corentin
* 11-12-2020
/////////////////////////////////////////////////////////////////////////////:///////////////////*/

/*ajout des bibliotheques*/
#include <SPI.h>
#include <MFRC522.h>
#include "FirebaseESP32.h"
#include "WiFi.h"

/*definition des constantes*/
#define FIREBASE_HOST "XXXX"                          // adresse de la BDD sur le cloud 
#define FIREBASE_AUTH "XXXX"                          // cle d'authentification firebase
#define WIFI_SSID "XXXX"                              // nom du wifi
#define WIFI_PASSWORD "XXXX"                          // mot de passe du wifi
#define pinRST 5                                      // pin RST du module RC522
#define pinSDA 4                                      // pin SDA du module RC522
#define VITESSE_TRANSMISSION 9600
#define TEMPS_ATTENTE 2000                            //Temps d attente en ms

/*création des objets*/
FirebaseData firebaseData;
FirebaseJson Json; 
MFRC522 rfid(pinSDA, pinRST);

void setup()
{
  Serial.begin(VITESSE_TRANSMISSION);

  /*Initialisation*/
  SPI.begin();
  rfid.PCD_Init();

  /*Connection wifi*/
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);                  // attribution du reseau et de sa clé WPA 
  while (WiFi.status()!= WL_CONNECTED){                 //tant que la connexion n'est pas établie on reste dans la boucle 
   delay(500);
   Serial.print(".");
  }                                                     // lorsque la connexion est effectué 
  Serial.println("wifi connected -> ip adress : "); 
  Serial.println(WiFi.localIP());                       // affichage de l'adresse IP

  /*Connection a la base de donnée*/
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);          // initialisation de la BDD avec son adresse et le password
  Firebase.reconnectWiFi(true); 
}
void loop()
{
  /*Si carte detecte*/
  if (rfid.PICC_IsNewCardPresent())
  {
    /*On lit le contenu*/
    if (rfid.PICC_ReadCardSerial())
    {
      String UID = "";
      for (byte i = 0; i < rfid.uid.size; i++)
      {
        UID = UID + rfid.uid.uidByte[i];                  //création de la varible UID
      }

      /*Affichage UID*/
      Serial.println("Voici l'UID de ce tag:");
      Serial.println(UID);

      /*envoie de UID sur la base de donnée*/
      Firebase.setString(firebaseData,"test_Nfn", UID);

      delay (2000);                                        //attente avant de relire
    }
  }
}
