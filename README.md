# BeaconFrameESP8266
CustomBeaconFrameESP8266 is a simple program for the ESP8266 that allows for a fast and easy setup to create network beacons with custom MAC addresses.

## Contribute
In the case of any issues that might occur, please send them via the [Issues tab](https://github.com/debruss/BeaconFrameESP8266/issues). Also, pull requests with new/improved features are always welcome :) 

## Libraries
This program depends on:
- [ESP8266WiFi.h](https://github.com/esp8266/Arduino)

## How to use
1. Enter the number of networks at `const int num_of_networks`,
2. Enter the SSID's in: `const char* ssids[]`,
3. Choose whether you have custom MAC Addresses or not at: `const bool use_random_mac`,
4. If you have custom MAC Addresses, add them at: `const int MACAddresses`,
5. Let's go...

## License
This program is available under the [MIT License](https://github.com/debruss/BeaconFrameESP8266/blob/master/LICENSE).
