#pragma once

#include <stdint.h>

#include "esphome/core/component.h"
#include "esphome/core/hal.h"

#include "registers.h"

namespace esphome {
    namespace everblu_cyble {

#define CC1101_FIFO_SIZE 64

        class CC1101 : public Component {
        public:
            // Configuration des broches
            void set_cs_pin(GPIOPin *pin);
            void set_gdo0_pin(GPIOPin *pin);
            void set_gdo2_pin(GPIOPin *pin);

            // Initialisation
            void setup() override;

            // Réception
            void receive();

            // Lecture FIFO
            uint8_t read_fifo(uint8_t *buffer);

            // Version du circuit
            uint8_t get_version();

        protected:
            GPIOPin *cs_pin_{nullptr};
            GPIOPin *gdo0_pin_{nullptr};
            GPIOPin *gdo2_pin_{nullptr};
        };

// Instance globale utilisée par EverbluCyble
        extern CC1101 cc1101;

// --------------------------------------------------------------------
// Driver bas niveau (pour l'instant intégré au même composant)
// --------------------------------------------------------------------

        void cc1101_init();

        void cc1101_reset();

        void cc1101_write_reg(uint8_t addr, uint8_t value);

        uint8_t cc1101_read_reg(uint8_t addr);

        void cc1101_write_burst(uint8_t addr, uint8_t *buffer, uint8_t length);

        void cc1101_read_burst(uint8_t addr, uint8_t *buffer, uint8_t length);

        void cc1101_strobe(uint8_t command);

        void cc1101_rx();

        void cc1101_tx();

        uint8_t cc1101_read_fifo(uint8_t *buffer);

        void cc1101_write_fifo(uint8_t *buffer, uint8_t length);

        uint8_t cc1101_get_version();

    }  // namespace everblu_cyble
}  // namespace esphome