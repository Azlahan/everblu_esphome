#include "cc1101.h"

#include "esphome/core/log.h"

namespace esphome {
    namespace everblu_cyble {

        static const char *TAG = "cc1101";


        void CC1101::setup() {
            ESP_LOGI(TAG, "CC1101 démarrage");

            if (this->init()) {
                ESP_LOGI(TAG, "CC1101 initialisé");
            } else {
                ESP_LOGE(TAG, "Erreur initialisation CC1101");
            }
        }


        void CC1101::loop() {
        }


        bool CC1101::init() {

            this->reset();

            uint8_t part = this->read_status(0x30);
            uint8_t version = this->read_status(0x31);

            ESP_LOGI(TAG, "PARTNUM : 0x%02X", part);
            ESP_LOGI(TAG, "VERSION : 0x%02X", version);

            this->initialized_ = true;

            return true;
        }


        void CC1101::reset() {

            ESP_LOGD(TAG, "Reset CC1101");

            this->enable();

            this->write_byte(0x30);  // SRES

            this->disable();

        }


        void CC1101::strobe(uint8_t command) {

            this->enable();

            this->write_byte(command);

            this->disable();

        }


        uint8_t CC1101::read_status(uint8_t reg) {

            uint8_t value = 0;


            this->enable();

            this->write_byte(reg | 0xC0);

            value = this->read_byte();

            this->disable();


            return value;
        }


        void CC1101::write_register(uint8_t reg, uint8_t value) {

            this->enable();

            this->write_byte(reg);
            this->write_byte(value);

            this->disable();

        }


    }  // namespace everblu_cyble
}  // namespace esphome