#include "cc1101.h"


// --------------------------------------------------
// Fonctions bas niveau SPI
// À connecter ensuite à ESP32 SPI
// --------------------------------------------------

void cc1101_write_reg(uint8_t addr, uint8_t value)
{
    // TODO SPI WRITE
}


uint8_t cc1101_read_reg(uint8_t addr)
{
    // TODO SPI READ

    return 0;
}


void cc1101_write_burst(uint8_t addr, uint8_t *buffer, uint8_t length)
{
    // TODO SPI BURST WRITE
}


void cc1101_read_burst(uint8_t addr, uint8_t *buffer, uint8_t length)
{
    // TODO SPI BURST READ
}


void cc1101_strobe(uint8_t command)
{
    // TODO COMMAND STROBE
}


// --------------------------------------------------
// Initialisation CC1101
// --------------------------------------------------

void cc1101_reset(void)
{
    // TODO RESET PIN
}


void cc1101_init(void)
{
    /*
       Initialisation radio à compléter avec
       les valeurs EverBlu du fichier original :

       IOCFGx
       FIFOTHR
       SYNC
       PKTCTRL
       FREQ
       MDMCFG
       DEVIATN
       AGC
       FSCAL
    */

}


// --------------------------------------------------
// Modes radio
// --------------------------------------------------

void cc1101_rx(void)
{
    cc1101_strobe(SRX);
}


void cc1101_tx(void)
{
    cc1101_strobe(STX);
}


// --------------------------------------------------
// FIFO
// --------------------------------------------------

uint8_t cc1101_read_fifo(uint8_t *buffer)
{
    uint8_t length = 0;

    // TODO lecture RX FIFO

    return length;
}


void cc1101_write_fifo(uint8_t *buffer, uint8_t length)
{
    // TODO écriture TX FIFO
}


// --------------------------------------------------
// Identification puce
// --------------------------------------------------

uint8_t cc1101_get_version(void)
{
    return cc1101_read_reg(VERSION);
}
