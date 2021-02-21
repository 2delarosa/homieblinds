/**
 * Homie Node to set and report position of a blind
 * 
 */
#include "BlindTiltNode.hpp"

BlindTiltNode::BlindTiltNode(const char *id, const char *name, const char *nType, const int measurementInterval)
    : HomieNode(id, name, nType, false, 0U, 0U)
{
  _measurementInterval = (measurementInterval > MIN_INTERVAL) ? measurementInterval : MIN_INTERVAL;
  _lastMeasurement     = 0;

}


/**
    * Called by Homie when Homie.setup() is called; Once!
  */
void BlindTiltNode::setup()
{
  Homie.getLogger() << cCaption
                    << endl;
  Homie.getLogger() << cIndent
                    << F("Blind1 Position: ")
                    << F("90") // Replace with function lookup
                    << endl;

  advertise(cPropertyTilt)
      .setName(cPropertyTiltName)
      .setDatatype(cPropertyTiltDataType)
      .setUnit(cPropertyTiltFormat);
}

  /**
   * Called by Homie when homie is connected and in run mode
  */
  void BlindTiltNode::loop() {
    if (millis() - _lastMeasurement >= (_measurementInterval * 1000UL) || _lastMeasurement == 0) {
      _lastMeasurement = millis();

      Homie.getLogger() << cIndent 
                        << F("〽 Sending Blind Tilt Positions: ") 
                        << getId() 
                        << endl;
      Homie.getLogger() << cIndent
                        << F("Blind1 Position: ")
                        << F("90") // Replace with function lookup
                        << endl;

      setProperty(cPropertyTilt)
          .setRetained(true)
          .send(WiFi.localIP().toString());
    }
  }