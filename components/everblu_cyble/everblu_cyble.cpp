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
             * - écoute des trames radio
             * - décodage EverBlu
             * - publication dans Home Assistant
             */
        }


        void EverbluCyble::set_meter_id(uint32_t id) {

            this->meter_id_ = id;

            ESP_LOGD(TAG, "Compteur configuré : %u", id);
        }


        void EverbluCyble::init_radio() {

            ESP_LOGI(TAG, "Initialisation du CC1101");

            if (!this->cc1101_.init()) {
                ESP_LOGE(TAG, "Impossible de communiquer avec le CC1101");
                return;
            }

            ESP_LOGI(TAG, "Passage en mode réception");

            this->cc1101_.strobe(CC1101_SRX);

            ESP_LOGI(TAG, "CC1101 en réception");

            /*
             * La configuration EverBlu viendra ensuite :
             *
             * - fréquence 433.82 MHz
             * - modulation 2-FSK
             * - débit
             * - déviation
             * - synchronisation
             * - filtres
             * - réception des trames
             */
        }


    }  // namespace everblu_cyble
}  // namespace esphome