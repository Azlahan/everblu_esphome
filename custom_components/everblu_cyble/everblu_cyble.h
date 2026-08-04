#pragma once

#include "esphome/core/component.h"
#include "esphome/core/gpio.h"
#include "esphome/components/sensor/sensor.h"


namespace esphome {
namespace everblu_cyble {


class EverbluCyble : public Component {

 public:

  // Initialisation ESPHome
  void setup() override;


  // Boucle principale
  void loop() override;


  // Priorité de démarrage
  float get_setup_priority() const override {
    return setup_priority::DATA;
  }


  // Configuration broche CS du CC1101
  void set_cs_pin(GPIOPin *cs) {
    this->cs_pin_ = cs;
  }


  // Capteur index compteur
  void set_index_sensor(sensor::Sensor *sensor) {
    this->index_sensor_ = sensor;
  }


  // Capteur batterie
  void set_battery_sensor(sensor::Sensor *sensor) {
    this->battery_sensor_ = sensor;
  }


  // Capteur RSSI
  void set_rssi_sensor(sensor::Sensor *sensor) {
    this->rssi_sensor_ = sensor;
  }


 protected:

  // Broche Chip Select CC1101
  GPIOPin *cs_pin_{nullptr};


  // Capteurs Home Assistant

  sensor::Sensor *index_sensor_{nullptr};

  sensor::Sensor *battery_sensor_{nullptr};

  sensor::Sensor *rssi_sensor_{nullptr};


  // Etat interne

  bool initialized_{false};


  // Temporisation lecture radio

  uint32_t last_read_{0};


};


}  // namespace everblu_cyble
}  // namespace esphome
