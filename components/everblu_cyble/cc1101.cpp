#include "cc1101.h"

#include "esphome/core/log.h"

namespace esphome {
    namespace everblu_cyble {

        static const char *TAG = "cc1101";


        void CC1101::setup() {
            ESP_LOGI(TAG, "CC1101 démarrage");

            if (this->init()) {
                ESP_LOGI(TAG, "CC1101 OK");
            } else {
                ESP_LOGE(TAG, "CC1101 erreur");
            }
        }


        void CC1101::loop() {
        }


        void CC1101::set_spi(spi::SPIComponent *spi) {
            this->spi_ = spi;
        }


        void CC1101::set_cs_pin(GPIOPin *cs) {
            this->cs_pin_ = cs;
        }


        bool CC1101::init() {

            if (this->cs_pin_ == nullptr || this->spi_ == nullptr) {
                ESP_LOGE(TAG, "SPI ou CS manquant");
                return false;
            }


            this->cs_pin_->setup();
            this->cs_pin_->digital_write(true);


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

            this->strobe(0x30);
        }


        void CC1101::strobe(uint8_t command) {

            this->cs_pin_->digital_write(false);

            this->spi_->write_byte(command);

            this->cs_pin_->digital_write(true);

        }


        uint8_t CC1101::read_status(uint8_t reg) {

            uint8_t value = 0;


            this->cs_pin_->digital_write(false);


            this->spi_->write_byte(reg | 0xC0);

            value = this->spi_->read_byte();


            this->cs_pin_->digital_write(true);


            return value;
        }


        void CC1101::write_register(uint8_t reg, uint8_t value) {

            this->cs_pin_->digital_write(false);


            this->spi_->write_byte(reg);
            this->spi_->write_byte(value);


            this->cs_pin_->digital_write(true);
        }


    }  // namespace everblu_cyble
}  // namespace esphome