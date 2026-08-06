#pragma once

#include <stdint.h>

#include <Arduino.h>
#include <SPI.h>

#include "esphome/core/component.h"

namespace esphome {
    namespace everblu_cyble {

        class CC1101 : public Component {
        public:
            void setup() override;
            void loop() override;

            bool init();

            void reset();
            void strobe(uint8_t command);

            uint8_t read_status(uint8_t reg);
            uint8_t read_register(uint8_t reg);
            void write_register(uint8_t reg, uint8_t value);

            bool test_connection();

        protected:
            static constexpr uint8_t PIN_SCK = 18;
            static constexpr uint8_t PIN_MISO = 19;
            static constexpr uint8_t PIN_MOSI = 23;
            static constexpr uint8_t PIN_CS = 5;

            static constexpr uint32_t SPI_FREQUENCY = 1000000;

            bool initialized_{false};

            void select_();
            void deselect_();
        };

    }  // namespace everblu_cyble
}  // namespace esphome