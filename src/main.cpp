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
#define SKN_MOD_NAME "Monitor-DHT-RCWL-Metrics"
#define SKN_MOD_VERSION "2.0.0"
#define SKN_MOD_BRAND "SknSensors"

#define SKN_DNODE_ID "hardware"
#define SKN_DNODE_TITLE "Device Info"
#define SKN_DNODE_TYPE "sensor"

ADC_MODE(ADC_VCC); //vcc read in MetricsNode

MetricsNode metricsNode(SKN_DNODE_ID, SKN_DNODE_TITLE, SKN_DNODE_TYPE);
BlindTiltNode blindTiltNode(SKN_DNODE_ID, SKN_DNODE_TITLE, SKN_DNODE_TYPE);

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

  metricsNode.setMeasurementInterval(60);
  blindTiltNode.setMeasurementInterval(60);

  Homie_setFirmware(SKN_MOD_NAME, SKN_MOD_VERSION);
  Homie_setBrand(SKN_MOD_BRAND);

  Homie.setBroadcastHandler(TDbroadcastHandler)
      .setup();
}

void loop()
{
  Homie.loop();
}