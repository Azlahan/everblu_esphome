#include "everblu_cyble.h"

#include "cc1101.h"
#include "protocol.h"

#include "esphome/core/log.h"
#include "esphome/core/hal.h"


namespace esphome {
namespace everblu_cyble {


static const char *TAG = "everblu_cyble";


// --------------------------------------------------
// Initialisation du composant
// --------------------------------------------------

void EverbluCyble::setup()
{
    ESP_LOGI(TAG, "Démarrage EverBlu Cyble");


    // Initialisation de la broche CS si présente
    if (this->cs_pin_ != nullptr)
    {
        this->cs_pin_->setup();
    }


    // Initialisation radio CC1101
    cc1101_component_init();


    // Test communication CC1101
    if (!cc1101_component_test())
    {
        ESP_LOGE(TAG,
                 "Erreur communication CC1101");

        return;
    }


    // Initialisation protocole
    protocol_init();


    // Passage en écoute
    cc1101_rx();


    this->initialized_ = true;


    ESP_LOGI(TAG,
             "EverBlu Cyble prêt");
}



// --------------------------------------------------
// Boucle principale
// --------------------------------------------------

void EverbluCyble::loop()
{
    if (!this->initialized_)
        return;


    uint32_t now = millis();


    if (now - this->last_read_ < 1000)
        return;


    this->last_read_ = now;



    /*
        Future séquence :

        1) Lire FIFO CC1101
        2) Récupérer la trame
        3) protocol_decode()
        4) Publier les capteurs HA

    */


    uint8_t buffer[CC1101_FIFO_SIZE];


    uint8_t length =
        cc1101_read_fifo(buffer);



    if (length == 0)
    {
        ESP_LOGD(TAG,
                 "Pas de trame");
        return;
    }



    EverbluData data;


    if (protocol_decode(
            buffer,
            length,
            &data))
    {

        ESP_LOGI(TAG,
                 "Trame EverBlu valide");


        if (this->index_sensor_ != nullptr)
        {
            this->index_sensor_->publish_state(
                data.index
            );
        }


        if (this->battery_sensor_ != nullptr)
        {
            this->battery_sensor_->publish_state(
                data.battery
            );
        }


        if (this->rssi_sensor_ != nullptr)
        {
            this->rssi_sensor_->publish_state(
                data.rssi
            );
        }
    }
}



} // namespace everblu_cyble
} // namespace esphome
