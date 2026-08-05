#include "cc1101.h"

#include "esphome/core/log.h"

namespace esphome {
    namespace everblu_cyble {

        static const char *TAG = "cc1101";


        void CC1101::setup() {
            ESP_LOGD(TAG, "CC1101 setup");
        }


        void CC1101::loop() {
        }


        void CC1101::set_spi(spi::SPIComponent *spi) {
            this->spi_ = spi;
        }


        bool CC1101::init() {

            ESP_LOGD(TAG, "Initialisation CC1101");

            this->reset();

            this->initialized_ = true;

            return true;
        }


        void CC1101::reset() {

            ESP_LOGD(TAG, "Reset CC1101");

            this->strobe(0x30);
        }


        void CC1101::write_register(uint8_t reg, uint8_t value) {

            if (this->spi_ == nullptr) {
                return;
            }

            ESP_LOGD(TAG, "WRITE REG 0x%02X = 0x%02X", reg, value);

        }


        uint8_t CC1101::read_register(uint8_t reg) {

            if (this->spi_ == nullptr) {
                return 0;
            }

            ESP_LOGD(TAG, "READ REG 0x%02X", reg);

            return 0;
        }


        void CC1101::strobe(uint8_t command) {

            ESP_LOGD(TAG, "STROBE 0x%02X", command);

        }


    }  // namespace everblu_cyble
}  // namespace esphome