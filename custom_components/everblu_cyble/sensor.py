import esphome.codegen as cg
import esphome.config_validation as cv

from esphome.components import sensor

from esphome.const import (
    CONF_ID,
    DEVICE_CLASS_BATTERY,
    DEVICE_CLASS_SIGNAL_STRENGTH,
    STATE_CLASS_TOTAL_INCREASING,
    UNIT_PERCENT,
    UNIT_DB,
)

from esphome import pins


# Namespace C++
everblu_cyble_ns = cg.esphome_ns.namespace("everblu_cyble")


EverbluCyble = everblu_cyble_ns.class_(
    "EverbluCyble",
    cg.Component,
)


CONF_CS_PIN = "cs_pin"
CONF_INDEX = "index"
CONF_BATTERY = "battery"
CONF_RSSI = "rssi"



CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(EverbluCyble),

        cv.Required(CONF_CS_PIN): pins.gpio_output_pin_schema,


        cv.Optional(CONF_INDEX): sensor.sensor_schema(
            unit_of_measurement="m³",
            state_class=STATE_CLASS_TOTAL_INCREASING,
        ),


        cv.Optional(CONF_BATTERY): sensor.sensor_schema(
            unit_of_measurement=UNIT_PERCENT,
            device_class=DEVICE_CLASS_BATTERY,
        ),


        cv.Optional(CONF_RSSI): sensor.sensor_schema(
            unit_of_measurement=UNIT_DB,
            device_class=DEVICE_CLASS_SIGNAL_STRENGTH,
        ),
    }
).extend(cv.COMPONENT_SCHEMA)



async def to_code(config):

    var = cg.new_Pvariable(
        config[CONF_ID]
    )


    await cg.register_component(
        var,
        config
    )


    # GPIO CS CC1101

    cs_pin = await cg.gpio_pin_expression(
        config[CONF_CS_PIN]
    )

    cg.add(
        var.set_cs_pin(cs_pin)
    )



    # Index compteur

    if CONF_INDEX in config:

        sens = await sensor.new_sensor(
            config[CONF_INDEX]
        )

        cg.add(
            var.set_index_sensor(sens)
        )



    # Batterie

    if CONF_BATTERY in config:

        sens = await sensor.new_sensor(
            config[CONF_BATTERY]
        )

        cg.add(
            var.set_battery_sensor(sens)
        )



    # RSSI

    if CONF_RSSI in config:

        sens = await sensor.new_sensor(
            config[CONF_RSSI]
        )

        cg.add(
            var.set_rssi_sensor(sens)
        )
