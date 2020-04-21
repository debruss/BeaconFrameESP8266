# BeaconFrameESP8266
BeaconFrameESP8266 is a simple program for the ESP8266 that allows for a fast and easy setup to create WiFi network beacons with (custom) MAC addresses. 

__Please note:__ [a library with this program as an example is available](https://github.com/debruss/BeaconFrameLib)

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

### Using and connecting an ESP8266 with a FTDI board
Do __not__ power an ESP8266 with 5V, use 3.3V instead.

__While programming:__

__FTDI__ --> __ESP8266__<br>
VCC --> VCC & EN<br>
GND --> GND & GPIO0<br>
RX  --> TX<br>
TX  --> RX<br>
<br>
__While in normal operation:__

__FTDI__ --> __ESP8266__<br>
VCC --> VCC & EN<br>
VCC --> ca. 10kOhm resistor --> GPIO0<br>
GND --> GND<br>
RX  --> TX<br>
TX  --> RX<br>

## License
This program is available under the [MIT License](https://github.com/debruss/BeaconFrameESP8266/blob/master/LICENSE).
