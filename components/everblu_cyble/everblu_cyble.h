#pragma once

#include <stdint.h>

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"

#include "cc1101.h"



namespace esphome {
    namespace everblu_cyble {



        class EverbluCyble :
                public Component,
                public sensor::Sensor
        {


        public:


            // ESPHome

            void setup() override;

            void loop() override;



            // Configuration compteur

            void set_meter_id(
                    uint32_t id
            );



            // Liaison radio

            void set_cc1101(
                    CC1101 *radio
            );



        protected:


            uint32_t meter_id_{0};


            CC1101 *cc1101_{nullptr};


            bool initialized_{false};


            uint32_t last_read_{0};



        };



    } // namespace everblu_cyble
} // namespace esphome