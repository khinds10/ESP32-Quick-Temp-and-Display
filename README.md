# ESP32-Quick-Temp-and-Display
#####DHT22 Sensor - SD1306 i2c Display for quick time and temperature + data logging

![Finished Product](https://github.com/khinds10/ESP32-Quick-Temp-and-Display/blob/main/Construction/5.jpg)

###FLASH ESP32

Checkout the ESP32 Folder to your VSCode with PlatformIO installed as a dependancy.

Connect the USB from the ESP32 to your computer running VSCode/PlatformIO to build and deploy the project.

#####Configure your project

Located in the main src/ folder create a copy of settings.h from settings-default.h and set your custom values for the variables.

You can set WIFI (ssid, password), Timezone (gmtOffset_sec) and latitude, longitude where you live.

#####OPTIONAL DATAHUB 
(datahub_host, device_name settings)

use [https://github.com/khinds10/DeviceHub ](https://github.com/khinds10/DeviceHub)

to setup a custom datahub for your device to post temps as time goes on.

#####Get Outside weather 
(weather_api_endpoint)

[https://openweathermap.org/](https://openweathermap.org/) account is required, the device will simply read from the default forecast returned from the API, it will also post it to the Datahub.

Wire and Hot Glue the components.

![Wiring](https://github.com/khinds10/ESP32-Quick-Temp-and-Display/blob/main/Construction/1.jpg)


###WIRING

__DHT22__

[+] pin -> ESP32 [3V]

[-] pin -> ESP32 [GND]

[out] pint -> ESP32 [Pin 4]

__SD1306__

[+] pin -> ESP32 [3V]

[-] pin -> ESP32 [GND]

[SDA] pin -> ESP32 [Pin 21]

[SCL] pin -> ESP32 [Pin 22]

![Hot Glue Components](https://github.com/khinds10/ESP32-Quick-Temp-and-Display/blob/main/Construction/2.jpg)

3D Print the Box and back panel, use the hole on the side to run the USB to power the ESP32 inside the case.

![Finizhed Product](https://github.com/khinds10/ESP32-Quick-Temp-and-Display/blob/main/Construction/3.jpg)

![Finished Product](https://github.com/khinds10/ESP32-Quick-Temp-and-Display/blob/main/Construction/4.jpg)
