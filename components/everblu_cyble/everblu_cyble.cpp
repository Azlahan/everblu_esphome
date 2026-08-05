#include "everblu_cyble.h"
#include "registers.h"

#include "esphome/core/log.h"

namespace esphome {
    namespace everblu_cyble {

        static const char *TAG = "everblu_cyble";


        void EverbluCyble::setup() {
            ESP_LOGI(TAG, "Démarrage EverBlu Cyble");

            this->init_radio();

            this->initialized_ = true;

            ESP_LOGI(TAG, "EverBlu Cyble initialisé");
        }


        void EverbluCyble::loop() {

            if (!this->initialized_) {
                return;
            }

            /*
             * Ici viendra :
             * - écoute trame radio
             * - décodage Cyble
             * - publication du volume
             */
        }


        void EverbluCyble::set_meter_id(uint32_t id) {
            this->meter_id_ = id;

            ESP_LOGD(TAG, "Compteur configuré : %u", id);
        }


        void EverbluCyble::init_radio() {

            ESP_LOGD(TAG, "Reset CC1101");

            this->cc1101_.reset();


            /*
             * Configuration radio EverBlu
             *
             * Les registres seront injectés ici :
             * - fréquence 433 MHz
             * - débit FSK
             * - déviation
             * - synchro
             * - filtres
             */


            this->cc1101_.strobe(CC1101_SRX);

            ESP_LOGD(TAG, "CC1101 en réception");
        }


    }  // namespace everblu_cyble
}  // namespace esphome