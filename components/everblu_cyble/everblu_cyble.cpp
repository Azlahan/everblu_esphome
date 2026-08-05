#include "everblu_cyble.h"

#include "protocol.h"

#include "esphome/core/log.h"



namespace esphome {
    namespace everblu_cyble {



        static const char *TAG = "everblu_cyble";




        void EverbluCyble::set_meter_id(
                uint32_t id
        )
        {
            this->meter_id_ = id;
        }





        void EverbluCyble::set_cc1101(
                CC1101 *radio
        )
        {
            this->cc1101_ = radio;
        }





        void EverbluCyble::setup()
        {

            ESP_LOGI(TAG,
                     "Initialisation EverBlu");


            ESP_LOGI(TAG,
                     "Compteur : %lu",
                     this->meter_id_);




            if (this->cc1101_ != nullptr)
            {


                ESP_LOGI(TAG,
                         "Initialisation CC1101");


                this->cc1101_->setup();



                ESP_LOGI(TAG,
                         "Version CC1101 : 0x%02X",
                         this->cc1101_->get_version());



                this->cc1101_->rx();

            }
            else
            {

                ESP_LOGW(TAG,
                         "CC1101 non connecté");

            }





            protocol_init();



            this->initialized_ = true;


        }







        void EverbluCyble::loop()
        {

            if (!this->initialized_)
                return;



            if (this->cc1101_ == nullptr)
                return;




            uint32_t now = millis();



            if (now - this->last_read_ < 1000)
                return;



            this->last_read_ = now;





            uint8_t buffer[CC1101_FIFO_SIZE];



            uint8_t length =
                    this->cc1101_->read_fifo(
                            buffer
                    );



            if (length == 0)
                return;





            ESP_LOGD(TAG,
                     "Trame reçue %u octets",
                     length);





            EverbluData data;



            if (!protocol_decode(
                    buffer,
                    length,
                    &data))
            {
                return;
            }






            if (!data.valid)
                return;






            if (this->meter_id_ != 0 &&
                data.meter_id != this->meter_id_)
            {
                return;
            }







            float volume =
                    data.index / 1000.0f;





            ESP_LOGI(TAG,
                     "Index : %.3f m3",
                     volume);





            this->publish_state(
                    volume
            );

        }



    } // namespace everblu_cyble
} // namespace esphome