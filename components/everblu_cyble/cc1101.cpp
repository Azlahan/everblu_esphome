#include "cc1101.h"

#include "esphome/core/log.h"

namespace esphome {
    namespace everblu_cyble {

        static const char *TAG = "cc1101";


        void CC1101::setup() {
            ESP_LOGI(TAG, "CC1101 démarrage");

            if (this->init()) {
                ESP_LOGI(TAG, "CC1101 prêt");
            } else {
                ESP_LOGE(TAG, "Erreur initialisation CC1101");
            }
        }


        void CC1101::loop() {
        }


        void CC1101::set_spi(spi::SPIComponent *spi) {
            this->spi_ = spi;
        }


        void CC1101::set_cs_pin(GPIOPin *pin) {
            this->cs_pin_ = pin;
        }


        bool CC1101::init() {

            if (this->spi_ == nullptr) {
                ESP_LOGE(TAG, "SPI non configuré");
                return false;
            }

            if (this->cs_pin_ == nullptr) {
                ESP_LOGE(TAG, "CS non configuré");
                return false;
            }


            this->cs_pin_->setup();
            this->cs_pin_->digital_write(true);


            this->reset();


            this->initialized_ = true;

            return true;
        }


        void CC1101::reset() {

            ESP_LOGD(TAG, "Reset CC1101");

            // Pour l'instant :
            // la séquence SPI réelle sera ajoutée
            // après validation de la communication.
        }


        void CC1101::strobe(uint8_t command) {

            ESP_LOGD(TAG, "STROBE 0x%02X", command);

            // Commande CC1101 à implémenter
            // lorsque l'accès SPI bas niveau sera ajouté.
        }


    }  // namespace everblu_cyble
}  // namespace esphome