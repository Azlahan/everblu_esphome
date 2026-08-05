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
            void setup() override;
            void loop() override;

            void set_meter_id(uint32_t id);

        protected:
            void init_radio();

            uint32_t meter_id_{0};

            bool initialized_{false};

            uint32_t last_read_{0};

            CC1101 cc1101_;
        };

    }  // namespace everblu_cyble
}  // namespace esphome