# Lumino

A remotely controlled lamp based on ESP8266.

## Build

This project intended to be built using [PlatformIO](http://platformio.org/)
1. Install [Atom editor](https://atom.io/)
2. Install [PlatformIO](http://platformio.org/)
3. Clone the repo
```shell
$ git clone https://github.com/anisimovsergey/lumino-esp
```
4. Open the folder in Atom editor and build it using PlatformIO

## Architecture

The application architecture is based on the message processing. This approach allows to compose the application from modules which don't directly depend on each other but rather sending messages and events using the message queue. The advantages of such architecture:
1. Modules are completely decoupled and can evolve independently
2. Asynchronous communication support and better responsiveness
3. It is possible to add and remove modules during run time

## Modules

### Display controller (DisplayController)
Display controller is responsible for reflecting the current state of the application, including the currently selected color, connection and access point state, on a display although for this application the display it's just a group of LEDs. This controller doesn't process any messages directly but rather listening on the events from the color, connection and access point resources.

### Settings controller (SettingsController)
Settings controller provides access to the application settings such as the device name and currently selected color.

### Web Server (WebServerAsync)
Asynchronous web-server serves static content which is displayed as the WiFi connection page when the user connects to the access point created by the device and gets redirected. This module is also handling asynchronous WebSockets communication by accepting the clients connections, receiving requests adding them to the message queue and sending the responses back to the clients.

### WiFi Manager (WiFiManger)
This manager creates the access point when the device boots up as well as redirects all the DNS requests to the device itself so it can serve as a captive portal for connecting the device to the user's WiFi network. This module also responsible for establishing a WiFi connection to the specified network as well as advertising the device as MDNS service so that it can be discovered by the client applications (such as [this one](https://github.com/anisimovsergey/lumino-ios))

### WiFi Scanner (WiFiScanner)
WiFi scanner allows to scan WiFi networks asynchronously and reports the scanning results back to the clients.

## Used libraries
* [Arduino Core for ESP8266](https://github.com/esp8266/Arduino)
* [Gluino](https://github.com/anisimovsergey/gluino)
* [Arduino JSON](https://github.com/bblanchon/ArduinoJson)
* [ESP Asynchronous Web Server](https://github.com/me-no-dev/ESPAsyncWebServer)
* [ESP Asynchronous TCP](https://github.com/me-no-dev/ESPAsyncTCP)
* [Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
