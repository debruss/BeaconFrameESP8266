// BeaconFrameESP8266
// Year: 2020
// Place: Quarantine


/* 
 *  ===== HOW TO USE =====
 *  1. Enter number of networks in: num_of_networks
 *  2. Enter the SSID's in: ssids[]
 *  3. Choose whether you have custom MAC Addresses or not at: const bool use_random_mac
 *  4. If you have custom MAC's, add them at: MACAddresses[]
 *  5. Let's go...
 */


#include <ESP8266WiFi.h>

extern "C" {
  #include "user_interface.h"
}


// === SETTINGS === 
const int num_of_networks = 6;
const bool use_random_mac = true;
const char* ssids[num_of_networks] PROGMEM = // PROGMEM is just for fun :)
{
  "DeBruss",
  "It burns when IP",
  "NSA Surveillance Pigeon",
  "McDonald's Free WiFi",
  "Shout \"MONKEY\" for password",
  "NSA Surveillance Flower"
};
const int MACAddresses[num_of_networks][6] = 
{
  {random(256),random(256),random(256),random(256),random(256),random(256)},
  {random(256),random(256),random(256),random(256),random(256),random(256)},
  {random(256),random(256),random(256),random(256),random(256),random(256)},
  {random(256),random(256),random(256),random(256),random(256),random(256)},
  {random(256),random(256),random(256),random(256),random(256),random(256)},
  {random(256),random(256),random(256),random(256),random(256),random(256)}
};



// Beacon Packet buffer 128
// Look into: https://core.ac.uk/download/pdf/14699804.pdf
uint8_t packet[128] = { 0x80, 0x00, 0x00, 0x00,                           // Frame Control
                /*4*/   0xff, 0xff, 0xff, 0xff, 0xff, 0xff,               // Destination (but it is a broadcast)
                /*10*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06,               // Source address
                /*16*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06,               // Source address
                /*22*/  0xc0, 0x6c,                                       // Fragment and sequence
                /*24*/  0x83, 0x51, 0xf7, 0x8f, 0x0f, 0x00, 0x00, 0x00,   // Timestamp
                /*32*/  0x64, 0x00,                                       // Interval
                /*34*/  0x01, 0x04,                                       // Capabilities
                /* SSID */
                /*36*/  0x00}; // More information is added in the build_beacon_packet() function         

// For simplicity
const uint8_t tail[] = {0x01, 0x08, 0x82, 0x84, 0x8b, 0x96, 0x24, 0x30, 0x48, 0x6c, 0x03, 0x01};              


// A simple function to build beacon packets faster than entering them manually, returns the total length
// Length is needed for the wifi_send_pkt_freedom() function
int build_beacon_packet(const char* beacon_name, int beacon_channel, bool random_mac)
{ 
  int beacon_index = 0;
  while(strcmp(beacon_name, ssids[beacon_index]) != 0) beacon_index++;
  // Randomize SRC MAC (for now)
  if(random_mac)
  {
    packet[10] = packet[16] = random(256);
    packet[11] = packet[17] = random(256);
    packet[12] = packet[18] = random(256);
    packet[13] = packet[19] = random(256);
    packet[14] = packet[20] = random(256);
    packet[15] = packet[21] = random(256);
  } else {
    for(int i = 0; i < 6; i++)
    {
      packet[10+i] = packet[16+i] = MACAddresses[beacon_index][i];
    }
  }

  

  // Set the channel:
  if(beacon_channel == 0) beacon_channel = random(12);
  wifi_set_channel(beacon_channel);
  
  int q = 0;
  do {
    q++;
  } while(beacon_name[q] != '\0');

  packet[37] = q;
  for(int i = 0; i < q; i++) packet[38+i] = beacon_name[i];
  for(int i = q; i < q+12; i++) packet[i+38] = tail[i-q];
  packet[50+q] = beacon_channel; // 38+12+q

  return 48+q;  // 38+12+q-2;
}


void setup() {
  delay(500);
  //Serial.begin(115200);
  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(1);
}



void loop() {
  for(int k = 0; k < num_of_networks; k++)
  {
    int packet_length = build_beacon_packet(ssids[k], 1, use_random_mac); // false --> use predefined MAC's, true --> create random MAC's
    for(int i = 0; i < 3; i++) wifi_send_pkt_freedom(packet, packet_length, 0);
    delay(1);
  }
}
