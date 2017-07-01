# Lumino

A remotely controlled lamp based on ESP8266.

## Building the application

This project intended to be built using [PlatformIO](http://platformio.org/)
1. Install [Atom editor](https://atom.io/)
2. Install [PlatformIO](http://platformio.org/)
3. Clone the repo
```shell
$ git clone https://github.com/anisimovsergey/lumino-esp
```
4. Open the folder in Atom editor and build it using PlatformIO
5. Upload the program to your device using PlatformIO

## Uploading static content

Lumino uses a captive portal for creating a connection with your home WiFi. The captive portal implementation consists of two parts, one is the WebSockets based API implemented in this project and another one is a static content stored in EEPROM and served by the web served running on the same device.
For building and uploading this static content to EEPROM you need to do the following:
1. Clone the [lumino-web](https://github.com/anisimovsergey/lumino-web) project.
2. Build it executing `npm install & npm run build` in the project folder.
3. Copy content of the `/dist` folder from `lumino-web` to `/data` of `lumino-esp`.
4. Upload the static content `PlatformIO`->`Run other target...`

## Architecture

The application architecture is based on the message processing. This approach allows to compose the application from modules which don't directly depend on each other but, rather, sending messages and events using the message queue. The advantages of such architecture:
1. Modules are completely decoupled and can evolve independently
2. Asynchronous communication support and better responsiveness
3. It is possible to add and remove modules during run time

![components diagram](https://raw.githubusercontent.com/anisimovsergey/lumino-esp/master/docs/images/components_diagram.png)

### Display controller (DisplayController)
Display controller is responsible for reflecting the current state of the application on a display, including currently selected color, the WiFi connection and the access point state, although in this application the display is just a group of NeoPixel LEDs. This controller doesn't process any requests directly, but instead it listening on the events from the color, settings, connection and access point resources.

### Settings controller (SettingsController)
Settings controller provides access to the application settings stored in EEPROM, such as the device name and currently selected color. The settings are not saved immediately when they change but after 10 seconds timeout just to extend the EEPROM live time.

### Web Server (WebServerAsync)
Asynchronous web-server serves static content which is displayed as the WiFi connection page when the user connects to the access point created by the device. This module is also handling asynchronous WebSockets communication by accepting the clients connections, receiving requests, adding them to the message queue and sending responses back to the clients.

### WiFi Manager (WiFiManger)
This manager creates an access point when the device boots up as well as redirects all the DNS requests to the device itself so it can serve as a [captive portal](https://en.wikipedia.org/wiki/Captive_portal). The captive portal allows to connect the device to the user's WiFi network. This module also responsible for establishing a WiFi connection to the specified network and for advertising the device as mDNS service so that it can be discovered by the client applications (such as [this one](https://github.com/anisimovsergey/lumino-ios)).

### WiFi Scanner (WiFiScanner)
WiFi scanner allows to scan available WiFi networks asynchronously and reports the discovered networks back to the clients.

## Setting up the device

When the device is powered on, it creates an unprotected WiFi access point with a name starting with `LUMINO_` followed by a unique four letter sequence which can include capital letters from A to F and numbers from 0 to 9. This unique name is specific to every device and never changes.

When the access point is available, you should be able connect the device to a WiFi network by doing the following steps:
1. Scan the available WiFi networks on your mobile phone or a computer.
2. Find the one created by your device (it should have `LUMINO_` prefix) and connect to it.
3. You should be redirected to the captive portal page hosted on the device. If you are not redirected automatically, try to open http://192.168.4.1/ in your browser. This page allows you to see all the WiFi networks available for the device to connect.
4. Connect the device to your WiFi network by selecting its SSID in the list of the available ones. For the secured home network, which is mostly the case, you need to provide the password too.
5. When the device connects successfully to the selected network, you can disconnect from the one created by the device itself.

If the user doesn't connect to the WiFi access point in 5 minutes or disconnects from it and doesn't reconnect for the same period of time, the device disables it. In order to re-enable the access point, you need to simply switch the device off and on again.

![access point state diagram](https://raw.githubusercontent.com/anisimovsergey/lumino-esp/master/docs/images/soft_ap_state_diagram.png)

In case of a connection attempt failure, due to an incorrect password or other error, the device displays an error message to the user and remains in the disconnected state trying to connect to the specified WiFi network again and again.

![connection state diagram](https://raw.githubusercontent.com/anisimovsergey/lumino-esp/master/docs/images/connection_state_diagram.png)

In the connected state the WiFi access point created by the device in the initial state, gets eventually disabled but the user can still access the device settings through the WiFi network the device now connected to. For doing that, the user, while being connected to the same network, needs to run [Lumino application](https://github.com/anisimovsergey/lumino-ios) on a mobile device.

If the device losses the WiFi connection, due to a restart of some issues with the network itself, it starts automatically reconnecting using the network identifier and the password stored in the device's memory.

## Communication

When the device is connected to the local network it can be discovered as service "lumino-ws" using mDNS. The client can communicate with the device using WebSockets protocol by connecting to `ws://[device]/ws` endpoint where `device` is the ether a discovered mDNS name or IP address of the device. All the communication messages are formatted as JSON. Some examples of the requests, responses and events you can see below.

### Networks resource
Request for the WiFi networks scanning:
```json
{
  "_type": "request",
  "id": "[random id]",
  "requestType": "scan",
  "resource": "networks"
}
```
Response (request accepted):
```json
{
  "_type": "response",
  "id": "[random id]",
  "requestType": "scan",
  "resource": "networks",
  "content": {
    "_type": "status",
    "code": 202,
    "message": "Scanning WiFi networks."
  }
}
```
#### Events
When the scan is completed successfully the results are broadcasted to all the clients:
```json
{
  "_type": "event",
  "eventType": "scanned",
  "resource": "networks",
  "content": {
    "_type": "networks",
    "elements": [
      {
        "_type": "network",
        "ssid": "BTHub4-NC8S",
        "rssi": -64,
        "encryption": "auto"
      }
    ]
  }
}
```
### Connection resource
#### Reading
Request:
```json
{
  "_type": "request",
  "id": "[random id]",
  "requestType": "read",
  "resource": "connection"
}
```
Response:
```json
{
  "_type": "response",
  "id": "[random id]",
  "requestType": "read",
  "resource": "connection",
  "content": {
    "_type": "connection",
    "ssid": "BTHub4-NC8S",
    "isConnected": true,
    "isProtected": true,
    "rssi": -82,
    "localIP": "192.168.1.71",
    "subnetMask": "255.255.0.0",
    "gatewayIP": "192.168.1.1",
    "dnsIP": "192.168.1.1"
  }
}
```
#### Creating
For connecting to a WiFi network you need to create a connection resource:
```json
{
  "_type": "request",
  "id": "[random id]",
  "requestType": "create",
  "resource": "connection",
  "content": {
    "_type": "connection",
    "ssid": "BTHub4-NC8S",
    "password": "password"
  }
}
```
#### Deleting
For disconnecting from the WiFi network you need to delete the connection resource:
```json
{
  "_type": "request",
  "id": "[random id]",
  "requestType": "delete",
  "resource": "connection"
}
```
#### Events
When the status of the created WiFi connection changes, the device issues the following event:
```json
{
  "_type": "event",
  "eventType": "updated",
  "resource": "connection",
  "content": {
    "_type": "connection",
    "ssid": "BTHub4-NC8S",
    "isConnected": true,
    "isProtected": true,
    "rssi": -82,
    "localIP": "192.168.1.71",
    "subnetMask": "255.255.0.0",
    "gatewayIP": "192.168.1.1",
    "dnsIP": "192.168.1.1"
  }
}
```
### Color resource
#### Reading
Reading the color:
```json
{
  "_type": "request",
  "id": "[random id]",
  "requestType": "read",
  "resource": "color"
}
```
Response:
```json
{
  "_type": "response",
  "id": "[random id]",
  "requestType": "read",
  "resource": "color",
  "content": {
    "_type": "color",
    "h": 0.4,
    "s": 0.9,
    "v": 0.3
  }
}
```
#### Updating
Updating the color:
```json
{
  "_type": "request",
  "id": "[random id]",
  "requestType": "update",
  "resource": "color",
  "content": {
    "_type": "color",
    "h": 0.4,
    "s": 0.9,
    "v": 0.3
  }
}
```
### Settings resource
#### Reading
Reading the settings:
```json
{
  "_type": "request",
  "id": "[random id]",
  "requestType": "read",
  "resource": "settings"
}
```
Response:
```json
{
  "_type": "response",
  "id": "[random id]",
  "requestType": "read",
  "resource": "settings",
  "content": {
    "_type": "settings",
    "isOn": true,
    "uniqueName":"LUMINO_BB6C",
    "deviceName": "MY_LUMINO"
  }
}
```
#### Updating
Updating the settings:
```json
{
  "_type": "request",
  "id": "[random id]",
  "resource": "settings",
  "requestType": "update",
   "content": {
    "_type": "settings",
    "isOn": true,
    "deviceName": "My new Lumino"
  }
}
```

## Used libraries
* [Arduino Core for ESP8266](https://github.com/esp8266/Arduino)
* [Gluino](https://github.com/anisimovsergey/gluino)
* [Arduino JSON](https://github.com/bblanchon/ArduinoJson)
* [ESP Asynchronous Web Server](https://github.com/me-no-dev/ESPAsyncWebServer)
* [ESP Asynchronous TCP](https://github.com/me-no-dev/ESPAsyncTCP)
* [Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
