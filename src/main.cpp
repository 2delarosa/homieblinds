/**
 * @file main.cpp
 * @author Tony De La Rosa and James Scott, Jr.  aka(Skoona) (skoona@gmail.com)
 * @brief HomieNode Implementation of Tilt Blind.
 * @version 1.0.0
 * @date 2021-02-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <Arduino.h>
#include "MetricsNode.hpp"
#include "BlindTiltNode.hpp"

#ifdef ESP8266
extern "C"
{
#include "user_interface.h" // to set CPU Freq for Non-Huzzah's
}
#endif

/*
 * SKN_NODE_ID becomes the base name when ranges are used
 * ex: sknSensors/deviceName/DHT_0/temperature -> 72.3 degress
 * Note: HomieNode(...range,lower,upper) manages this array suffix change; i.e no more name fixups
*/
#define TD_MOD_NAME "Blind Tilt Operations"
#define TD_MOD_VERSION "1.0.0"
#define TD_MOD_BRAND "TDControl"

#define SKN_DNODE_ID "hardware"
#define SKN_DNODE_TITLE "Device Info"
#define SKN_DNODE_TYPE "sensor"

#define TD_BNODE_ID "ThreeBlinds"
#define TD_BNODE_TITLE "Blind Tilt Control" // 24 Character limitation
#define TD_BNODE_TYPE "Rollershutter" // Here is where one to rename it for Rollershutter or Dimmer

ADC_MODE(ADC_VCC); //vcc read in MetricsNode

MetricsNode metricsNode(SKN_DNODE_ID, SKN_DNODE_TITLE, SKN_DNODE_TYPE, 60);
BlindTiltNode blindTiltNode(TD_BNODE_ID, TD_BNODE_TITLE, TD_BNODE_TYPE, 60);

bool TDbroadcastHandler(const String &level, const String &value)
{
  Homie.getLogger() << "Received broadcast level " << level << ": " << value << endl;
  return true;
}

void setup()
{  
  delay(50);  
  Serial.begin(115200);
  while( !Serial)
    delay(100); // wait for external monitor to ready

  Serial << endl << "Starting..." << endl;

  Homie_setFirmware(TD_MOD_NAME, TD_MOD_VERSION);
  Homie_setBrand(TD_MOD_BRAND);

  Homie.setBroadcastHandler(TDbroadcastHandler)
      .setup();
}

void loop()
{
  Homie.loop();
}