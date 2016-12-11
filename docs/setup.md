# Setting up the device

When the device is powered the first time it sets itself into the `Initial` state.

## The initial state
In the initial state:
* The device name is set to `DEVICE_` prefix followed by a random four letter sequence which can include capital letters from A to Z  and numbers from 0 to 9.
* An unprotected WiFi network access point is created with the name equal to the device name.
* All the information about the networks the device has been previously connected to is erased.

When the device is in the initial state, you can connect it to your home WiFi network by following these steps:
* Scan the available WiFi networks on your mobile phone or a computer.
* Find the one created by your device (it should have `DEVICE_` prefix) and connect to it.
* You should be redirected to the captive portal page hosted on the device. This page allows you to see all the WiFi networks available for the device to connect.
* Connect the device to your WiFi network by selecting it in the list of the available ones, or typing the network identifier (SSID) in. For the secured networks you need to provide a password too.

If the device successfully connects to a WiFi network, its own access point gets disabled and the user's browser is redirected to the settings webpage hosted on the same device but now accessible through the network it connected to. The address of this page should correspond to the device name followed by `.local` suffix (e.g. device_r2d2.local).

If the user doesn't connect to the WiFi access point created by the device in 5 minutes, the device automatically switches to the [silent state](#silent_state).

## The connected state

As soon as the device successfully connects to a WiFi network, the network identifier (SSID) as well as required password are stored in the device and used in the reconnection attempts.

The device can be disconnec

Disconnect or connect to another WiFi network.

## <a name="silent_state"></a> The silent state

If the device is in the initial state and the user doesn't connect to its WiFi network in 5 minutes, the device gets switched to the silent state by shutting down its WiFi access point.
The user can switch it back to the initial state and enable the access point by pressing the reset button.
