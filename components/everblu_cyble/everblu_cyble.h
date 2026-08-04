#pragma once

#include "esphome/core/component.h"
#include "esphome/core/gpio.h"
#include "esphome/components/sensor/sensor.h"


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



  // Identifiant compteur EverBlu

  void set_meter_id(uint32_t id) {
    this->meter_id_ = id;
  }



  // Broche CS du CC1101

  void set_cs_pin(GPIOPin *pin) {
    this->cs_pin_ = pin;
  }



  // Broche GDO0 du CC1101

  void set_gdo0_pin(GPIOPin *pin) {
    this->gdo0_pin_ = pin;
  }



  // Broche GDO2 du CC1101

  void set_gdo2_pin(GPIOPin *pin) {
    this->gdo2_pin_ = pin;
  }



 protected:


  // Identifiant compteur

  uint32_t meter_id_{0};



  // GPIO CC1101

  GPIOPin *cs_pin_{nullptr};

  GPIOPin *gdo0_pin_{nullptr};

  GPIOPin *gdo2_pin_{nullptr};



  // Etat interne

  bool initialized_{false};



  // Timer lecture

  uint32_t last_read_{0};


};


} // namespace everblu_cyble
} // namespace esphome
