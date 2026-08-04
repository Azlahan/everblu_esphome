#include "cc1101_driver.h"

#include "esphome/core/log.h"


namespace esphome {
    namespace everblu_cyble {


        static const char *TAG = "everblu_cc1101";


// Etat interne du driver

        static bool initialized = false;



// --------------------------------------------------
// SPI bas niveau
// --------------------------------------------------

        void cc1101_write_reg(
                uint8_t addr,
                uint8_t value
        )
        {
            /*
               TODO:
               Connexion SPI ESPHome à ajouter ici.

               Pour l'instant :
               - structure du driver OK
               - compilation OK
            */
        }



        uint8_t cc1101_read_reg(
                uint8_t addr
        )
        {
            /*
               Lecture SPI CC1101
            */

            return 0;
        }



        void cc1101_write_burst(
                uint8_t addr,
                uint8_t *buffer,
                uint8_t length
        )
        {
            /*
               Ecriture FIFO / burst SPI
            */
        }



        void cc1101_read_burst(
                uint8_t addr,
                uint8_t *buffer,
                uint8_t length
        )
        {
            /*
               Lecture FIFO / burst SPI
            */
        }



        void cc1101_strobe(
                uint8_t command
        )
        {
            /*
               Commandes CC1101 :
               SRES
               SRX
               STX
               etc.
            */
        }



// --------------------------------------------------
// Reset
// --------------------------------------------------

        void cc1101_reset(void)
        {
            ESP_LOGI(
                    TAG,
                    "Reset CC1101"
            );


            cc1101_strobe(SRES);
        }



// --------------------------------------------------
// Initialisation CC1101
// --------------------------------------------------

        void cc1101_init(void)
        {

            ESP_LOGI(
                    TAG,
                    "Initialisation CC1101"
            );


            cc1101_reset();


            /*
               Configuration EverBlu à venir :

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
               AGC
            */


            initialized = true;


            ESP_LOGI(
                    TAG,
                    "CC1101 initialise"
            );
        }



// --------------------------------------------------
// Modes radio
// --------------------------------------------------

        void cc1101_rx(void)
        {

            if (!initialized)
                return;


            ESP_LOGD(
                    TAG,
                    "CC1101 RX"
            );


            cc1101_strobe(SRX);
        }



        void cc1101_tx(void)
        {

            if (!initialized)
                return;


            ESP_LOGD(
                    TAG,
                    "CC1101 TX"
            );


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
               Lire RX FIFO CC1101
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
               Ecriture TX FIFO CC1101
            */
        }



// --------------------------------------------------
// Identification
// --------------------------------------------------

        uint8_t cc1101_get_version(void)
        {

            ESP_LOGI(
                    TAG,
                    "Lecture version CC1101"
            );


            return cc1101_read_reg(
                    VERSION
            );
        }



    } // namespace everblu_cyble
} // namespace esphome