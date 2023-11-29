#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9    // Configurable, typically a pin connected to RST
#define SS_PIN 10    // Configurable, typically a pin connected to SDA/SS

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
  Serial.begin(9600);   // Initialize serial communication
  SPI.begin();          // Initiate SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522

  //Serial.println("RFID-RC522 Test");
}

void loop() {

  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    String cardUID; // Initialize an empty String to store the card UID
    //delay(600);
    // Concatenate card UID bytes into a String
    for (byte i = 0; i < mfrc522.uid.size; ++i) {
      if (mfrc522.uid.uidByte[i] < 0x10) {
        cardUID += "0";
      }
      cardUID += String(mfrc522.uid.uidByte[i], HEX);
    }

    // Envoyer les données avec un caractère de fin de ligne
    cardUID += "\n"; // Ajout du caractère de fin de ligne

    // Convertir la chaîne String en un tableau de caractères (const char*)
    const char* cardData = cardUID.c_str();

    // Envoyer les données via Serial.write
    Serial.println(cardUID); // Envoi du tableau de caractères via Serial.write
    delay(300);

    // Halt PICC
    mfrc522.PICC_HaltA();
    // Stop encryption on PCD
    mfrc522.PCD_StopCrypto1();
  }
}
