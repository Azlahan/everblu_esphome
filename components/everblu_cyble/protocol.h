#pragma once

#include <stdint.h>
#include <stddef.h>


namespace esphome {
namespace everblu_cyble {


// Structure contenant les données décodées du compteur

struct EverbluData {

  // Index compteur (volume)
  uint32_t index = 0;


  // Batterie en %
  uint8_t battery = 0;


  // Qualité signal radio
  int16_t rssi = 0;


  // Numéro compteur
  uint32_t meter_id = 0;


  // Trame valide
  bool valid = false;

};



// Initialise le décodeur
void protocol_init();


// Analyse une trame reçue
bool protocol_decode(
    const uint8_t *data,
    size_t length,
    EverbluData *result
);


// Vérification signature EverBlu
bool protocol_check_frame(
    const uint8_t *data,
    size_t length
);



} // namespace everblu_cyble
} // namespace esphome
