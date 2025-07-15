#include "sensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace lumentree_inverter {

void LumentreeInverterSensor::on_lumentree_data(const std::vector<uint8_t> &data) {
  // DOPASUJ parser pod swoje ramki!
  if (data.size() > 10) {
    float voltage = (data[4] << 8 | data[5]) / 10.0f;     // PRZYKŁAD: bajty 4-5
    float current = (data[6] << 8 | data[7]) / 100.0f;    // bajty 6-7
    float power   = (data[8] << 8 | data[9]);             // bajty 8-9
    if (voltage_sensor_) voltage_sensor_->publish_state(voltage);
    if (current_sensor_) current_sensor_->publish_state(current);
    if (power_sensor_) power_sensor_->publish_state(power);
  }
}

}  // namespace lumentree_inverter
}  // namespace esphome
