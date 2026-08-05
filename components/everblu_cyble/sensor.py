import esphome.codegen as cg
import esphome.config_validation as cv

from esphome.components import sensor

from esphome.const import (
    CONF_ID,
    DEVICE_CLASS_WATER,
    STATE_CLASS_TOTAL_INCREASING,
)


# Namespace C++
everblu_cyble_ns = cg.esphome_ns.namespace(
    "everblu_cyble"
)


# Classe C++
EverbluCyble = everblu_cyble_ns.class_(
    "EverbluCyble",
    cg.Component,
    sensor.Sensor,
)


CONF_METER_ID = "meter_id"


CONFIG_SCHEMA = sensor.sensor_schema(
    EverbluCyble,
    unit_of_measurement="m³",
    accuracy_decimals=3,
    device_class=DEVICE_CLASS_WATER,
    state_class=STATE_CLASS_TOTAL_INCREASING,
).extend(
    {
        cv.GenerateID(): cv.declare_id(EverbluCyble),

        cv.Required(CONF_METER_ID): cv.uint32_t,
    }
).extend(
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


    cg.add(
        var.set_meter_id(
            config[CONF_METER_ID]
        )
    )