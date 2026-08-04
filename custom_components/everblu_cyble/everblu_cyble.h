#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
namespace everblu_cyble {


class EverbluCyble : public Component, public spi::SPIDevice {
 public:

  // Initialisation ESPHome
  void setup() override;

  // Boucle principale
  void loop() override;

  // Niveau de log
  float get_setup_priority() const override {
    return setup_priority::DATA;
  }


  // Configuration SPI
  void set_cs_pin(GPIOPin *cs) {
    this->cs_pin_ = cs;
  }


  // Capteurs Home Assistant

  void set_index_sensor(sensor::Sensor *sensor) {
    this->index_sensor_ = sensor;
  }

  void set_battery_sensor(sensor::Sensor *sensor) {
    this->battery_sensor_ = sensor;
  }

  void set_rssi_sensor(sensor::Sensor *sensor) {
    this->rssi_sensor_ = sensor;
  }


 protected:

  GPIOPin *cs_pin_{nullptr};


  sensor::Sensor *index_sensor_{nullptr};
  sensor::Sensor *battery_sensor_{nullptr};
  sensor::Sensor *rssi_sensor_{nullptr};


  // Gestion interne
  bool initialized_{false};

  uint32_t last_read_{0};


};


}  // namespace everblu_cyble
}  // namespace esphome
