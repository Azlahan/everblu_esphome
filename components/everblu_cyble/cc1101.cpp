#include "cc1101.h"
#include "cc1101_driver.h"

#include "esphome/core/log.h"

namespace esphome {
    namespace everblu_cyble {

        static const char *const TAG = "cc1101";

        CC1101 cc1101;

        void CC1101::set_cs_pin(GPIOPin *pin) {
            this->cs_pin_ = pin;
        }

        void CC1101::set_gdo0_pin(GPIOPin *pin) {
            this->gdo0_pin_ = pin;
        }

        void CC1101::set_gdo2_pin(GPIOPin *pin) {
            this->gdo2_pin_ = pin;
        }

        void CC1101::setup() {
            Component::setup();

            ESP_LOGI(TAG, "Initialisation CC1101");

            if (this->cs_pin_ != nullptr)
                this->cs_pin_->setup();

            if (this->gdo0_pin_ != nullptr)
                this->gdo0_pin_->setup();

            if (this->gdo2_pin_ != nullptr)
                this->gdo2_pin_->setup();

            cc1101_init();

            ESP_LOGI(TAG, "CC1101 VERSION 0x%02X", cc1101_get_version());
        }

        void CC1101::receive() {
            cc1101_rx();
        }

        uint8_t CC1101::read_fifo(uint8_t *buffer) {
            return cc1101_read_fifo(buffer);
        }

        uint8_t CC1101::get_version() {
            return cc1101_get_version();
        }

// --------------------------------------------------
// Driver bas niveau CC1101 temporaire
// --------------------------------------------------

        static bool cc1101_initialized = false;


        void cc1101_init()
        {
            ESP_LOGI(TAG, "Driver CC1101 init");

            cc1101_reset();

            cc1101_initialized = true;
        }


        void cc1101_rx()
        {
            if (!cc1101_initialized)
                return;

            ESP_LOGD(TAG, "CC1101 passe en RX");

            cc1101_strobe(SRX);
        }


        uint8_t cc1101_read_fifo(uint8_t *buffer)
        {
            if (!cc1101_initialized)
                return 0;

            return 0;
        }


        uint8_t cc1101_get_version()
        {
            return cc1101_read_reg(VERSION);
        }


        void cc1101_reset()
        {
            ESP_LOGI(TAG, "Reset CC1101");

            cc1101_strobe(SRES);
        }


        void cc1101_strobe(uint8_t command)
        {
            // SPI réel à venir
        }


        uint8_t cc1101_read_reg(uint8_t addr)
        {
            return 0;
        }


        void cc1101_write_reg(uint8_t addr, uint8_t value)
        {
        }


        void cc1101_read_burst(
                uint8_t addr,
                uint8_t *buffer,
                uint8_t length)
        {
        }


        void cc1101_write_burst(
                uint8_t addr,
                uint8_t *buffer,
                uint8_t length)
        {
        }


        void cc1101_tx()
        {
            if (!cc1101_initialized)
                return;

            cc1101_strobe(STX);
        }


        void cc1101_write_fifo(
                uint8_t *buffer,
                uint8_t length)
        {
        }

    }  // namespace everblu_cyble
}  // namespace esphome