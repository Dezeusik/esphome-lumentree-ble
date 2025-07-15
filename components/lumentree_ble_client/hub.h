#pragma once
#include "esphome/core/component.h"
#include "esphome/components/ble_client/ble_client.h"
#include <vector>

namespace esphome {
namespace lumentree_ble_client {

class LumentreeBLEListener {
 public:
  virtual void on_lumentree_data(const std::vector<uint8_t> &data) = 0;
};

class LumentreeBLEClient : public esphome::ble_client::BLEClientNode {
 public:
  void register_listener(LumentreeBLEListener *listener) { listeners_.push_back(listener); }

  void gattc_notify_callback(uint16_t handle, std::vector<uint8_t> &value) override {
    for (auto *listener : listeners_) listener->on_lumentree_data(value);
  }

 protected:
  std::vector<LumentreeBLEListener *> listeners_;
};

}  // namespace lumentree_ble_client
}  // namespace esphome
