#pragma once

#include "esphome.h"
#include "ble_client/ble_client.h"

namespace esphome {
namespace lumentree_ble_sensor {

class LumentreeBLESensor : public Component, public ble_client::BLEClientListener {
 public:
  LumentreeBLESensor() = default;

  void set_ble_client(ble_client::BLEClient *client) {
    this->client_ = client;
    if (client_) client_->register_listener(this);
  }

  void set_update_interval(uint32_t ms) { update_interval_ = ms; }

  Sensor *voltage_sensor = new Sensor();
  Sensor *current_sensor = new Sensor();
  Sensor *power_sensor   = new Sensor();

  void setup() override {}
  void loop() override;

  void on_notify(uint16_t handle, std::vector<uint8_t> &data) override;

 protected:
  ble_client::BLEClient *client_{nullptr};
  uint32_t last_ = 0;
  uint32_t update_interval_ = 10000; // 10 sekund domyślnie
};

}  // namespace lumentree_ble_sensor
}  // namespace esphome
