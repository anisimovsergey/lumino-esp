# Setting up the device

When the device is powered the first time it sets itself into the `Initial` state.

## The initial state
In the initial state:
* The device name is set to `DEVICE_` prefix followed by a random four letter sequence which can include capital letters from A to Z  and numbers from 0 to 9.
* An unprotected WiFi network access point is created with the name equal to the device name.
* All the information about the networks the device has been previously connected to is erased.

When the device is in the initial state, you can use your phone or a computer with a WiFi adapter for connecting the device to your home network:
* Scan the available WiFi networks on your mobile phone of computer.
* Find the one created by your device, it should have `DEVICE_` prefix, and connect to it.
* You should be redirected to the captive portal page hosted on the device. This page allows you to see all the available WiFi networks and connect to them.
* Connect the device to your WiFi network by selecting it in the list of the available ones, or typing its identifier (SSID) in. For the secured networks you need to provide a password.

If the device successfully connects to the selected WiFi network its own access point gets deleted and the user's browser is redirected to the webpage hosted on the same device but now already through the users WiFi network.

## The connected state

As soon as the device successfully connects the first time to a WiFi network the network identifier (SSID) as well as required password are stored in the device and used in the subsequent connection attempts.

Disconnect or connect to another WiFi network.

## The silent state

If the device is in the initial state and the user doesn't connect to its WiFi network in 10 minutes, the device gets switched to the silent state by shutting down its WiFi access point.
The user can switch it back to the initial state by pressing the reset button.
