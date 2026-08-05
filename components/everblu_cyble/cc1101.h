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
            void set_cs_pin(GPIOPin *cs);

            bool init();

            uint8_t read_status(uint8_t reg);
            void write_register(uint8_t reg, uint8_t value);
            void strobe(uint8_t command);

            void reset();

        protected:
            spi::SPIComponent *spi_{nullptr};
            GPIOPin *cs_pin_{nullptr};

            bool initialized_{false};
        };

    }  // namespace everblu_cyble
}  // namespace esphome