#include "cc1101.h"

#include "esphome/core/log.h"

namespace esphome {
    namespace everblu_cyble {

        static const char *TAG = "everblu_cyble.cc1101";


        void CC1101::setup() {
            ESP_LOGD(TAG, "Initialisation CC1101");

            if (this->init()) {
                ESP_LOGI(TAG, "CC1101 initialisé");
            } else {
                ESP_LOGE(TAG, "Echec initialisation CC1101");
            }
        }


        void CC1101::loop() {
            // Lecture radio cyclique à implémenter
        }


        bool CC1101::init() {
            ESP_LOGD(TAG, "Reset CC1101");

            this->reset();

            // Configuration minimale du CC1101
            // Les registres EverBlu seront ajoutés ensuite
            // après intégration complète des valeurs du projet original.

            this->initialized_ = true;

            return true;
        }


        void CC1101::reset() {
            ESP_LOGD(TAG, "Commande RESET");

            this->strobe(0x30);  // SRES : Reset CC1101
        }


        void CC1101::write_register(uint8_t reg, uint8_t value) {
            this->enable();

            this->write_byte(reg);
            this->write_byte(value);

            this->disable();
        }


        uint8_t CC1101::read_register(uint8_t reg) {
            uint8_t value = 0;

            this->enable();

            this->write_byte(reg | 0x80);
            value = this->read_byte();

            this->disable();

            return value;
        }


        uint8_t CC1101::read_status(uint8_t reg) {
            return this->read_register(reg | 0xC0);
        }


        void CC1101::strobe(uint8_t command) {
            this->enable();

            this->write_byte(command);

            this->disable();
        }


        void CC1101::transmit(uint8_t *data, uint8_t length) {
            if (!this->initialized_) {
                return;
            }

            ESP_LOGD(TAG, "Transmission %d octets", length);

            // FIFO TX sera ajouté avec la gestion complète
        }


        bool CC1101::receive(uint8_t *data, uint8_t length) {
            if (!this->initialized_) {
                return false;
            }

            // FIFO RX sera ajouté avec la gestion complète

            return false;
        }


    }  // namespace everblu_cyble
}  // namespace esphome