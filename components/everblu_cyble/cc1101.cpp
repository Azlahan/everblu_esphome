#include "cc1101.h"

#include "esphome/core/log.h"

namespace esphome {
    namespace everblu_cyble {

        static const char *const TAG = "cc1101";


        void CC1101::setup() {

            ESP_LOGI(TAG, "Setup CC1101");

        }


        void CC1101::loop() {

        }


        bool CC1101::init() {

            ESP_LOGI(TAG, "Initialisation du CC1101");

            /*
             * TODO:
             * Initialisation SPI réelle du CC1101
             * - reset
             * - lecture VERSION
             * - configuration registres
             */

            this->initialized_ = true;

            return true;
        }



        void CC1101::reset() {

            ESP_LOGI(TAG, "Reset CC1101");

            /*
             * TODO:
             * Séquence reset CC1101 :
             * CS LOW
             * attente
             * SRES (0x30)
             * attente READY
             */

        }



        void CC1101::strobe(uint8_t command) {

            ESP_LOGD(TAG, "STROBE 0x%02X", command);

            /*
             * TODO:
             * Envoi commande CC1101
             */

        }



        uint8_t CC1101::read_status(uint8_t reg) {

            ESP_LOGD(TAG, "Lecture STATUS 0x%02X", reg);

            /*
             * TODO:
             * Lecture registre STATUS CC1101
             */

            return 0;

        }



        uint8_t CC1101::read_register(uint8_t reg) {

            ESP_LOGD(TAG, "Lecture registre 0x%02X", reg);

            /*
             * TODO:
             * Lecture registre configuration CC1101
             */

            return 0;

        }



        void CC1101::write_register(uint8_t reg, uint8_t value) {

            ESP_LOGD(TAG,
                     "Ecriture registre 0x%02X = 0x%02X",
                     reg,
                     value);

            /*
             * TODO:
             * Ecriture registre configuration CC1101
             */

        }



    }  // namespace everblu_cyble
}  // namespace esphome