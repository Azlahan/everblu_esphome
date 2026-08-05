#pragma once

#include <stdint.h>

#include "esphome/core/component.h"
#include "esphome/components/spi/spi.h"
#include "esphome/components/gpio/gpio.h"

#include "registers.h"


namespace esphome {
    namespace everblu_cyble {


#define CC1101_FIFO_SIZE 64


        class CC1101 : public Component,
                       public spi::SPIDevice {


        public:


            // -------------------------------
            // Pins
            // -------------------------------

            void set_cs_pin(GPIOPin *pin);

            void set_gdo0_pin(GPIOPin *pin);

            void set_gdo2_pin(GPIOPin *pin);



            // -------------------------------
            // ESPHome
            // -------------------------------

            void setup() override;

            void loop() override {}



            // -------------------------------
            // Radio
            // -------------------------------

            void receive();

            void transmit();



            // -------------------------------
            // SPI
            // -------------------------------

            uint8_t transfer_byte(
                    uint8_t data
            );



            // -------------------------------
            // Registres
            // -------------------------------

            void write_reg(
                    uint8_t addr,
                    uint8_t value
            );


            uint8_t read_reg(
                    uint8_t addr
            );



            // -------------------------------
            // Burst
            // -------------------------------

            void write_burst(
                    uint8_t addr,
                    uint8_t *buffer,
                    uint8_t length
            );


            void read_burst(
                    uint8_t addr,
                    uint8_t *buffer,
                    uint8_t length
            );



            // -------------------------------
            // FIFO
            // -------------------------------

            uint8_t read_fifo(
                    uint8_t *buffer
            );


            void write_fifo(
                    uint8_t *buffer,
                    uint8_t length
            );



            // -------------------------------
            // Commandes
            // -------------------------------

            void strobe(
                    uint8_t command
            );



            // -------------------------------
            // Identification
            // -------------------------------

            uint8_t get_version();



        protected:


            GPIOPin *cs_pin_{nullptr};

            GPIOPin *gdo0_pin_{nullptr};

            GPIOPin *gdo2_pin_{nullptr};


        };



        extern CC1101 cc1101;



    } // namespace everblu_cyble
} // namespace esphome