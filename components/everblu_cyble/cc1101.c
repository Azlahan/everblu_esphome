#pragma once

#include <stdint.h>


#define CC1101_FIFO_SIZE 64


// Registres / commandes bas niveau
#include "registers.h"



#ifdef __cplusplus
extern "C" {
#endif


void cc1101_init(void);

void cc1101_reset(void);


void cc1101_write_reg(
    uint8_t addr,
    uint8_t value
);


uint8_t cc1101_read_reg(
    uint8_t addr
);


void cc1101_write_burst(
    uint8_t addr,
    uint8_t *buffer,
    uint8_t length
);


void cc1101_read_burst(
    uint8_t addr,
    uint8_t *buffer,
    uint8_t length
);


void cc1101_strobe(
    uint8_t command
);


void cc1101_rx(void);


void cc1101_tx(void);


uint8_t cc1101_read_fifo(
    uint8_t *buffer
);


void cc1101_write_fifo(
    uint8_t *buffer,
    uint8_t length
);


uint8_t cc1101_get_version(void);



#ifdef __cplusplus
}
#endif
