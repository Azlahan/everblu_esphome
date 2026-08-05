#pragma once

#include <stdint.h>

#include "esphome/core/component.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
    namespace everblu_cyble {

        class CC1101 : public Component {
        public:
            void setup() override;
            void loop() override;

            void set_spi(spi::SPIComponent *spi);

            bool init();

            void write_register(uint8_t reg, uint8_t value);
            uint8_t read_register(uint8_t reg);

            void strobe(uint8_t command);

            void reset();

        protected:
            spi::SPIComponent *spi_{nullptr};

            bool initialized_{false};
        };

    }  // namespace everblu_cyble
}  // namespace esphome