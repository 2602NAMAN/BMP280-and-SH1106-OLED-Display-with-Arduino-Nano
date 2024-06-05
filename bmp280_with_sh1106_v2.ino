#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <U8glib.h>

// Create BMP280 object
Adafruit_BMP280 bmp; 

// Create U8GLIB object for SH1106
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);

// Temperture logo for splashscreen
const uint8_t temp_logo[] U8G_PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x46, 0x00, 0x00, 0x00, 0x00, 0x82, 0x00, 0x00, 0x00, 0x00, 
	0x82, 0x00, 0x00, 0x00, 0x00, 0x82, 0x00, 0x00, 0x00, 0x00, 0x82, 0xe0, 0x00, 0x00, 0x00, 0x82, 
	0x00, 0x00, 0x00, 0x00, 0x82, 0x00, 0x00, 0x00, 0x00, 0x82, 0x00, 0x00, 0x00, 0x00, 0x82, 0xf8, 
	0x00, 0x00, 0x00, 0x82, 0x00, 0x00, 0x00, 0x00, 0x92, 0x00, 0x00, 0x00, 0x00, 0xba, 0xe0, 0x00, 
	0x00, 0x00, 0xba, 0x00, 0x00, 0x00, 0x00, 0xba, 0x00, 0x00, 0x00, 0x00, 0xba, 0xf8, 0x00, 0x00, 
	0x00, 0xba, 0x00, 0x00, 0x00, 0x00, 0xba, 0x00, 0x00, 0x00, 0x00, 0xba, 0xe0, 0x00, 0x00, 0x00, 
	0xba, 0x00, 0x00, 0x00, 0x00, 0xba, 0x00, 0x00, 0x00, 0x00, 0xba, 0x00, 0x00, 0x00, 0x01, 0xbb, 
	0x00, 0x00, 0x00, 0x02, 0x38, 0x80, 0x00, 0x00, 0x02, 0x7c, 0x40, 0x00, 0x00, 0x04, 0xfe, 0x40, 
	0x00, 0x00, 0x04, 0xff, 0x40, 0x00, 0x00, 0x04, 0xff, 0x00, 0x00, 0x00, 0x04, 0xff, 0x40, 0x00, 
	0x00, 0x04, 0xfe, 0x40, 0x00, 0x00, 0x02, 0x7e, 0x40, 0x00, 0x00, 0x02, 0x38, 0x80, 0x00, 0x00, 
	0x01, 0x81, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Pressure logo for splashscreen
const uint8_t pres_logo[] U8G_PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x03, 0xff, 0xc0, 0x00, 0x00, 
	0x1f, 0x81, 0xf8, 0x00, 0x00, 0x38, 0x00, 0x1c, 0x00, 0x00, 0xf1, 0x99, 0x8f, 0x00, 0x01, 0xc8, 
	0x99, 0x13, 0x80, 0x03, 0x88, 0x99, 0x11, 0xc0, 0x07, 0x04, 0x18, 0x20, 0xe0, 0x06, 0x46, 0x00, 
	0x62, 0x60, 0x0c, 0x62, 0x00, 0x44, 0x30, 0x1c, 0x00, 0x18, 0x00, 0x18, 0x1b, 0x00, 0x18, 0x00, 
	0xd8, 0x11, 0xc0, 0x18, 0x03, 0x88, 0x30, 0x60, 0x18, 0x06, 0x0c, 0x30, 0x00, 0x18, 0x00, 0x0c, 
	0x37, 0x00, 0x18, 0x00, 0xec, 0x60, 0x00, 0x18, 0x00, 0x06, 0x60, 0x00, 0x3c, 0x00, 0x06, 0x60, 
	0x00, 0x66, 0x01, 0xe6, 0x67, 0x80, 0x66, 0x01, 0xe6, 0x60, 0x00, 0x3e, 0x00, 0x06, 0x60, 0x00, 
	0x18, 0x00, 0x06, 0x37, 0x00, 0x18, 0x00, 0xe4, 0x34, 0x00, 0x18, 0x00, 0x2c, 0x30, 0x60, 0x00, 
	0x06, 0x0c, 0x10, 0xc0, 0x00, 0x03, 0x08, 0x1b, 0x00, 0x00, 0x00, 0xd8, 0x1c, 0x00, 0x00, 0x00, 
	0x18, 0x0c, 0x03, 0xff, 0xc0, 0x30, 0x06, 0x00, 0x00, 0x00, 0x60, 0x07, 0x00, 0x00, 0x00, 0xe0, 
	0x03, 0x80, 0xff, 0x81, 0xc0, 0x01, 0xc0, 0x00, 0x03, 0x80, 0x00, 0xf0, 0x00, 0x07, 0x00, 0x00, 
	0x38, 0x00, 0x1c, 0x00, 0x00, 0x1f, 0x80, 0xf8, 0x00, 0x00, 0x03, 0xff, 0xc0, 0x00, 0x00, 0x00, 
	0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Altitude logo for splashscreen
const uint8_t alt_logo[] U8G_PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x03, 0x80, 
	0x00, 0x00, 0x00, 0x07, 0xc0, 0x01, 0xfc, 0x00, 0x07, 0xc0, 0x00, 0xfc, 0x00, 0x0e, 0xe0, 0x00, 
	0x30, 0x00, 0x0c, 0x70, 0x00, 0x30, 0x00, 0x1c, 0x70, 0x00, 0x78, 0x00, 0x38, 0x38, 0xc0, 0x30, 
	0x00, 0x38, 0x38, 0xe0, 0x30, 0x00, 0x70, 0x1d, 0xe0, 0x30, 0x00, 0x70, 0x1d, 0xf0, 0x78, 0x00, 
	0xe4, 0x4f, 0xf0, 0x30, 0x00, 0xfe, 0xff, 0x38, 0x30, 0x01, 0xff, 0xff, 0x18, 0x30, 0x03, 0xff, 
	0xfe, 0x1c, 0x30, 0x03, 0xff, 0xfe, 0x0e, 0x78, 0x07, 0xff, 0xff, 0xfe, 0x30, 0x07, 0xff, 0xff, 
	0xff, 0x30, 0x0f, 0xff, 0xff, 0xff, 0x30, 0x0f, 0xff, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff, 
	0xb0, 0x1f, 0xff, 0xff, 0xff, 0xf0, 0x3f, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0xff, 0xff, 0xff, 0xfc, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

//Splashscreen
void displaySplashScreen() 
{
  // Show splashscreen for 3 seconds
  u8g.firstPage();
  do {
    // Draw logo bitmap at (48, 16)
    u8g.drawBitmapP(2, 12, 40/8, 40, temp_logo);
    u8g.drawBitmapP(42, 12, 40/8, 40, pres_logo);
    u8g.drawBitmapP(84, 12, 40/8, 40, alt_logo);

    u8g.setContrast(255); // Set the display brightness (0-255)

  } while (u8g.nextPage());

  delay(2000);
}

void setup() 
{
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize BMP280 sensor
  if (!bmp.begin(0x76)) 
  {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  } 
  else 
  {
    Serial.println("BMP280 sensor initialized successfully.");
  }

  // Initialize OLED display
  Serial.println("OLED display initialized successfully.");
  u8g.setContrast(255); // Set the display brightness (0-255)

  // Display splash screen
  displaySplashScreen();

  // Default settings from datasheet
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     // Operating Mode
                  Adafruit_BMP280::SAMPLING_X2,     // Temp. oversampling
                  Adafruit_BMP280::SAMPLING_X16,    // Pressure oversampling
                  Adafruit_BMP280::FILTER_X16,      // Filtering
                  Adafruit_BMP280::STANDBY_MS_500); // Standby time
}

void loop() 
{
  Serial.print(F("Temperature = "));
  Serial.print(bmp.readTemperature());
  Serial.println(" °C");

  Serial.print(F("Pressure = "));
  Serial.print(bmp.readPressure()/100);
  Serial.println(" hPa");

  Serial.print(F("Altitude = "));
  Serial.print(bmp.readAltitude(1013.25)); // Adjusted to local forecast!
  Serial.println(" m");

  // Convert float to string for display
  char temperatureStr[10];
  dtostrf(bmp.readTemperature(), 6, 2, temperatureStr);

  char pressureStr[10];
  dtostrf(bmp.readPressure()/100, 6, 2, pressureStr);

  char altitudeStr[10];
  dtostrf(bmp.readAltitude(1013.25), 6, 2, altitudeStr);

  // Display values on OLED
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_profont12r); // font for heading
    u8g.drawStr(0, 10, "BMP280 Sensor Data:");
    u8g.drawLine(0, 12, 106, 12); // Draw a line under the heading
    
    // font for the data
    u8g.setFont(u8g_font_profont11); 

    // Display Temperature
    u8g.drawStr(0, 28, "Temperature:");
    u8g.drawStr(69, 28, temperatureStr);
    u8g.drawStr(107, 28, "\xB0""C");
    
    // Display Pressure
    u8g.drawStr(0, 40, "Pressure:");
    u8g.drawStr(57, 40, pressureStr);
    u8g.drawStr(95, 40, "hPa");
    
    // Display Altitude
    u8g.drawStr(0, 52, "Altitude:");
    u8g.drawStr(57, 52, altitudeStr);
    u8g.drawStr(95, 52, "m");

  } while (u8g.nextPage());

  // Delay before next reading
  delay(1000);
}