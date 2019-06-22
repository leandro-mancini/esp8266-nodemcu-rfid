#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN D4
#define RST_PIN D2
#define LED_RED D1
#define LED_GREEN D3

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();

  rfid.PCD_Init();

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  Serial.println("UID de leitura de RFID");
}

void loop() {
  digitalWrite(LED_RED, HIGH);
  
  if (rfid.PICC_IsNewCardPresent()) {
    if (rfid.PICC_ReadCardSerial()) {
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_GREEN, HIGH);
      
      Serial.print("TAG UID: ");

      for (byte i = 0; i < rfid.uid.size; i++) {
        Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(rfid.uid.uidByte[i], HEX);
      }

      Serial.println();

      rfid.PICC_HaltA();

      delay(500);

      digitalWrite(LED_GREEN, LOW);
    }
  }
}
