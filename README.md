# BMP280-and-SH1106-OLED-Display-with-Arduino-Nano

This project demonstrates how to read temperature, pressure, and altitude data from a BMP280 sensor and display it on an SH1106 OLED using an Arduino Nano.

## Components
1. Arduino Nano
2. BMP280 Sensor
3. SH1106 OLED Display
4. Jumper Wires
5. Breadboard (optional)

## Libraries Used
1. Adafruit BMP280 Library
2. U8glib Library

## Wiring Diagram
### BMP280 to Arduino Nano
VCC to 3.3V

GND to GND

SCL to A5 (SCL)

SDA to A4 (SDA)

### SH1106 OLED to Arduino Nano
VCC to 3.3V (or 5V, depending on your module)

GND to GND

SCL to A5 (SCL)

SDA to A4 (SDA)

## Setup Instructions

1. Install Libraries:

- Open Arduino IDE.
- Go to Sketch -> Include Library -> Manage Libraries.
- Install Adafruit BMP280 Library and U8glib.

2. Wiring:

    ![image](https://github.com/2602NAMAN/BMP280-and-SH1106-OLED-Display-with-Arduino-Nano/assets/113130600/ab3ae171-edb1-464a-b24a-7ada596def56)

- Connect the BMP280 and SH1106 OLED to the Arduino Nano as per the wiring diagram.

3. Upload Code:

- Open the provided code in Arduino IDE.
- Select the correct board and port.
- Upload the code to the Arduino Nano.

## On display output
![WhatsApp Image 2024-06-05 at 7 01 25 PM](https://github.com/2602NAMAN/BMP280-and-SH1106-OLED-Display-with-Arduino-Nano/assets/113130600/175e33fd-aeb7-4682-9ace-a1b14f9b7d3a)

## Usage
Once the code is uploaded, the Arduino Nano will read the sensor data and display the temperature, pressure, and altitude on the SH1106 OLED display.

Feel free to customize it further according to your needs!

