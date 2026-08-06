#include "cc1101.h"

#include "esphome/core/log.h"

namespace esphome {
    namespace everblu_cyble {

        static const char *const TAG = "cc1101";


/*
 * Command Strobes CC1101
 */
        static constexpr uint8_t CC1101_SRES = 0x30;
        static constexpr uint8_t CC1101_SRX  = 0x34;


/*
 * Status register
 */
        static constexpr uint8_t CC1101_VERSION = 0x31;


/*
 * SPI flags
 */
        static constexpr uint8_t CC1101_READ = 0x80;
        static constexpr uint8_t CC1101_WRITE = 0x00;


/*
 * ESPHome lifecycle
 */
        void CC1101::setup() {

            ESP_LOGI(TAG, "Setup CC1101");

        }


        void CC1101::loop() {

        }



/*
 * Initialisation radio
 */
        bool CC1101::init() {

            ESP_LOGI(TAG, "Initialisation du CC1101");


            this->reset();


            uint8_t version = this->read_status(CC1101_VERSION);


            ESP_LOGI(TAG, "Version CC1101 : 0x%02X", version);


            /*
             * Une valeur 0x00 ou 0xFF indique généralement
             * une absence de communication SPI
             */
            if (version == 0x00 || version == 0xFF) {

                ESP_LOGE(TAG, "CC1101 non détecté");

                this->initialized_ = false;

                return false;
            }


            this->initialized_ = true;


            ESP_LOGI(TAG, "CC1101 détecté");


            return true;
        }



/*
 * Reset matériel CC1101
 */
        void CC1101::reset() {

            ESP_LOGI(TAG, "Reset CC1101");


            /*
             * Reset logiciel CC1101
             */
            this->strobe(CC1101_SRES);


            delay(1);

        }



/*
 * Envoi commande STROBE
 */
        void CC1101::strobe(uint8_t command) {


        this->enable();


        this->write_byte(command);


        this->disable();


        ESP_LOGD(TAG, "STROBE 0x%02X", command);

    }



/*
 * Lecture registre STATUS
 */
    uint8_t CC1101::read_status(uint8_t reg) {


        uint8_t value;


        this->enable();


        this->write_byte(reg | CC1101_READ);


        value = this->read_byte();


        this->disable();


        ESP_LOGD(TAG,
                 "STATUS 0x%02X = 0x%02X",
                 reg,
                 value);


        return value;

    }



/*
 * Lecture registre configuration
 */
    uint8_t CC1101::read_register(uint8_t reg) {


        uint8_t value;


        this->enable();


        this->write_byte(reg | CC1101_READ);


        value = this->read_byte();


        this->disable();


        ESP_LOGD(TAG,
                 "READ 0x%02X = 0x%02X",
                 reg,
                 value);


        return value;

    }



/*
 * Ecriture registre configuration
 */
    void CC1101::write_register(uint8_t reg, uint8_t value) {


        this->enable();


        this->write_byte(reg | CC1101_WRITE);


        this->write_byte(value);


        this->disable();


        ESP_LOGD(TAG,
                 "WRITE 0x%02X = 0x%02X",
                 reg,
                 value);

    }



}  // namespace everblu_cyble
}  // namespace esphome