# ESP8866-RFID-Access-System
### **Overview**
This project implements a simple RFID-based access system using an **ESP8266 (NodeMCU)**, a **0.96" OLED display**, and **Green/Red LEDs**. It reads **RFID cards**, displays the **card UID** on the OLED, and indicates access status via LEDs.

#### **Features:**
- Displays UID on OLED screen
- Green LED indicates access granted
- Red LED indicates access denied
- Safe 3.3 V operation with 1 kΩ LED resistors
- Simple Arduino code for easy modification

#### **Components**
- ESP8266 NodeMCU
- 0.96" OLED Display (SSD1306, I2C)
- MFRC522 RFID Reader
- Green LED with 1 kΩ resistor
- Red LED with 1 kΩ resistor
- Jumper wires & breadboard

#### **Pin Connections**
- ***0.96" OLED (I2C)***
  
| OLED Pin | ESP8266 Pin |
| -------- | ----------- |
| VCC      | 3.3V        |
| GND      | GND         |
| SDA      | D2 (GPIO4)  |
| SCL      | D1 (GPIO5)  |

- ***RFID MFRC522 (SPI)***
  
| RFID Pin | ESP8266 Pin |
| -------- | ----------- |
| SDA      | D8 (GPIO15) |
| SCK      | D5 (GPIO14) |
| MOSI     | D7 (GPIO13) |
| MISO     | D6 (GPIO12) |
| RST      | D0 (GPIO16) |
| 3.3V     | 3.3V        |
| GND      | GND         |

- ***LEDs***
  
| LED   | ESP8266 Pin | Resistor |
| ----- | ----------- | -------- |
| Green | D1 (GPIO5)  | 1 kΩ     |
| Red   | D2 (GPIO4)  | 1 kΩ     |

#### **Installation**
1. Install Arduino IDE and **ESP8266 board package**.
2. Install required libraries via Library Manager:
   - Adafruit SSD1306
   - Adafruit GFX
   - MFRC522
3. Connect hardware according to the pin mapping above.
4. Open **card-scan-esp.ino** and upload to our ESP8266.

#### **Usage**
1. Power the ESP8266 via USB.
2. Open Serial Monitor at 9600 baud to view scanned card UIDs.
3. Scan an RFID card.
4. If the card UID matches the authorizedUID in the code, Green LED lights and OLED shows “**OK**”.
Otherwise, Red LED lights and OLED shows “**NO**”.
5. Change the authorizedUID variable in main.ino to set your card:
```String authorizedUID = "C3311025"; // Replace with your card UID```

#### **Notes**
- All modules must be powered from 3.3 V. Do not use 5V.
- **RST pin** should remain unconnected except via the onboard reset button.
- The LEDs are connected with 1 kΩ resistors for safe operation.
- No buzzer is included in this project.
