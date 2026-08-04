#pragma once

#include "esphome/core/component.h"
#include "esphome/core/gpio.h"
#include "esphome/components/sensor/sensor.h"

#include <string>


namespace esphome {
namespace everblu_cyble {


class EverbluCyble : public Component, public sensor::Sensor {

 public:

  // Cycle ESPHome
  void setup() override;

  void loop() override;


  float get_setup_priority() const override {
    return setup_priority::DATA;
  }


  // Identifiant compteur

  void set_meter_id(const std::string &id) {
    this->meter_id_ = id;
  }


  // Broche CS CC1101

  void set_cs_pin(GPIOPin *pin) {
    this->cs_pin_ = pin;
  }


  // GDO0 CC1101

  void set_gdo0_pin(GPIOPin *pin) {
    this->gdo0_pin_ = pin;
  }


  // GDO2 CC1101

  void set_gdo2_pin(GPIOPin *pin) {
    this->gdo2_pin_ = pin;
  }


 protected:


  std::string meter_id_;


  GPIOPin *cs_pin_{nullptr};

  GPIOPin *gdo0_pin_{nullptr};

  GPIOPin *gdo2_pin_{nullptr};


  bool initialized_{false};


  uint32_t last_read_{0};

};


} // namespace everblu_cyble
} // namespace esphome
