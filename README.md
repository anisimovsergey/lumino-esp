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
Display controller is responsible for reflecting the current state of the application, including currently selected color, the connection and access point state, on a display, although for this application the display is just a group of NeoPixel LEDs. This controller doesn't process any requests directly but rather listening on the events from the color, connection and access point resources.

### Settings controller (SettingsController)
Settings controller provides access to the application settings such as the device name and currently selected color.

### Web Server (WebServerAsync)
Asynchronous web-server serves static content which is displayed as the WiFi connection page when the user connects to the access point created by the device. This module is also handling asynchronous WebSockets communication by accepting the clients connections, receiving requests, adding them to the message queue and sending the responses back to the clients.

### WiFi Manager (WiFiManger)
This manager creates the access point when the device boots up as well as redirects all the DNS requests to the device itself so it can serve as a captive portal. The captive portal allows to connect the device to the user's WiFi network. This module also responsible for establishing a WiFi connection to the specified network and for advertising the device as MDNS service so that it can be discovered by the client applications (such as [this one](https://github.com/anisimovsergey/lumino-ios))

### WiFi Scanner (WiFiScanner)
WiFi scanner allows to scan WiFi networks asynchronously and reports the discovered networks back to the clients.

## Setting up the device

### Power on

When the device is powered on, it could be be set in either of two states:
* The [initial state](#initial_state), if the WiFi network identifier and password are not stored in the device, what normally happens when the user switches it on the first time of after reseting it.
* The [connected state](#connected_state) when the device has already been connected to the WiFi network before and the network identifier and password are stored in the device memory.

### <a name="initial_state"></a> The initial state
In the initial state:
* The device name is set to `DEVICE_` followed by a random four letter sequence which can include capital letters from A to Z  and numbers from 0 to 9.
* An unprotected WiFi network access point is created with the name equal to the device name.

When the device is in the initial state, you can connect it to your home WiFi network by following these steps:
1. Scan the available WiFi networks on your mobile phone or a computer.
* Find the one created by your device (it should have `DEVICE_` prefix) and connect to it.
* You should be redirected to the captive portal page hosted on the device. If you are not redirected automatically, try to open the following page in your browser:
http://192.164.1.4/ This page allows you to see all the WiFi networks available for the device to connect.
* Connect the device to your WiFi network by selecting it in the list of the available ones. For the secured home network, which is mostly the case, you need to provide the password too.

If the user doesn't connect to the WiFi access point created by the device in 5 minutes, the device automatically switches to the [silent state](#silent_state).

When the device successfully connects to a WiFi network, it switches to the [connected state](#connected_state). Now you can disconnect from the WiFi network created by the device, connect back to your home network and use the software coming with the device for changing its settings. The WiFi access point created by the device will be automatically disabled in 5 minutes when the device switches to the [silent state](#silent_state).

In case of a connection attempt failure, due to an incorrect password or other error, the device displays an error message to the user and remains in the initial state.

### <a name="connected_state"></a> The connected state

As soon as the device successfully connects to a WiFi network, the network identifier as well as the required password are stored in the device's memory and used in the reconnection attempts.

In the connected state the WiFi access point created by the device in the initial state, gets eventually disabled (see [silent state](#silent_state)) but the user can still access the device settings through the WiFi network the device now connected to. For doing that, the user, while being connected to the same network, needs to run the software coming with the device.

Using the software, the user can manipulate the device settings and can also disconnect the device from the WiFi network. In this case, the device erases the current network identifier and password, disconnects from the network and switches back to the [initial state](#initial_state). The same effect can be achieved by pressing the reset button.

If the device losses the WiFi connection, due to a restart of some issues with the network itself, it starts automatically reconnecting using the network identifier and the password stored in the device's memory.

### <a name="silent_state"></a> The silent state

If the device is in the initial or connected state and the user doesn't connect to its WiFi access point in 5 minutes or disconnects from it and doesn't reconnect for the same period of time, the device gets switched to the silent state by shutting down its WiFi access point.

In order to enable the access point, the user needs to simply switch it off and on again.

## Used libraries
* [Arduino Core for ESP8266](https://github.com/esp8266/Arduino)
* [Gluino](https://github.com/anisimovsergey/gluino)
* [Arduino JSON](https://github.com/bblanchon/ArduinoJson)
* [ESP Asynchronous Web Server](https://github.com/me-no-dev/ESPAsyncWebServer)
* [ESP Asynchronous TCP](https://github.com/me-no-dev/ESPAsyncTCP)
* [Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
