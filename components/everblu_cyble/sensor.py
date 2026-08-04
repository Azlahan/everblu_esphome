import esphome.codegen as cg
import esphome.config_validation as cv

from esphome.components import sensor

from esphome.const import (
    CONF_ID,
    DEVICE_CLASS_WATER,
    STATE_CLASS_TOTAL_INCREASING,
)

from esphome import pins



# Namespace C++
everblu_cyble_ns = cg.esphome_ns.namespace(
    "everblu_cyble"
)


EverbluCyble = everblu_cyble_ns.class_(
    "EverbluCyble",
    cg.Component,
    sensor.Sensor,
)



# Configuration YAML

CONF_METER_ID = "meter_id"
CONF_CS_PIN = "cs_pin"
CONF_GDO0_PIN = "gdo0_pin"
CONF_GDO2_PIN = "gdo2_pin"



CONFIG_SCHEMA = sensor.sensor_schema(
    EverbluCyble,

    unit_of_measurement="m³",

    accuracy_decimals=3,

    device_class=DEVICE_CLASS_WATER,

    state_class=STATE_CLASS_TOTAL_INCREASING,

).extend({

    # Identifiant compteur EverBlu
    cv.Required(CONF_METER_ID):
        cv.uint32_t,


    # CSN CC1101
    cv.Required(CONF_CS_PIN):
        pins.gpio_output_pin_schema,


    # GDO0 CC1101
    cv.Optional(CONF_GDO0_PIN):
        pins.internal_gpio_input_pin_schema,


    # GDO2 CC1101
    cv.Optional(CONF_GDO2_PIN):
        pins.internal_gpio_input_pin_schema,


}).extend(
    cv.COMPONENT_SCHEMA
)




async def to_code(config):


    var = cg.new_Pvariable(
        config[CONF_ID]
    )


    await cg.register_component(
        var,
        config
    )


    await sensor.register_sensor(
        var,
        config
    )



    # Identifiant compteur

    cg.add(
        var.set_meter_id(
            config[CONF_METER_ID]
        )
    )



    # CS CC1101

    cs_pin = await cg.gpio_pin_expression(
        config[CONF_CS_PIN]
    )


    cg.add(
        var.set_cs_pin(
            cs_pin
        )
    )



    # GDO0 CC1101

    if CONF_GDO0_PIN in config:

        gdo0_pin = await cg.gpio_pin_expression(
            config[CONF_GDO0_PIN]
        )


        cg.add(
            var.set_gdo0_pin(
                gdo0_pin
            )
        )



    # GDO2 CC1101

    if CONF_GDO2_PIN in config:

        gdo2_pin = await cg.gpio_pin_expression(
            config[CONF_GDO2_PIN]
        )


        cg.add(
            var.set_gdo2_pin(
                gdo2_pin
            )
        )
