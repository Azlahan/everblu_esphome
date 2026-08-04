#pragma once

#include <stdint.h>

#include "esphome/core/component.h"
#include "esphome/core/hal.h"

namespace esphome {
    namespace everblu_cyble {

#define CC1101_FIFO_SIZE 64

        class CC1101 : public Component {
        public:
            void set_cs_pin(GPIOPin *pin);
            void set_gdo0_pin(GPIOPin *pin);
            void set_gdo2_pin(GPIOPin *pin);

            void setup() override;

            void receive();

            uint8_t read_fifo(uint8_t *buffer);

            uint8_t get_version();

        protected:
            GPIOPin *cs_pin_{nullptr};
            GPIOPin *gdo0_pin_{nullptr};
            GPIOPin *gdo2_pin_{nullptr};
        };

        extern CC1101 cc1101;

    }  // namespace everblu_cyble
}  // namespace esphome