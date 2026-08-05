#pragma once


// ==================================================
// CC1101 Configuration Registers
// ==================================================

#define IOCFG2      0x00
#define IOCFG1      0x01
#define IOCFG0      0x02

#define FIFOTHR     0x03

#define SYNC1       0x04
#define SYNC0       0x05

#define PKTLEN      0x06
#define PKTCTRL1    0x07
#define PKTCTRL0    0x08

#define ADDR        0x09
#define CHANNR      0x0A


#define FSCTRL1     0x0B
#define FSCTRL0     0x0C


#define FREQ2       0x0D
#define FREQ1       0x0E
#define FREQ0       0x0F


#define MDMCFG4     0x10
#define MDMCFG3     0x11
#define MDMCFG2     0x12
#define MDMCFG1     0x13
#define MDMCFG0     0x14


#define DEVIATN     0x15


#define MCSM2       0x16
#define MCSM1       0x17
#define MCSM0       0x18


#define FOCCFG      0x19
#define BSCFG       0x1A


#define AGCCTRL2    0x1B
#define AGCCTRL1    0x1C
#define AGCCTRL0    0x1D


#define WOREVT1     0x1E
#define WOREVT0     0x1F


#define WORCTRL     0x20


#define FREND1      0x21
#define FREND0      0x22


#define FSCAL3      0x23
#define FSCAL2      0x24
#define FSCAL1      0x25
#define FSCAL0      0x26


#define RCCTRL1     0x27
#define RCCTRL0     0x28


#define FSTEST      0x29
#define PTEST       0x2A
#define AGCTEST     0x2B


#define TEST2       0x2C
#define TEST1       0x2D
#define TEST0       0x2E



// ==================================================
// FIFO
// ==================================================

#define TXFIFO      0x3F
#define RXFIFO      0x3F
#define FIFO        0x3F



// ==================================================
// Status Registers
// ==================================================

#define PARTNUM     0x30

#define VERSION     0x31

#define FREQEST     0x32

#define LQI         0x33

#define RSSI        0x34

#define MARCSTATE   0x35

#define WORTIME1    0x36
#define WORTIME0    0x37

#define PKTSTATUS   0x38

#define VCO_VC_DAC  0x39

#define TXBYTES     0x3A

#define RXBYTES     0x3B

#define RCCTRL1_STATUS 0x3C

#define RCCTRL0_STATUS 0x3D



// ==================================================
// Command Strobes CC1101
// ==================================================

#define CC1101_SRES        0x30
#define CC1101_SFSTXON     0x31
#define CC1101_SXOFF       0x32

#define CC1101_SCAL        0x33

#define CC1101_SRX         0x34

#define CC1101_STX         0x35

#define CC1101_SIDLE       0x36

#define CC1101_SAFC        0x37

#define CC1101_SWOR        0x38

#define CC1101_SPWD        0x39

#define CC1101_SFRX        0x3A

#define CC1101_SFTX        0x3B

#define CC1101_SWORRST     0x3C

#define CC1101_SNOP        0x3D



// ==================================================
// SPI flags
// ==================================================

#define WRITE_BURST        0x40

#define READ_SINGLE        0x80

#define READ_BURST         0xC0