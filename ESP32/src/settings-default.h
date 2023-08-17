// WiFi credentials
const char* ssid = "LINKSYS";
const char* password = "password";
char date_string[100];

// NTP setup
const char* ntpServer = "north-america.pool.ntp.org";
const long  gmtOffset_sec = -18000; // Eastern Daylight Time (EDT)
const int   daylightOffset_sec = 3600;

// scheduled datahub config
const char* datahub_host = "https://devices.website.net";

// weather api endpoint
const char* weather_api_endpoint = "https://openweather.website.net/";
const char* device_name = "temp-check-default";
const char* zipcode = "10001";

// latitude and logitude
float latitude = 40.0;
float longitude = -70.0;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// DHT setup
#define DHTPIN  15
#define DHTTYPE DHT22
