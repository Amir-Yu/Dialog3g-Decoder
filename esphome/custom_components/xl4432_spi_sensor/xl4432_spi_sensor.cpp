#include "esphome.h"
#include "esphome/core/log.h"
#include "xl4432_spi_sensor.h"
#include "xl4432.h"

namespace esphome {
namespace xl4432_spi_sensor {

static const char *TAG = "xl4432_spi_sensor.sensor";
#define nIRQ_PIN     5

// Declare a variable to hold the METER_ID that will be set from YAML
char METER_ID[3] = {0x4E, 0x61, 0xBC};  // default value (can be overwritten)
Xl4432 xl4432(METER_ID);

ICACHE_RAM_ATTR void nIRQ_ISR() {
	xl4432.spiDisableReciver();
	xl4432.checkForNewPacket();
	xl4432.spiEnableReciver();
}

void Xl4432SPISensor::setup() {
	// Retrieve the meter_id parameter from the YAML
  	auto meter_id = this->get_meter_id();
  	if (meter_id.has_value()) {
    	// Update METER_ID with YAML-provided value
    	for (size_t i = 0; i < 3 && i < meter_id.value().size(); i++) {
      		METER_ID[i] = meter_id.value()[i];
    	}
  	}
    pinMode(SS, OUTPUT);
    digitalWrite(SS, HIGH);
    pinMode(nIRQ_PIN, INPUT);
    attachInterrupt(nIRQ_PIN, nIRQ_ISR, FALLING);
    xl4432.initXl4432Registers();

	// Log the active METER_ID
	ESP_LOGD(TAG, "Will try to communicate to read meter ID number: [%02X, %02X, %02X]", METER_ID[0], METER_ID[1], METER_ID[2]);
}

void Xl4432SPISensor::update() {
}

void Xl4432SPISensor::loop() {
	if (xl4432.packetReady and xl4432.meterMeasurment > 0)
	{
		xl4432.packetReady = 0;
		publish_state(xl4432.meterMeasurment);
		ESP_LOGD("custom","Packet:%s",xl4432.output);
    }
}

void Xl4432SPISensor::dump_config() {
    ESP_LOGCONFIG(TAG, "Xl4432 SPI sensor");
}

}  // namespace xl4432_spi_sensor
}  // namespace esphome
