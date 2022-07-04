String getLocalTime() {
  time_t rawtime;
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return "";
  }
  char timeStringBuff[50];
  strftime(timeStringBuff, sizeof(timeStringBuff), "%I:%M %p", &timeinfo);
  return (String) timeStringBuff;
}

String getLocalDate() {
  time_t rawtime;
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return "";
  }
  char timeStringBuff[50];
  strftime(timeStringBuff, sizeof(timeStringBuff), "%D", &timeinfo);
  return (String) timeStringBuff;
}