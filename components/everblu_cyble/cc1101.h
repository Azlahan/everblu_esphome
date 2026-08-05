#pragma once

#include <stdint.h>

#include "esphome/core/component.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
    namespace everblu_cyble {

        class CC1101 : public Component,
                       public spi::SPIDevice {
        public:
            void setup() override;
            void loop() override;

            bool init();

            void reset();

            void write_register(uint8_t reg, uint8_t value);
            uint8_t read_status(uint8_t reg);

            void strobe(uint8_t command);

        protected:
            bool initialized_{false};
        };

    }  // namespace everblu_cyble
}  // namespace esphome