#pragma once
#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "../lumentree_ble_client/hub.h"

namespace esphome {
namespace lumentree_inverter {

class LumentreeInverterSensor : public esphome::Component,
                                public esphome::lumentree_ble_client::LumentreeBLEListener {
 public:
  void set_voltage_sensor(esphome::sensor::Sensor *s) { voltage_sensor_ = s; }
  void set_current_sensor(esphome::sensor::Sensor *s) { current_sensor_ = s; }
  void set_power_sensor(esphome::sensor::Sensor *s) { power_sensor_ = s; }

  void on_lumentree_data(const std::vector<uint8_t> &data) override;

 protected:
  esphome::sensor::Sensor *voltage_sensor_{nullptr};
  esphome::sensor::Sensor *current_sensor_{nullptr};
  esphome::sensor::Sensor *power_sensor_{nullptr};
};

}  // namespace lumentree_inverter
}  // namespace esphome
