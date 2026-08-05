#pragma once

#include <stdint.h>

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"

#include "cc1101.h"


namespace esphome {
    namespace everblu_cyble {


        class EverbluCyble : public Component,
                             public sensor::Sensor {

        public:

            // ESPHome
            void setup() override;

            void loop() override;



            // Configuration compteur
            void set_meter_id(
                    uint32_t id
            );


            // Configuration radio
            void set_cc1101(
                    CC1101 *radio
            );



        protected:

            // Identifiant compteur EverBlu
            uint32_t meter_id_{0};


            // Pointeur vers le CC1101
            CC1101 *cc1101_{nullptr};


            // Etat interne
            bool initialized_{false};


            // Temporisation lecture
            uint32_t last_read_{0};


        };


    } // namespace everblu_cyble
} // namespace esphome