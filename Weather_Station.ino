// DHT Temperature & Humidity Sensor

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 4     // Digital pin connected to the DHT sensor 

// Uncomment the type of sensor in use:
#define DHTTYPE    DHT11     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)



DHT_Unified dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);

uint32_t delayMS;

void setup() {
  Serial.begin(9600); // Initialize device.

  dht.begin(); // DHT Sensor Initialization
  
  lcd.begin(); // LCD initialization
  lcd.backlight(); // Turn on the blacklight and print a message.
  lcd.print("Welcome..!");
  sensor_t sensor;
  //delayMS = sensor.min_delay / 1000;
}

void loop() {
  //delay(delayMS); // Delay between measurements.
  delay(2000);
  lcd.clear(); // Clear LCD before refresh


  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    lcd.print("TEMP:");
    lcd.print(event.temperature);
    lcd.print((char)223);
    lcd.print("C");
    Serial.println(event.temperature);
  }


  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    lcd.setCursor(0, 1);
    lcd.print("HUMI:");
    lcd.print(event.relative_humidity);
    lcd.print("%");
  }

  
}
