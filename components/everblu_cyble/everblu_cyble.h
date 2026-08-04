#pragma once

#include "esphome/core/component.h"
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



        protected:


            // ID compteur recherché

            uint32_t meter_id_{0};



            // Etat interne

            bool initialized_{false};



            // Timer lecture FIFO

            uint32_t last_read_{0};


        };



    } // namespace everblu_cyble
} // namespace esphome