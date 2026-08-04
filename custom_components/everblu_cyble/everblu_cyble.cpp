#include "everblu_cyble.h"

#include "cc1101.h"
#include "protocol.h"

#include "esphome/core/log.h"


namespace esphome {
namespace everblu_cyble {


static const char *TAG = "everblu_cyble";



void EverbluCyble::setup()
{

  ESP_LOGI(TAG,
           "Initialisation EverBlu Cyble");


  ESP_LOGI(TAG,
           "Compteur : %s",
           this->meter_id_.c_str());


  if (this->cs_pin_ != nullptr)
  {
    this->cs_pin_->setup();
  }


  if (this->gdo0_pin_ != nullptr)
  {
    this->gdo0_pin_->setup();
  }


  if (this->gdo2_pin_ != nullptr)
  {
    this->gdo2_pin_->setup();
  }



  // Initialisation CC1101

  cc1101_init();


  uint8_t version =
      cc1101_get_version();


  ESP_LOGI(TAG,
           "CC1101 version: 0x%02X",
           version);



  protocol_init();


  cc1101_rx();


  this->initialized_ = true;


  ESP_LOGI(TAG,
           "EverBlu prêt");
}





void EverbluCyble::loop()
{

  if (!this->initialized_)
    return;


  uint32_t now = millis();


  if (now - this->last_read_ < 1000)
    return;


  this->last_read_ = now;



  uint8_t buffer[CC1101_FIFO_SIZE];


  uint8_t length =
      cc1101_read_fifo(buffer);



  if (length == 0)
    return;



  EverbluData data;


  if (protocol_decode(
          buffer,
          length,
          &data))
  {


    ESP_LOGI(TAG,
             "Trame EverBlu reçue");


    if (data.valid)
    {

      // Publication Home Assistant

      this->publish_state(
          data.index / 1000.0
      );

    }

  }

}



} // namespace everblu_cyble
} // namespace esphome
