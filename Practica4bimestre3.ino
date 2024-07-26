/*
   Fundacion Kinal
   Centro educativo tecnico laboral Kinal
   Quinto perito
   Quinto electronica
   Codigo Tecnico: EB5BV
   Curso: Taller de electronica digital y reparacion de computadoras I
   Proyecto: practica 4
   Dev: Profe. Alejandro Lopez Navas
   Fecha: 25 de julio.
*/

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

#define LED_VERDE 2
#define LED_ROJO 3
#define BUZZER 4

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_ROJO, LOW);
  noTone(BUZZER);
}

void loop() {
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Read the UID of the card
  String tagUID = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    tagUID += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
    tagUID += String(mfrc522.uid.uidByte[i], HEX);
  }
  tagUID.toUpperCase();

  Serial.println("UID tag : " + tagUID);

  // Example UID for registered tag
  String registeredUID = "4312D41C";

  if (tagUID == registeredUID) {
    // Correct tag
    digitalWrite(LED_VERDE, HIGH);
    tone(BUZZER, 200);
    delay(4000); // Keep LED and buzzer active for 4 seconds
    digitalWrite(LED_VERDE, LOW);
    noTone(BUZZER);
  } else {
    // Incorrect tag
    digitalWrite(LED_ROJO, HIGH);
    tone(BUZZER, 400);
    delay(2000); // Keep LED and buzzer active for 2 seconds
    digitalWrite(LED_ROJO, LOW);
    noTone(BUZZER);
  }
  
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}
