#pragma once

#include <stdint.h>

namespace esphome {
    namespace everblu_cyble {

// Registres configuration CC1101

// Configuration fréquence
        static const uint8_t CC1101_FREQ2 = 0x0D;
        static const uint8_t CC1101_FREQ1 = 0x0E;
        static const uint8_t CC1101_FREQ0 = 0x0F;

// Modulation / débit
        static const uint8_t CC1101_MDMCFG4 = 0x10;
        static const uint8_t CC1101_MDMCFG3 = 0x11;
        static const uint8_t CC1101_MDMCFG2 = 0x12;
        static const uint8_t CC1101_MDMCFG1 = 0x13;
        static const uint8_t CC1101_MDMCFG0 = 0x14;

// Déviation fréquence
        static const uint8_t CC1101_DEVIATN = 0x15;

// Amplification
        static const uint8_t CC1101_FREND1 = 0x21;
        static const uint8_t CC1101_FREND0 = 0x22;

// Contrôle automatique gain
        static const uint8_t CC1101_AGCCTRL2 = 0x19;
        static const uint8_t CC1101_AGCCTRL1 = 0x1A;
        static const uint8_t CC1101_AGCCTRL0 = 0x1B;

// Synchronisation
        static const uint8_t CC1101_SYNC1 = 0x04;
        static const uint8_t CC1101_SYNC0 = 0x05;

// Taille paquet
        static const uint8_t CC1101_PKTLEN = 0x06;
        static const uint8_t CC1101_PKTCTRL1 = 0x07;
        static const uint8_t CC1101_PKTCTRL0 = 0x08;

// GPIO radio
        static const uint8_t CC1101_IOCFG2 = 0x00;
        static const uint8_t CC1101_IOCFG1 = 0x01;
        static const uint8_t CC1101_IOCFG0 = 0x02;

// FIFO
        static const uint8_t CC1101_TXFIFO = 0x3F;
        static const uint8_t CC1101_RXFIFO = 0x3F;


// Commandes CC1101 (strobe)

        static const uint8_t CC1101_SRES   = 0x30;  // Reset
        static const uint8_t CC1101_SFSTXON = 0x31;
        static const uint8_t CC1101_SXOFF  = 0x32;
        static const uint8_t CC1101_SCAL   = 0x33;
        static const uint8_t CC1101_SRX    = 0x34;
        static const uint8_t CC1101_STX    = 0x35;
        static const uint8_t CC1101_SIDLE  = 0x36;
        static const uint8_t CC1101_SWOR   = 0x38;
        static const uint8_t CC1101_SPWD   = 0x39;
        static const uint8_t CC1101_SFRX   = 0x3A;
        static const uint8_t CC1101_SFTX   = 0x3B;
        static const uint8_t CC1101_SNOP   = 0x3D;


    }  // namespace everblu_cyble
}  // namespace esphome