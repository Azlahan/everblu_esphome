#include "everblu_cyble.h"

#include "cc1101.h"

#include "esphome/core/log.h"
#include "esphome/core/hal.h"


namespace esphome {
namespace everblu_cyble {


static const char *TAG = "everblu_cyble";


// --------------------------------------------------
// Initialisation ESPHome
// --------------------------------------------------

void EverbluCyble::setup() {

  ESP_LOGI(TAG, "Initialisation EverBlu Cyble");

  if (this->cs_pin_ != nullptr) {
    this->cs_pin_->setup();
  }


  // Initialisation radio CC1101
  cc1101_init();


  uint8_t version = cc1101_get_version();

  ESP_LOGI(TAG,
           "CC1101 version détectée : 0x%02X",
           version);


  // Passage en réception
  cc1101_rx();


  this->initialized_ = true;


  ESP_LOGI(TAG, "EverBlu prêt en réception");
}



// --------------------------------------------------
// Boucle principale
// --------------------------------------------------

void EverbluCyble::loop() {

  if (!this->initialized_)
    return;


  uint32_t now = millis();


  // Lecture toutes les secondes
  if (now - this->last_read_ < 1000)
    return;


  this->last_read_ = now;



  /*
      Ici viendra ensuite :

      1) Lecture FIFO CC1101
      2) Vérification trame EverBlu
      3) Décodage protocol.cpp
      4) Publication Home Assistant

  */


  uint8_t version = cc1101_get_version();


  // Test temporaire
  if (this->rssi_sensor_ != nullptr) {

    uint8_t rssi =
        cc1101_read_reg(RSSI);

    this->rssi_sensor_->publish_state(
        (float) rssi
    );
  }


  ESP_LOGD(TAG,
           "Attente trame EverBlu...");
}



} // namespace everblu_cyble
} // namespace esphome
