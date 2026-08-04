#include "everblu_cyble.h"

#include "cc1101.h"
#include "protocol.h"

#include "esphome/core/log.h"


namespace esphome {
namespace everblu_cyble {


static const char *TAG = "everblu_cyble";



void EverbluCyble::setup()
{

  ESP_LOGI(TAG, "Initialisation EverBlu Cyble");


  ESP_LOGI(TAG,
           "Compteur configuré : %u",
           this->meter_id_);




  // Initialisation des GPIO

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




  // Configuration CC1101

  cc1101.set_cs_pin(
      this->cs_pin_
  );


  cc1101.set_gdo0_pin(
      this->gdo0_pin_
  );


  cc1101.set_gdo2_pin(
      this->gdo2_pin_
  );



  cc1101.setup();


  cc1101.receive();



  // Initialisation protocole

  protocol_init();



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
      cc1101.read_fifo(buffer);



  if (length == 0)
  {
    return;
  }



  ESP_LOGD(TAG,
           "Trame reçue : %u octets",
           length);




  EverbluData data;



  if (!protocol_decode(
          buffer,
          length,
          &data))
  {

    ESP_LOGD(TAG,
             "Trame non reconnue");

    return;
  }




  if (!data.valid)
  {
    return;
  }




  // Filtrage compteur

  if (this->meter_id_ != 0 &&
      data.meter_id != this->meter_id_)
  {

    ESP_LOGD(TAG,
             "Compteur ignoré : %u",
             data.meter_id);

    return;
  }





  float volume =
      data.index / 1000.0f;



  ESP_LOGI(TAG,
           "Index eau : %.3f m3",
           volume);



  this->publish_state(volume);

}




} // namespace everblu_cyble
} // namespace esphome
