#pragma once

#include <stdint.h>

#include "registers.h"


namespace esphome {
    namespace everblu_cyble {


#define CC1101_FIFO_SIZE 64



// --------------------------------------------------
// Initialisation CC1101
// --------------------------------------------------

        void cc1101_init();

        void cc1101_reset();



// --------------------------------------------------
// Accès registres SPI
// --------------------------------------------------

        void cc1101_write_reg(
                uint8_t addr,
                uint8_t value
        );


        uint8_t cc1101_read_reg(
                uint8_t addr
        );



// --------------------------------------------------
// Accès burst SPI
// --------------------------------------------------

        void cc1101_write_burst(
                uint8_t addr,
                uint8_t *buffer,
                uint8_t length
        );


        void cc1101_read_burst(
                uint8_t addr,
                uint8_t *buffer,
                uint8_t length
        );



// --------------------------------------------------
// Commandes CC1101
// --------------------------------------------------

        void cc1101_strobe(
                uint8_t command
        );



// --------------------------------------------------
// Modes radio
// --------------------------------------------------

        void cc1101_rx();

        void cc1101_tx();



// --------------------------------------------------
// FIFO
// --------------------------------------------------

        uint8_t cc1101_read_fifo(
                uint8_t *buffer
        );


        void cc1101_write_fifo(
                uint8_t *buffer,
                uint8_t length
        );



// --------------------------------------------------
// Identification
// --------------------------------------------------

        uint8_t cc1101_get_version();



    } // namespace everblu_cyble
} // namespace esphome