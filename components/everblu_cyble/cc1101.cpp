#include "cc1101.h"

#include "esphome/core/log.h"

namespace esphome {
    namespace everblu_cyble {

        static const char *const TAG = "cc1101";

// CC1101 command strobes
        static constexpr uint8_t CC1101_SRES = 0x30;

// CC1101 status registers
        static constexpr uint8_t CC1101_PARTNUM = 0x30;
        static constexpr uint8_t CC1101_VERSION = 0x31;

// SPI access flags
        static constexpr uint8_t CC1101_READ_SINGLE = 0x80;
        static constexpr uint8_t CC1101_READ_BURST = 0xC0;


        void CC1101::setup() {
            ESP_LOGI(TAG, "Initialisation du driver CC1101");
        }


        void CC1101::loop() {
            // Rien pour le moment.
        }


        void CC1101::select_() {
            digitalWrite(PIN_CS, LOW);
        }


        void CC1101::deselect_() {
            digitalWrite(PIN_CS, HIGH);
        }


        bool CC1101::init() {
            ESP_LOGI(TAG, "Initialisation SPI du CC1101");

            pinMode(PIN_CS, OUTPUT);
            this->deselect_();

            delay(10);

            // SCK, MISO, MOSI, SS
            SPI.begin(
                    PIN_SCK,
                    PIN_MISO,
                    PIN_MOSI,
                    PIN_CS
            );

            delay(10);

            ESP_LOGI(
                    TAG,
                    "SPI initialise : SCK=%u MISO=%u MOSI=%u CS=%u",
                    PIN_SCK,
                    PIN_MISO,
                    PIN_MOSI,
                    PIN_CS
            );

            this->reset();

            delay(10);

            bool detected = this->test_connection();

            this->initialized_ = detected;

            if (detected) {
                ESP_LOGI(TAG, "CC1101 initialise avec succes");
            } else {
                ESP_LOGE(TAG, "Echec initialisation CC1101");
            }

            return detected;
        }


        void CC1101::reset() {
            ESP_LOGI(TAG, "Reset CC1101");

            // Reset sequence recommended for the CC1101.
            this->deselect_();
            delayMicroseconds(5);

            this->select_();
            delayMicroseconds(10);

            this->deselect_();
            delayMicroseconds(50);

            SPI.beginTransaction(
                    SPISettings(
                            SPI_FREQUENCY,
                            MSBFIRST,
                            SPI_MODE0
                    )
            );

            this->select_();

            // SRES
            SPI.transfer(CC1101_SRES);

            delayMicroseconds(100);

            this->deselect_();

            SPI.endTransaction();

            delay(10);

            ESP_LOGI(TAG, "Reset CC1101 termine");
        }


        void CC1101::strobe(uint8_t command) {
        SPI.beginTransaction(
        SPISettings(
                SPI_FREQUENCY,
                MSBFIRST,
                SPI_MODE0
        )
        );

        this->select_();

        SPI.transfer(command);

        this->deselect_();

        SPI.endTransaction();
    }


    uint8_t CC1101::read_status(uint8_t reg) {
        uint8_t value;

        SPI.beginTransaction(
                SPISettings(
                        SPI_FREQUENCY,
                        MSBFIRST,
                        SPI_MODE0
                )
        );

        this->select_();

        // Status registers require burst-read access.
        SPI.transfer(reg | CC1101_READ_BURST);

        value = SPI.transfer(0x00);

        this->deselect_();

        SPI.endTransaction();

        return value;
    }


    uint8_t CC1101::read_register(uint8_t reg) {
        uint8_t value;

        SPI.beginTransaction(
                SPISettings(
                        SPI_FREQUENCY,
                        MSBFIRST,
                        SPI_MODE0
                )
        );

        this->select_();

        SPI.transfer(reg | CC1101_READ_SINGLE);

        value = SPI.transfer(0x00);

        this->deselect_();

        SPI.endTransaction();

        return value;
    }


    void CC1101::write_register(uint8_t reg, uint8_t value) {
        SPI.beginTransaction(
                SPISettings(
                        SPI_FREQUENCY,
                        MSBFIRST,
                        SPI_MODE0
                )
        );

        this->select_();

        SPI.transfer(reg);
        SPI.transfer(value);

        this->deselect_();

        SPI.endTransaction();
    }


    bool CC1101::test_connection() {
        ESP_LOGI(TAG, "Test de communication avec le CC1101...");

        uint8_t partnum = this->read_status(CC1101_PARTNUM);
        uint8_t version = this->read_status(CC1101_VERSION);

        ESP_LOGI(
                TAG,
                "CC1101 PARTNUM = 0x%02X",
                partnum
        );

        ESP_LOGI(
                TAG,
                "CC1101 VERSION = 0x%02X",
                version
        );

        // Floating/unresponsive SPI commonly reads all 0xFF.
        if (partnum == 0xFF && version == 0xFF) {
            ESP_LOGE(
                    TAG,
                    "CC1101 non detecte : lecture SPI = FF FF"
            );

            return false;
        }

        // PARTNUM should normally be 0x00 on CC1101.
        if (partnum != 0x00) {
            ESP_LOGW(
                    TAG,
                    "PARTNUM inattendu : 0x%02X",
                    partnum
            );
        }

        ESP_LOGI(
                TAG,
                "Communication SPI avec CC1101 OK"
        );

        return true;
    }

}  // namespace everblu_cyble
}  // namespace esphome