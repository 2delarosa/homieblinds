/**
 * Homie Node to set and report position of a blind
 * 
 */

#pragma once  //required

#include <Homie.hpp>

#ifdef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY !)
#error Select ESP8266 board.
#endif


class BlindTiltNode : public HomieNode {

public:
  BlindTiltNode (const char *id, const char *name, const char *nType, const int measurementInterval = MEASUREMENT_INTERVAL);
  void setMeasurementInterval(unsigned long interval) { _measurementInterval = interval; }

protected : //Not accessible by main.cpp
  void setup() override;
  void loop() override;
  
private:

  // suggested rate is 1/60Hz (1m)
  static const int MIN_INTERVAL         = 60;  // in seconds
  static const int MEASUREMENT_INTERVAL = 60;
  unsigned long _measurementInterval;
  unsigned long _lastMeasurement;

  const char* cCaption = "• Blind Tilt Position Node";
  const char* cIndent  = "  ◦ ";

  const char *cPropertyTilt = "blind1";
  const char *cPropertyTiltName = "pos";
  const char *cPropertyTiltDataType = "integer";
  const char *cPropertyTiltFormat = "degrees";
  
};