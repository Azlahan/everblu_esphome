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
    ESP_LOGI(TAG, "Initialisation protocole EverBlu");
}



// --------------------------------------------------
// Vérification d'une trame EverBlu
// --------------------------------------------------

bool protocol_check_frame(
        const uint8_t *data,
        size_t length)
{

    if (data == nullptr)
        return false;


    if (length < 8)
        return false;


    /*
       TODO :

       Ajouter ici :
       - recherche préambule
       - synchro CC1101
       - longueur paquet
       - CRC
       - identification Cyble

    */


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
        Décodage temporaire

        Sera remplacé par :

        - extraction ID compteur
        - extraction index eau
        - état batterie
        - qualité radio

    */


    result->valid = true;


    // Valeurs temporaires
    result->meter_id = 0;

    result->index = 0;

    result->battery = 0;

    result->rssi = 0;



    ESP_LOGD(TAG,
             "Trame EverBlu reçue");


    return true;
}



} // namespace everblu_cyble
} // namespace esphome
