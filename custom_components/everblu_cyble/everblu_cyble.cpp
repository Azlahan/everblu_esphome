#include "cc1101.h"
#include "esphome/core/log.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
namespace everblu_cyble {

static const char *TAG = "cc1101";


// Instance SPI globale
static SPIComponent *spi_bus = nullptr;


// Broches CC1101
static uint8_t cs_pin = 5;


// --------------------------------------------------
// Gestion SPI bas niveau
// --------------------------------------------------

void cc1101_spi_begin(SPIComponent *spi, uint8_t cs)
{
    spi_bus = spi;
    cs_pin = cs;

    ESP_LOGI(TAG, "CC1101 SPI initialisé");
}


// Ecriture registre CC1101
void cc1101_write_reg(uint8_t addr, uint8_t value)
{
    if (spi_bus == nullptr)
        return;

    uint8_t data[2];

    data[0] = addr;
    data[1] = value;

    spi_bus->enable();
    spi_bus->write_array(data, 2);
    spi_bus->disable();
}


// Lecture registre CC1101
uint8_t cc1101_read_reg(uint8_t addr)
{
    if (spi_bus == nullptr)
        return 0;

    uint8_t tx = addr | READ_SINGLE;
    uint8_t rx = 0;

    spi_bus->enable();

    spi_bus->transfer_byte(tx);
    rx = spi_bus->transfer_byte(0);

    spi_bus->disable();

    return rx;
}


// Burst écriture
void cc1101_write_burst(uint8_t addr, uint8_t *buffer, uint8_t length)
{
    if (spi_bus == nullptr)
        return;

    spi_bus->enable();

    spi_bus->transfer_byte(addr | WRITE_BURST);

    for (uint8_t i = 0; i < length; i++)
    {
        spi_bus->transfer_byte(buffer[i]);
    }

    spi_bus->disable();
}


// Burst lecture
void cc1101_read_burst(uint8_t addr, uint8_t *buffer, uint8_t length)
{
    if (spi_bus == nullptr)
        return;

    spi_bus->enable();

    spi_bus->transfer_byte(addr | READ_BURST);

    for (uint8_t i = 0; i < length; i++)
    {
        buffer[i] = spi_bus->transfer_byte(0);
    }

    spi_bus->disable();
}


// Command strobe
void cc1101_strobe(uint8_t command)
{
    if (spi_bus == nullptr)
        return;

    spi_bus->enable();

    spi_bus->transfer_byte(command);

    spi_bus->disable();
}


// --------------------------------------------------
// Initialisation CC1101
// --------------------------------------------------

void cc1101_init()
{
    ESP_LOGI(TAG, "Initialisation CC1101");

    cc1101_reset();

    // Lecture version pour test
    uint8_t version = cc1101_read_reg(VERSION);

    ESP_LOGI(TAG, "CC1101 VERSION = 0x%02X", version);
}


}  // namespace everblu_cyble
}  // namespace esphome
