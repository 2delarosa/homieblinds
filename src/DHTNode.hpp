/**
 * Homie Node for DHT Temperature and Humidity  Sensor
 * 
 */

#pragma once

#include <Homie.hpp>
#include <Wire.h>
#include "DHTesp.h"

#ifdef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY !)
#error Select ESP8266 board.
#endif


class DHTNode : public HomieNode {

public:
  DHTNode(const uint8_t dhtPin, DHTesp::DHT_MODEL_t dhtModel, const char *id, const char *name, const char *nType, const int measurementInterval);

  void          setMeasurementInterval(unsigned long interval) { _measurementInterval = interval; }
  unsigned long getMeasurementInterval() const { return _measurementInterval; }
  float getTemperatureF() const { return DHTesp::toFahrenheit( _sensorResults.temperature ); }
  float getHumidity() const { return _sensorResults.humidity; }
  String getModelName();

protected : void setup() override;
  void loop() override;
  
private:
  // DHT Sensors address
  static const int _sensorAddress = 0x44;  

  // suggested rate is 1/60Hz (1m)
  static const int MIN_INTERVAL         = 60;  // in seconds
  static const int MEASUREMENT_INTERVAL = 300;

  const char* cCaption = "• DHT (11/22) Temperature & Humidity Sensor:";
  const char* cIndent  = "  ◦ ";

  const char* cTemperature     = "temperature";
  const char* cTemperatureName = "Temperature";
  const char* cTemperatureUnit = "°F";

  const char *cHumidity = "humidity";
  const char *cHumidityName = "Humidity";
  const char *cHumidityUnit = "%rH";

  unsigned long _measurementInterval;
  unsigned long _lastMeasurement;

  DHTesp *sensor;
  TempAndHumidity _sensorResults;
  DHTesp::DHT_ERROR_t _sensorStatus;
};