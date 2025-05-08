#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
namespace xl4432_spi_sensor {

ICACHE_RAM_ATTR void nIRQ_ISR();

class Xl4432SPISensor : public sensor::Sensor,
                       public PollingComponent,
                       public spi::SPIDevice<spi::BIT_ORDER_MSB_FIRST, spi::CLOCK_POLARITY_LOW, spi::CLOCK_PHASE_LEADING,
                                            spi::DATA_RATE_1KHZ> {
 public:
  void setup() override;
  void update() override;
  void loop() override;
  void dump_config() override;
  
  // Add these methods for meter_id configuration
  void set_meter_id(const std::vector<uint8_t> &meter_id) { meter_id_ = meter_id; }
  optional<std::vector<uint8_t>> get_meter_id() const { return meter_id_; }

 protected:
  optional<std::vector<uint8_t>> meter_id_;
};

}  // namespace xl4432_spi_sensor
}  // namespace esphome
