import esphome.codegen as cg
import esphome.config_validation as cv

from esphome.components import spi, sensor

from esphome.const import (
    CONF_ID,
)


DEPENDENCIES = [
    "spi",
    "sensor",
]


AUTO_LOAD = [
    "sensor",
]



everblu_cyble_ns = cg.esphome_ns.namespace(
    "everblu_cyble"
)


EverbluCyble = everblu_cyble_ns.class_(
    "EverbluCyble",
    cg.Component,
    sensor.Sensor,
)


CC1101 = everblu_cyble_ns.class_(
    "CC1101",
    cg.Component,
    spi.SPIDevice,
)



CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(EverbluCyble),

    }
).extend(
    spi.spi_device_schema()
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


    await spi.register_spi_device(
        var,
        config
    )