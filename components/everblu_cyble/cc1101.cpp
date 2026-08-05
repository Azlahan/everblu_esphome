#include "cc1101.h"

#include "esphome/core/log.h"


namespace esphome {
    namespace everblu_cyble {


        static const char *TAG = "cc1101";


        CC1101 cc1101;



// --------------------------------------------------
// Configuration pins
// --------------------------------------------------

        void CC1101::set_cs_pin(GPIOPin *pin)
        {
            this->cs_pin_ = pin;
        }


        void CC1101::set_gdo0_pin(GPIOPin *pin)
        {
            this->gdo0_pin_ = pin;
        }


        void CC1101::set_gdo2_pin(GPIOPin *pin)
        {
            this->gdo2_pin_ = pin;
        }



// --------------------------------------------------
// ESPHome setup
// --------------------------------------------------

        void CC1101::setup()
        {

            ESP_LOGI(TAG, "Initialisation CC1101");


            if (this->cs_pin_ != nullptr)
            {
                this->cs_pin_->setup();

                this->cs_pin_->digital_write(true);
            }


            if (this->gdo0_pin_ != nullptr)
                this->gdo0_pin_->setup();


            if (this->gdo2_pin_ != nullptr)
                this->gdo2_pin_->setup();



            SPI.begin();


            delay(10);


            this->reset();


            ESP_LOGI(TAG,
                     "CC1101 VERSION : 0x%02X",
                     this->get_version());

        }



        void CC1101::loop()
        {

        }



// --------------------------------------------------
// SPI bas niveau
// --------------------------------------------------

        uint8_t CC1101::transfer(uint8_t data)
        {
            return SPI.transfer(data);
        }



// --------------------------------------------------
// Reset CC1101
// --------------------------------------------------

        void CC1101::reset()
        {

            ESP_LOGI(TAG, "Reset CC1101");


            if (this->cs_pin_ == nullptr)
                return;


            this->cs_pin_->digital_write(true);

            delay(1);

            this->cs_pin_->digital_write(false);

            delay(1);


            SPI.transfer(SRES);


            delay(10);


            this->cs_pin_->digital_write(true);

        }



// --------------------------------------------------
// Commandes STROBE
// --------------------------------------------------

        void CC1101::strobe(uint8_t command)
        {

            if (this->cs_pin_ == nullptr)
                return;


            this->cs_pin_->digital_write(false);


            SPI.transfer(command);


            this->cs_pin_->digital_write(true);

        }



// --------------------------------------------------
// Registres
// --------------------------------------------------

        void CC1101::write_reg(
                uint8_t addr,
                uint8_t value
        )
        {

            this->cs_pin_->digital_write(false);


            SPI.transfer(addr);

            SPI.transfer(value);


            this->cs_pin_->digital_write(true);

        }



        uint8_t CC1101::read_reg(
                uint8_t addr
        )
        {

            uint8_t value;


            this->cs_pin_->digital_write(false);


            SPI.transfer(addr | READ_SINGLE);


            value = SPI.transfer(0);


            this->cs_pin_->digital_write(true);


            return value;

        }



// --------------------------------------------------
// Burst
// --------------------------------------------------

        void CC1101::write_burst(
                uint8_t addr,
                uint8_t *buffer,
                uint8_t length
        )
        {

            this->cs_pin_->digital_write(false);


            SPI.transfer(addr | WRITE_BURST);


            for (uint8_t i = 0; i < length; i++)
            {
                SPI.transfer(buffer[i]);
            }


            this->cs_pin_->digital_write(true);

        }



        void CC1101::read_burst(
                uint8_t addr,
                uint8_t *buffer,
                uint8_t length
        )
        {

            this->cs_pin_->digital_write(false);


            SPI.transfer(addr | READ_BURST);


            for (uint8_t i = 0; i < length; i++)
            {
                buffer[i] = SPI.transfer(0);
            }


            this->cs_pin_->digital_write(true);

        }



// --------------------------------------------------
// FIFO
// --------------------------------------------------

        uint8_t CC1101::read_fifo(
                uint8_t *buffer
        )
        {

            uint8_t count;


            count = this->read_reg(RXBYTES);


            if (count == 0)
                return 0;


            if (count > CC1101_FIFO_SIZE)
                count = CC1101_FIFO_SIZE;



            this->read_burst(
                    0x3F,
                    buffer,
                    count
            );


            return count;

        }



        void CC1101::write_fifo(
                uint8_t *buffer,
                uint8_t length
        )
        {

            if (length > CC1101_FIFO_SIZE)
                length = CC1101_FIFO_SIZE;


            this->write_burst(
                    0x3F,
                    buffer,
                    length
            );

        }



// --------------------------------------------------
// Modes radio
// --------------------------------------------------

        void CC1101::rx()
        {

            ESP_LOGI(TAG,
                     "Mode RX");


            this->strobe(SRX);

        }



        void CC1101::tx()
        {

            ESP_LOGI(TAG,
                     "Mode TX");


            this->strobe(STX);

        }



// --------------------------------------------------
// Identification
// --------------------------------------------------

        uint8_t CC1101::get_version()
        {

            return this->read_reg(VERSION);

        }



    } // namespace everblu_cyble
} // namespace esphome