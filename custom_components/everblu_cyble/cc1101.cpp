#include "cc1101.h"

#include "esphome/core/log.h"


namespace esphome {
namespace everblu_cyble {


static const char *TAG = "cc1101";


// Initialisation wrapper ESPHome
void cc1101_component_init()
{
    ESP_LOGI(TAG, "Initialisation wrapper CC1101");

    cc1101_init();


    uint8_t version = cc1101_get_version();


    ESP_LOGI(TAG,
             "CC1101 VERSION = 0x%02X",
             version);
}


// Test lecture radio
bool cc1101_component_test()
{
    uint8_t version = cc1101_get_version();

    if (version == 0x00 || version == 0xFF)
    {
        ESP_LOGE(TAG,
                 "CC1101 non détecté");
        return false;
    }


    ESP_LOGI(TAG,
             "CC1101 détecté");

    return true;
}


} // namespace everblu_cyble
} // namespace esphome
