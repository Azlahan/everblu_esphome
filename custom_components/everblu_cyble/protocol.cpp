#include "protocol.h"

#include "esphome/core/log.h"


namespace esphome {
namespace everblu_cyble {


static const char *TAG = "everblu_protocol";



// --------------------------------------------------
// Initialisation protocole
// --------------------------------------------------

void protocol_init()
{
    ESP_LOGI(TAG,
             "Initialisation protocole EverBlu");
}



// --------------------------------------------------
// Vérification trame
// --------------------------------------------------

bool protocol_check_frame(
        const uint8_t *data,
        size_t length)
{

    if (data == nullptr)
        return false;


    /*
       Taille minimale provisoire.

       À remplacer par la vraie structure
       du paquet EverBlu Cyble.
    */

    if (length < 8)
        return false;


    return true;
}




// --------------------------------------------------
// Décodage trame
// --------------------------------------------------

bool protocol_decode(
        const uint8_t *data,
        size_t length,
        EverbluData *result)
{

    if (result == nullptr)
        return false;


    if (!protocol_check_frame(data, length))
        return false;



    /*
       PLACEHOLDER

       Ici viendra :

       - lecture identifiant compteur
       - lecture index eau
       - lecture batterie
       - calcul RSSI

    */



    result->valid = true;


    /*
       Valeurs de test uniquement
       pour vérifier le chemin :

       CC1101 -> protocole -> ESPHome -> HA

    */

    result->meter_id = 0;

    result->index = 0;

    result->battery = 100;

    result->rssi = -50;



    ESP_LOGD(TAG,
             "Trame EverBlu décodée (test)");



    return true;
}



} // namespace everblu_cyble
} // namespace esphome
