#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ===== OLED CONFIG =====
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ===== RFID CONFIG =====
#define SS_PIN  D8
#define RST_PIN D0
MFRC522 mfrc522(SS_PIN, RST_PIN);

// ===== LED PINS =====
#define GREEN_LED D3   // GPIO5
#define RED_LED   D4   // GPIO4

// ===== AUTHORIZED UID (CHANGE THIS) =====
String authorizedUID = "C3311025";

void setup() {
  // GPIO setup
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);

  // Serial
  Serial.begin(9600);

  // OLED init
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed");
    while (true);
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println("RFID");
  display.println("READY");
  display.display();

  // RFID init
  SPI.begin();
  mfrc522.PCD_Init();

  delay(1000);
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;

  // Read UID
  String uid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    uid += String(mfrc522.uid.uidByte[i], HEX);
  }
  uid.toUpperCase();

  Serial.print("UID: ");
  Serial.println(uid);

  // Show UID
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println("UID:");
  display.println(uid);
  display.display();

  delay(700);

  // Access check
  if (uid == authorizedUID) {
    accessGranted();
  } else {
    accessDenied();
  }

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
  delay(1000);
}

void accessGranted() {
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);

  display.clearDisplay();
  display.setTextSize(3);
  display.setCursor(20, 20);
  display.println("OK");
  display.display();

  delay(1200);
  digitalWrite(GREEN_LED, LOW);
}

void accessDenied() {
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);

  display.clearDisplay();
  display.setTextSize(3);
  display.setCursor(0, 20);
  display.println("NO");
  display.display();

  delay(1200);
  digitalWrite(RED_LED, LOW);
}