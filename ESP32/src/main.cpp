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
#include <Fonts/FreeMono9pt7b.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <settings.h>
#include <internet/wifi.h>
#include <devices/dht22.h>
#include <devices/sdd1306.h>
#include <internet/ntp.h>
#include <internet/api.h>

// reboot every 25000 samples
int totalSamples = 0;

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
  display.setRotation(2);

  // initialize DHT22 device, add sensors
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);

  // set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
}

void loop() {
  
  // show 12 hour time
  time_t curr_time;
	curr_time = time(NULL);
	tm *tm_local = localtime(&curr_time);
  if (tm_local->tm_hour > 12) tm_local->tm_hour = tm_local->tm_hour - 12;
  if (tm_local->tm_hour == 0) tm_local->tm_hour = 12;
  
  delay(delayMS);
  sensors_event_t event;
  samplesTaken = samplesTaken + 1;
  totalSamples = totalSamples + 1;
  Serial.println("Samples taken: " + String(samplesTaken));
  
  // get temperature event and print its value to screen
  dht.temperature().getEvent(&event);
  if (!isnan(event.temperature)) currentTemperature = celciusToFahrenheit(event.temperature);
  Serial.println("Current temp: " + currentTemperature);

  // update local temp on screen temp or time has changed
  bool updateScreen = false;
  if ((previousLocalTemp != currentTemperature) || (previousLocalTime != getLocalTime())) updateScreen = true;

  if (updateScreen) {
    display.clearDisplay();
    displayText(device_location, 0, 15, 1, &FreeMonoBold12pt7b);

    displayText("In:" + currentTemperature + " F", 0, 60, 1, &FreeMonoBold12pt7b);
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

  // reboot every 25000 samples
  if (totalSamples > 25000) ESP.restart();
}