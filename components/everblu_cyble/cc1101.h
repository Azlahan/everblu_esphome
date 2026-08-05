#pragma once

#include "esphome/core/component.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
    namespace everblu_cyble {

        class CC1101 : public Component, public spi::SPIDevice {
        public:
            void setup() override;
            void loop() override;

            // Initialisation du transceiver
            bool init();

            // Configuration des registres radio
            void write_register(uint8_t reg, uint8_t value);
            uint8_t read_register(uint8_t reg);

            // Commandes radio
            void strobe(uint8_t command);

            // Transmission / réception
            void transmit(uint8_t *data, uint8_t length);
            bool receive(uint8_t *data, uint8_t length);

            // Lecture état radio
            uint8_t read_status(uint8_t reg);

            // Contrôle du module
            void reset();

        protected:
            bool initialized_{false};
        };

    }  // namespace everblu_cyble
}  // namespace esphome