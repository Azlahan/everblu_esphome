#pragma once

#include <stdint.h>


#define CC1101_FIFO_SIZE 64


#ifdef __cplusplus

#include "esphome/core/gpio.h"


namespace esphome {
namespace everblu_cyble {


class CC1101 {

 public:

  void set_cs_pin(GPIOPin *pin);

  void set_gdo0_pin(GPIOPin *pin);

  void set_gdo2_pin(GPIOPin *pin);


  void setup();


  void receive();


  uint8_t read_fifo(
      uint8_t *buffer
  );


  uint8_t get_version();



 protected:

  GPIOPin *cs_pin_{nullptr};

  GPIOPin *gdo0_pin_{nullptr};

  GPIOPin *gdo2_pin_{nullptr};

};


extern CC1101 cc1101;


}
}

#endif



#ifdef __cplusplus
extern "C" {
#endif


// Fonctions bas niveau cc1101.c

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
