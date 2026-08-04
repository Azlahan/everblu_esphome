#include "cc1101.h"

#include "esphome/core/log.h"


namespace esphome {
namespace everblu_cyble {


static const char *TAG = "cc1101";


CC1101 cc1101;



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




void CC1101::setup()
{

    ESP_LOGI(TAG,
             "Initialisation CC1101");


    if (this->cs_pin_ != nullptr)
        this->cs_pin_->setup();


    if (this->gdo0_pin_ != nullptr)
        this->gdo0_pin_->setup();


    if (this->gdo2_pin_ != nullptr)
        this->gdo2_pin_->setup();



    cc1101_init();


    ESP_LOGI(TAG,
             "CC1101 VERSION 0x%02X",
             cc1101_get_version());

}



void CC1101::receive()
{
    cc1101_rx();
}



uint8_t CC1101::read_fifo(
        uint8_t *buffer)
{
    return cc1101_read_fifo(buffer);
}



uint8_t CC1101::get_version()
{
    return cc1101_get_version();
}



}
}
