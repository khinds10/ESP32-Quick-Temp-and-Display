#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "time.h"
#include <Wire.h>
#include <string>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeMonoBold24pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <settings.h>
#include <internet/wifi.h>
#include <devices/dht22.h>
#include <devices/sdd1306.h>
#include <internet/ntp.h>
#include <internet/api.h>

void setup() {
  Serial.begin(115200);

  // begin WiFi connection
  initWiFi();
  Serial.print("RRSI: ");
  Serial.println(WiFi.RSSI());

  // init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  
  // init SDD1306 display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) Serial.println(F("SSD1306 allocation failed"));

  // initialize DHT22 device, add sensors
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);

  // set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
}

void loop() {
  
  delay(delayMS);
  sensors_event_t event;
  samplesTaken = samplesTaken + 1;
  Serial.println("Samples taken: " + String(samplesTaken));
  
  // get temperature event and print its value to screen
  dht.temperature().getEvent(&event);
  if (!isnan(event.temperature)) currentTemperature = celciusToFahrenheit(event.temperature);

  // update local temp on screen temp or time has changed
  bool updateScreen = false;
  if ((previousLocalTemp != currentTemperature) || (previousLocalTime != getLocalTime())) updateScreen = true;

  if (updateScreen) {
    display.clearDisplay();
    displayText(getLocalTime(), 0, 20, 1, &FreeMonoBold12pt7b);
    displayText(currentTemperature + "F", 0, 60, 1, &FreeMonoBold24pt7b);
    previousLocalTime = getLocalTime();
    previousLocalTemp = currentTemperature;
  }
  
  // get humidity event 
  dht.humidity().getEvent(&event);
  if (!isnan(event.relative_humidity)) currentHumidity = event.relative_humidity;

  // update the weather hub with the current temperature and humidity
  if (samplesTaken > samplesCount) {
    updateWeatherHub(currentTemperature, currentHumidity);
    samplesTaken = 0;
  }
}