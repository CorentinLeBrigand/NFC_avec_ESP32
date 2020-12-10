/*///////////////////////////////////////////////////////////////////
* NFC avec ESP32
* Lecture de UID du badge NFC avec un module MFRC522 et un ESP32
* Le Brigand Corentin
* 10-12-2020
///////////////////////////////////////////////////////////////////*/

Matériels
  -ESP 32
  -MFRC522
  -Badge NFC
  
Adressage
ESP32    <--->     MFRC522
GPIO4              SDA
GPIO18             SCK
GPIO23             MOSI
GPIO19             MISO
Pas connectée      IRQ
GND                GND
GPIO5              RST
3.3V               3.3V
