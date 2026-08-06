#include "cc1101.h"

#include "esphome/core/log.h"

namespace esphome {
    namespace everblu_cyble {

        static const char *const TAG = "cc1101";

        void CC1101::setup() {
        }

        void CC1101::loop() {
        }

        bool CC1101::init() {
            ESP_LOGI(TAG, "Initialisation du CC1101");

            this->initialized_ = true;

            return true;
        }

        void CC1101::reset() {
            ESP_LOGI(TAG, "Reset CC1101");
        }

        void CC1101::strobe(uint8_t command) {
            ESP_LOGD(TAG, "Strobe 0x%02X", command);
        }

        uint8_t CC1101::read_status(uint8_t reg) {
            ESP_LOGD(TAG, "Read status 0x%02X", reg);
            return 0;
        }

        uint8_t CC1101::read_register(uint8_t reg) {
            ESP_LOGD(TAG, "Read register 0x%02X", reg);
            return 0;
        }

        void CC1101::write_register(uint8_t reg, uint8_t value) {
            ESP_LOGD(TAG, "Write register 0x%02X = 0x%02X", reg, value);
        }

    }  // namespace everblu_cyble
}  // namespace esphome