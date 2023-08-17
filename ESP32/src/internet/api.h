/**
 * update the weather hub with the current temperature and humidity
 * @param String currentTemperature
 * @param String currentHumidity
 */
String updateWeatherHub(String temperature, String humidity) {

  HTTPClient http;
  String requestBody;
  StaticJsonDocument<1000> weatherReponseDoc;
  StaticJsonDocument<1000> deviceHubPOSTDoc;
  
  // get the outside weather
  http.begin((String) weather_api_endpoint + "?zipcode=" + (String) zipcode);
  http.addHeader("Content-Type", "application/json"); 
  int httpCode = http.GET();
  if(httpCode > 0) {
  
    String httpResponse = http.getString();
    Serial.println(httpCode);
    Serial.println(httpResponse);

    // deserialize the JSON document
    DeserializationError error = deserializeJson(weatherReponseDoc, httpResponse);

    // test if parsing succeeds.
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
    }
  }
  http.end();

  // create JSON document including the inside conditions to save to the device hub
  if(httpCode > 0) {
    deviceHubPOSTDoc["device"] = device_name;
    deviceHubPOSTDoc["value1"] = (String) temperature;
    deviceHubPOSTDoc["value2"] = (String) humidity;
    deviceHubPOSTDoc["value3"] = floatToString(weatherReponseDoc["main"]["temp"]);
    deviceHubPOSTDoc["value4"] = floatToString(weatherReponseDoc["main"]["humidity"]);
    deviceHubPOSTDoc["value5"] = weatherReponseDoc["weather"][0]["description"];    
    serializeJsonPretty(deviceHubPOSTDoc, requestBody);
    Serial.println(requestBody);

    // HTTP POST JSON
    http.begin((String) datahub_host + "/api/logJSON/");
    http.addHeader("Content-Type", "application/json");
    httpCode = http.PUT(requestBody);
    Serial.println(httpCode);
    Serial.println(http.getString());
    http.end();
    return floatToString(weatherReponseDoc["main"]["temp"]);
  }
  return "";
}

// update the data hub with uptime and ip address
void updateDataHub() {
  HTTPClient http;
  String requestBody;
  StaticJsonDocument<1000> deviceHubPOSTDoc;
  
  // create JSON document with the device ip and uptime
  deviceHubPOSTDoc["device"] = device_name;
  deviceHubPOSTDoc["value1"] = WiFi.localIP().toString();
  deviceHubPOSTDoc["value2"] = floatToString(millis() / 1000);
  serializeJsonPretty(deviceHubPOSTDoc, requestBody);
  Serial.println(requestBody);

  // HTTP POST JSON
  http.begin((String) datahub_host + "/api/logJSON/");
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.PUT(requestBody);
  Serial.println(httpCode);
  Serial.println(http.getString());
  http.end();
}
