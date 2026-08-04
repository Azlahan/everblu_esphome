#include "cc1101.h"


// Etat interne du driver
static uint8_t initialized = 0;


// --------------------------------------------------
// SPI - à relier au wrapper ESPHome C++
// --------------------------------------------------

void cc1101_write_reg(uint8_t addr, uint8_t value)
{
    // Implémentation SPI à venir
}


uint8_t cc1101_read_reg(uint8_t addr)
{
    // Implémentation SPI à venir
    return 0;
}


void cc1101_write_burst(uint8_t addr, uint8_t *buffer, uint8_t length)
{
    // Implémentation SPI burst à venir
}


void cc1101_read_burst(uint8_t addr, uint8_t *buffer, uint8_t length)
{
    // Implémentation SPI burst à venir
}


void cc1101_strobe(uint8_t command)
{
    // Commande CC1101
}


// --------------------------------------------------
// Reset CC1101
// --------------------------------------------------

void cc1101_reset(void)
{
    cc1101_strobe(SRES);
}


// --------------------------------------------------
// Configuration radio
// --------------------------------------------------

void cc1101_init(void)
{
    /*
      Configuration initiale CC1101

      Les valeurs exactes EverBlu seront ajoutées ici :

      FREQ2/FREQ1/FREQ0
      MDMCFG4
      MDMCFG3
      MDMCFG2
      DEVIATN
      SYNC1/SYNC0
      PKTCTRL
      AGC
    */


    cc1101_reset();

    initialized = 1;
}


// --------------------------------------------------
// Modes radio
// --------------------------------------------------

void cc1101_rx(void)
{
    if (!initialized)
        return;

    cc1101_strobe(SRX);
}


void cc1101_tx(void)
{
    if (!initialized)
        return;

    cc1101_strobe(STX);
}


// --------------------------------------------------
// FIFO
// --------------------------------------------------

uint8_t cc1101_read_fifo(uint8_t *buffer)
{
    if (!initialized)
        return 0;

    return 0;
}


void cc1101_write_fifo(uint8_t *buffer, uint8_t length)
{
    if (!initialized)
        return;
}


// --------------------------------------------------
// Identification
// --------------------------------------------------

uint8_t cc1101_get_version(void)
{
    return cc1101_read_reg(VERSION);
}
