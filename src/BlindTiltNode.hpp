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
  virtual bool handleInput(const HomieRange& range, const String& property, const String& value);
  
private:

  // suggested rate is 1/60Hz (1m)
  static const int MIN_INTERVAL         = 60;  // in seconds
  static const int MEASUREMENT_INTERVAL = 60;
  unsigned long _measurementInterval;
  unsigned long _lastMeasurement;

  const char* cCaption = "• Blind Tilt Position Node";
  const char* cIndent  = "  ◦ ";

  const char *cPropertyLeft = "windowLeft";
  const char *cPropertyLeftName = "Left Window"; //Can use spaces
  const char *cPropertyLeftDataType = "enum:UP,DOWN,CENTER";
  const char *cPropertyLeftFormat = "%"; // Homie requires % instead of word percent
  
  const char *cPropertyCenter = "windowCenter";
  const char *cPropertyCenterName = "Center Window"; //Can use spaces
  const char *cPropertyCenterDataType = "enum:UP,DOWN,CENTER";
  const char *cPropertyCenterFormat = "%"; // Homie requires % instead of word percent
  
  const char *cPropertyRight = "windowRight";
  const char *cPropertyRightName = "Right Window"; //Can use spaces
  const char *cPropertyRightDataType = "enum:UP,DOWN,CENTER";
  const char *cPropertyRightFormat = "%"; // Homie requires % instead of word percent
  
};