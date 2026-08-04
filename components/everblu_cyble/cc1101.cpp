#include "cc1101.h"

#include "esphome/core/log.h"


namespace esphome {
    namespace everblu_cyble {


        static const char *TAG = "cc1101";


// Etat interne du driver

        static bool initialized = false;



// --------------------------------------------------
// Initialisation
// --------------------------------------------------

        void cc1101_init()
        {
            ESP_LOGI(TAG, "Initialisation CC1101");


            cc1101_reset();


            /*
               Configuration radio à venir :

               FREQ2
               FREQ1
               FREQ0

               MDMCFG4
               MDMCFG3
               MDMCFG2

               DEVIATN

               SYNC1
               SYNC0

               PKTCTRL

               AGCCTRL
            */


            initialized = true;


            ESP_LOGI(TAG, "CC1101 initialise");
        }



// --------------------------------------------------
// Reset
// --------------------------------------------------

        void cc1101_reset()
        {
            ESP_LOGI(TAG, "Reset CC1101");

            cc1101_strobe(SRES);
        }



// --------------------------------------------------
// Registres SPI
// --------------------------------------------------

        void cc1101_write_reg(
                uint8_t addr,
                uint8_t value
        )
        {
            /*
               TODO:
               SPI natif ESP32 vers CC1101
            */
        }



        uint8_t cc1101_read_reg(
                uint8_t addr
        )
        {
            /*
               TODO:
               SPI natif ESP32 vers CC1101
            */

            return 0;
        }



// --------------------------------------------------
// Burst SPI
// --------------------------------------------------

        void cc1101_write_burst(
                uint8_t addr,
                uint8_t *buffer,
                uint8_t length
        )
        {
            /*
               TODO:
               Ecriture FIFO / burst
            */
        }



        void cc1101_read_burst(
                uint8_t addr,
                uint8_t *buffer,
                uint8_t length
        )
        {
            /*
               TODO:
               Lecture FIFO / burst
            */
        }



// --------------------------------------------------
// Commandes CC1101
// --------------------------------------------------

        void cc1101_strobe(
                uint8_t command
        )
        {
            /*
               TODO:
               SPI STROBE

               SRES
               SRX
               STX
               SIDLE
               SFRX
               SFTX
            */
        }



// --------------------------------------------------
// Modes radio
// --------------------------------------------------

        void cc1101_rx()
        {
            if (!initialized)
                return;


            ESP_LOGD(TAG, "CC1101 passe en RX");


            cc1101_strobe(SRX);
        }



        void cc1101_tx()
        {
            if (!initialized)
                return;


            ESP_LOGD(TAG, "CC1101 passe en TX");


            cc1101_strobe(STX);
        }



// --------------------------------------------------
// FIFO
// --------------------------------------------------

        uint8_t cc1101_read_fifo(
                uint8_t *buffer
        )
        {
            if (!initialized)
                return 0;


            /*
               TODO:
               Lecture FIFO RX
            */


            return 0;
        }



        void cc1101_write_fifo(
                uint8_t *buffer,
                uint8_t length
        )
        {
            if (!initialized)
                return;


            /*
               TODO:
               Ecriture FIFO TX
            */
        }



// --------------------------------------------------
// Identification
// --------------------------------------------------

        uint8_t cc1101_get_version()
        {
            ESP_LOGI(TAG, "Lecture version CC1101");


            return cc1101_read_reg(VERSION);
        }



    } // namespace everblu_cyble
} // namespace esphome