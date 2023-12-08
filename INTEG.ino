#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

#define RST_PIN 9    // Configurable, typically a pin connected to RST
#define SS_PIN 10    // Configurable, typically a pin connected to SDA/SS

LiquidCrystal_I2C lcd(0x27, 16, 2);

int attempts = 0;
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
  Serial.begin(9600);   // Initialize serial communication
  SPI.begin();          // Initiate SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.clear();
}

void loop() {
lcd.clear(); // Clear LCD before displaying new data

    lcd.setCursor(0, 0);
    lcd.print("swipe card");
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    String cardUID; // Initialize an empty String to store the card UID
    for (byte i = 0; i < mfrc522.uid.size; ++i) {
      if (mfrc522.uid.uidByte[i] < 0x10) {
        cardUID += "0";
      }
      cardUID += String(mfrc522.uid.uidByte[i], HEX);
    }

    cardUID += "\n";

    const char* cardData = cardUID.c_str();

    Serial.println(cardUID);
    delay(300);

    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();

    
 if(cardUID=="839d82c5\n")
  {
    lcd.clear(); // Clear LCD before displaying new data

    lcd.setCursor(0, 0);
    lcd.print("connected");

  }
  else
  {
    lcd.clear(); // Clear LCD before displaying new data

    lcd.setCursor(0, 0);
    lcd.print("not connected");
  }
    if (Serial.available() > 0) {
      String marque = Serial.readStringUntil('\n');

      char access = '\0';

      if (marque == "<<EMPTY>>") {
        access = '0'; // Empty string
      } else {
        access = '1'; // Non-empty string
      }

      if (access == '1') {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("nom :");
        lcd.setCursor(0, 1);
        lcd.print(marque); // Directly print the string without conversion
        delay(5000);
        attempts = 0;
        lcd.clear();
      } else if (access == '0') {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("INTROUVABLE");
        attempts += 1;

        lcd.setCursor(0, 1);
        String str2 = "left: " + String(3 - attempts);
        lcd.print(str2);
        delay(800);
        if (attempts != 3) {
          // Show remaining attempts if not yet 3
          lcd.setCursor(0, 1);
          lcd.print(str2);
        } else if (attempts == 3) {
          int chrono = 10;
          while (chrono != 0) {
            lcd.clear();
            lcd.setCursor(8, 0);
            lcd.print(chrono);
            chrono -= 1;
            delay(1000);
          }
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Try again...");
          attempts = 0;
        }
        delay(1000); // Delay added for readability
        lcd.clear();
      }
    }
  }
  delay(1000); 
}
