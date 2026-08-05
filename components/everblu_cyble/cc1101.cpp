#include "cc1101.h"

#include "esphome/core/log.h"

#include <Arduino.h>


namespace esphome {
    namespace everblu_cyble {


        static const char *TAG = "cc1101";


        CC1101 cc1101;



// --------------------------------------------------
// Configuration
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
// ESPHome
// --------------------------------------------------

        void CC1101::setup()
        {

            ESP_LOGI(TAG, "Initialisation CC1101");


            if (this->cs_pin_ == nullptr)
            {
                ESP_LOGE(TAG, "CS absent");
                return;
            }


            this->cs_pin_->setup();

            this->cs_pin_->digital_write(true);



            if (this->gdo0_pin_ != nullptr)
                this->gdo0_pin_->setup();


            if (this->gdo2_pin_ != nullptr)
                this->gdo2_pin_->setup();



            // Initialisation SPI ESPHome
            this->spi_setup();


            this->reset();



            ESP_LOGI(TAG,
                     "Version CC1101 : 0x%02X",
                     this->get_version());

        }



        void CC1101::loop()
        {

        }



// --------------------------------------------------
// SPI
// --------------------------------------------------

        uint8_t CC1101::transfer_byte(uint8_t data)
        {

            uint8_t response = 0;


            this->transfer(
                    &data,
                    &response,
                    1
            );


            return response;

        }



// --------------------------------------------------
// Reset
// --------------------------------------------------

        void CC1101::reset()
        {

            ESP_LOGI(TAG, "Reset CC1101");


            this->cs_pin_->digital_write(true);

            delay(1);


            this->cs_pin_->digital_write(false);

            delay(1);


            this->transfer_byte(CC1101_SRES);


            delay(10);


            this->cs_pin_->digital_write(true);


        }



// --------------------------------------------------
// STROBE
// --------------------------------------------------

        void CC1101::strobe(uint8_t command)
        {

            this->cs_pin_->digital_write(false);


            this->transfer_byte(command);


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


            this->transfer_byte(addr);

            this->transfer_byte(value);


            this->cs_pin_->digital_write(true);

        }



        uint8_t CC1101::read_reg(uint8_t addr)
        {

            uint8_t value;


            this->cs_pin_->digital_write(false);


            this->transfer_byte(
                    addr | READ_SINGLE
            );


            value = this->transfer_byte(0);



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


            this->transfer_byte(
                    addr | WRITE_BURST
            );


            for(uint8_t i = 0; i < length; i++)
            {
                this->transfer_byte(buffer[i]);
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


            this->transfer_byte(
                    addr | READ_BURST
            );


            for(uint8_t i = 0; i < length; i++)
            {
                buffer[i] = this->transfer_byte(0);
            }


            this->cs_pin_->digital_write(true);

        }



// --------------------------------------------------
// FIFO
// --------------------------------------------------

        uint8_t CC1101::read_fifo(uint8_t *buffer)
        {

            uint8_t count;


            count = this->read_reg(RXBYTES);


            if(count == 0)
                return 0;


            if(count > CC1101_FIFO_SIZE)
                count = CC1101_FIFO_SIZE;



            this->read_burst(
                    RXFIFO,
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

            if(length > CC1101_FIFO_SIZE)
                length = CC1101_FIFO_SIZE;



            this->write_burst(
                    TXFIFO,
                    buffer,
                    length
            );

        }



// --------------------------------------------------
// Radio
// --------------------------------------------------

        void CC1101::rx()
        {

            ESP_LOGI(TAG, "Mode RX");


            this->strobe(
                    CC1101_SRX
            );

        }




        void CC1101::tx()
        {

            ESP_LOGI(TAG, "Mode TX");


            this->strobe(
                    CC1101_STX
            );

        }



// --------------------------------------------------
// Identification
// --------------------------------------------------

        uint8_t CC1101::get_version()
        {

            return this->read_reg(
                    VERSION
            );

        }



    } // namespace everblu_cyble
} // namespace esphome