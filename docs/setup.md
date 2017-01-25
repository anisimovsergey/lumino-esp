# Setting up the device

## Power on

When the device is powered on, it could be be set in either of two states:
* The [initial state](#initial_state), if the WiFi network identifier and password are not stored in the device, what normally happens when the user switches it on the first time of after reseting it.
* The [connected state](#connected_state) when the device has already been connected to the WiFi network before and the network identifier and password are stored in the device memory.

## <a name="initial_state"></a> The initial state
In the initial state:
* The device name is set to `DEVICE_` followed by a random four letter sequence which can include capital letters from A to Z  and numbers from 0 to 9.
* An unprotected WiFi network access point is created with the name equal to the device name.
* All the information about the networks the device has been previously connected to is erased.

When the device is in the initial state, you can connect it to your home WiFi network by following these steps:
1. Scan the available WiFi networks on your mobile phone or a computer.
* Find the one created by your device (it should have `DEVICE_` prefix) and connect to it.
* You should be redirected to the captive portal page hosted on the device. If you are not redirected automatically, try to open the following page in your browser:
http://192.164.1.4/ This page allows you to see all the WiFi networks available for the device to connect.
* Connect the device to your WiFi network by selecting it in the list of the available ones, or typing the network identifier (SSID) in. For the secured home network, which is mostly the case, you need to provide the password too.

If the user doesn't connect to the WiFi access point created by the device in 5 minutes, the device automatically switches to the [silent state](#silent_state).

When the device successfully connects to a WiFi network, it switches to the [connected state](#connected_state). Now you can disconnect from the WiFi network created by the device, connect back to your home network and use the software coming with the device for changing its settings. The WiFi access point created by the device will be automatically disabled in 5 minutes when the device switches to the [silent state](#silent_state).

In case of a connection attempt failure, due to an incorrect password or other error, the device displays an error message to the user and remains in the initial state.

## <a name="connected_state"></a> The connected state

As soon as the device successfully connects to a WiFi network, the network identifier as well as the required password are stored in the device and used in the reconnection attempts.

In the connected state the WiFi access point created by the device in the initial state, gets eventually disabled (see [silent state](#silent_state)) but the user can still access the device settings through the WiFi network the device now connected to. For doing that, the user, while being connected to the same network, needs to run the software coming with the device.

Using the software, the user change manipulate the device settings and can also disconnect the device from the WiFi network. In this case, the device erases the current network identifier and password, disconnects from the network and switches back to the [initial state](#initial_state). The same effect can be achieved by pressing the reset button.

If the device losses the WiFi connection, due to a restart of some issues with the network itself, it starts automatically reconnecting using the network identifier and the password stored in the device's memory.

## <a name="silent_state"></a> The silent state

If the device is in the initial or connected state and the user doesn't connect to its WiFi network in 5 minutes or disconnects from it and doesn't reconnect for the same period of time, the device is switched to the silent state by shutting down its WiFi access point.

In order to enable the access point, the user needs to simply switch it off and on again.
