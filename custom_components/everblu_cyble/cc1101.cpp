#include "cc1101.h"

#include "esphome/core/log.h"
#include "esphome/components/spi/spi.h"


namespace esphome {
namespace everblu_cyble {


static const char *TAG = "cc1101";


// Pointeur SPI utilisé par le driver C
SPIComponent *cc1101_spi = nullptr;


// Initialisation du bus SPI CC1101
void cc1101_set_spi(SPIComponent *spi)
{
    cc1101_spi = spi;

    ESP_LOGI(TAG, "Bus SPI CC1101 configuré");
}


// Test présence CC1101
bool cc1101_test()
{
    uint8_t version = cc1101_read_reg(VERSION);

    ESP_LOGI(TAG,
             "Version CC1101 : 0x%02X",
             version);

    return version != 0x00 && version != 0xFF;
}


} // namespace everblu_cyble
} // namespace esphome
