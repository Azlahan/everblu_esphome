#ifndef CC1101_H
#define CC1101_H

#include <stdint.h>
#include "registers.h"


// Taille FIFO CC1101
#define CC1101_FIFO_SIZE 64


// Initialisation du CC1101
void cc1101_init(void);


// Reset matériel du CC1101
void cc1101_reset(void);


// Ecriture registre
void cc1101_write_reg(uint8_t addr, uint8_t value);


// Lecture registre
uint8_t cc1101_read_reg(uint8_t addr);


// Ecriture burst
void cc1101_write_burst(uint8_t addr, uint8_t *buffer, uint8_t length);


// Lecture burst
void cc1101_read_burst(uint8_t addr, uint8_t *buffer, uint8_t length);


// Command strobe
void cc1101_strobe(uint8_t command);


// Passage en réception
void cc1101_rx(void);


// Passage en émission
void cc1101_tx(void);


// Lecture FIFO RX
uint8_t cc1101_read_fifo(uint8_t *buffer);


// Ecriture FIFO TX
void cc1101_write_fifo(uint8_t *buffer, uint8_t length);


// Vérification présence CC1101
uint8_t cc1101_get_version(void);

#ifdef __cplusplus

namespace esphome {
namespace everblu_cyble {

void cc1101_component_init();

bool cc1101_component_test();

}
}

#endif
