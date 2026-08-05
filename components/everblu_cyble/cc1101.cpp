#include "cc1101.h"

#include "esphome/core/log.h"


namespace esphome {
    namespace everblu_cyble {


        static const char *TAG = "cc1101";


        CC1101 cc1101;



// --------------------------------------------------
// Configuration
// --------------------------------------------------

        void CC1101::set_spi_parent(
                spi::SPIComponent *spi)
        {
            this->spi_ = spi;
        }



        void CC1101::set_cs_pin(
                GPIOPin *pin)
        {
            this->cs_pin_ = pin;
        }



        void CC1101::set_gdo0_pin(
                GPIOPin *pin)
        {
            this->gdo0_pin_ = pin;
        }



        void CC1101::set_gdo2_pin(
                GPIOPin *pin)
        {
            this->gdo2_pin_ = pin;
        }



// --------------------------------------------------
// Setup
// --------------------------------------------------

        void CC1101::setup()
        {

            ESP_LOGI(
                    TAG,
                    "Initialisation CC1101"
            );


            if (this->cs_pin_ != nullptr)
            {
                this->cs_pin_->setup();
                this->cs_pin_->digital_write(true);
            }


            if (this->gdo0_pin_ != nullptr)
                this->gdo0_pin_->setup();


            if (this->gdo2_pin_ != nullptr)
                this->gdo2_pin_->setup();



            delay(10);


            this->strobe(SRES);


            delay(10);


            uint8_t version = this->get_version();


            ESP_LOGI(
                    TAG,
                    "CC1101 VERSION 0x%02X",
                    version
            );

        }



// --------------------------------------------------
// SPI transfert
// --------------------------------------------------

        uint8_t CC1101::transfer_byte(
                uint8_t data)
        {

            if (this->spi_ == nullptr)
                return 0;


            return this->spi_->transfer_byte(
                    data
            );

        }



// --------------------------------------------------
// Registres
// --------------------------------------------------

        void CC1101::write_reg(
                uint8_t addr,
                uint8_t value)
        {

            if (this->cs_pin_ != nullptr)
                this->cs_pin_->digital_write(false);



            this->transfer_byte(addr);

            this->transfer_byte(value);



            if (this->cs_pin_ != nullptr)
                this->cs_pin_->digital_write(true);

        }



        uint8_t CC1101::read_reg(
                uint8_t addr)
        {

            uint8_t value = 0;



            if (this->cs_pin_ != nullptr)
                this->cs_pin_->digital_write(false);



            this->transfer_byte(
                    addr | READ_SINGLE
            );


            value =
                    this->transfer_byte(0);



            if (this->cs_pin_ != nullptr)
                this->cs_pin_->digital_write(true);



            return value;

        }



// --------------------------------------------------
// Burst
// --------------------------------------------------

        void CC1101::write_burst(
                uint8_t addr,
                uint8_t *buffer,
                uint8_t length)
        {

            if (this->cs_pin_ != nullptr)
                this->cs_pin_->digital_write(false);



            this->transfer_byte(
                    addr | WRITE_BURST
            );


            for(uint8_t i=0;i<length;i++)
            {
                this->transfer_byte(
                        buffer[i]
                );
            }



            if (this->cs_pin_ != nullptr)
                this->cs_pin_->digital_write(true);

        }



        void CC1101::read_burst(
                uint8_t addr,
                uint8_t *buffer,
                uint8_t length)
        {

            if (this->cs_pin_ != nullptr)
                this->cs_pin_->digital_write(false);



            this->transfer_byte(
                    addr | READ_BURST
            );


            for(uint8_t i=0;i<length;i++)
            {
                buffer[i] =
                        this->transfer_byte(0);
            }



            if (this->cs_pin_ != nullptr)
                this->cs_pin_->digital_write(true);

        }



// --------------------------------------------------
// Commandes
// --------------------------------------------------

        void CC1101::strobe(
                uint8_t command)
        {

            if (this->cs_pin_ != nullptr)
                this->cs_pin_->digital_write(false);



            this->transfer_byte(
                    command
            );


            if (this->cs_pin_ != nullptr)
                this->cs_pin_->digital_write(true);

        }



// --------------------------------------------------
// Radio
// --------------------------------------------------

        void CC1101::receive()
        {

            ESP_LOGD(
                    TAG,
                    "Passage CC1101 RX"
            );


            this->strobe(SRX);

        }



        void CC1101::transmit()
        {

            ESP_LOGD(
                    TAG,
                    "Passage CC1101 TX"
            );


            this->strobe(STX);

        }



// --------------------------------------------------
// FIFO
// --------------------------------------------------

        uint8_t CC1101::read_fifo(
                uint8_t *buffer)
        {

            uint8_t count =
                    this->read_reg(RXBYTES)
                    & 0x7F;


            if(count > 0)
            {
                this->read_burst(
                        RXFIFO,
                        buffer,
                        count
                );
            }


            return count;

        }



        void CC1101::write_fifo(
                uint8_t *buffer,
                uint8_t length)
        {

            this->write_burst(
                    TXFIFO,
                    buffer,
                    length
            );

        }



// --------------------------------------------------
// Version
// --------------------------------------------------

        uint8_t CC1101::get_version()
        {

            return this->read_reg(
                    VERSION
            );

        }



    } // namespace everblu_cyble
} // namespace esphome