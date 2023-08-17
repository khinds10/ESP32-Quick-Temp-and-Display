// setup the DHT library
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
int samplesTaken = 0;
int samplesCount = 300;

// current DHT22 readings
String currentTemperature = "";
String currentHumidity = "";

// float to String
String floatToString(float f) {
  return String(f, 0);
}

// convert celcius to fahrenheit
String celciusToFahrenheit(float celcius) {
  float fahrenheit = celcius * 9.0 / 5.0 + 32.0 + tempCalibrate;
  return floatToString(fahrenheit);
}