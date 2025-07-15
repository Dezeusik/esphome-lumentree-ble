#include "lumentree_ble_sensor.h"

namespace esphome {
namespace lumentree_ble_sensor {

void LumentreeBLESensor::loop() {
  if (!client_ || client_->state() != ble_client::ClientState::ESTABLISHED)
    return;
  uint32_t now = millis();
  if (now - last_ > update_interval_) {
    last_ = now;
    // Wysyłamy zapytanie modbus: 01 03 00 00 00 10 44 06
    std::vector<uint8_t> cmd = {0x01, 0x03, 0x00, 0x00, 0x00, 0x10, 0x44, 0x06};
    client_->write(0xFFE0, 0xFFE1, cmd, false);
    ESP_LOGI("LumentreeBLE", "Zapytanie BLE wysłane");
  }
}

void LumentreeBLESensor::on_notify(uint16_t handle, std::vector<uint8_t> &data) {
  if (data.size() < 35) return; // 3 bajty nagłówka, 32 danych, 2 CRC
  ESP_LOGI("LumentreeBLE", "Odebrano: %s", format_hex_pretty(data).c_str());

  // Dane od offsetu 3: 16 rejestrów (2 bajty każdy)
  uint16_t regs[16];
  for (int i = 0; i < 16; i++)
    regs[i] = (data[3 + i * 2] << 8) | data[3 + i * 2 + 1];

  float voltage = regs[1] / 10.0f;
  float current = regs[2] / 100.0f;
  float power   = regs[3];

  if (voltage_sensor) voltage_sensor->publish_state(voltage);
  if (current_sensor) current_sensor->publish_state(current);
  if (power_sensor) power_sensor->publish_state(power);

  ESP_LOGI("LumentreeBLE", "Napięcie: %.1f V, Prąd: %.2f A, Moc: %.0f W", voltage, current, power);
}

}  // namespace lumentree_ble_sensor
}  // namespace esphome