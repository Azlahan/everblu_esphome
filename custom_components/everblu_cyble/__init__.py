import esphome.codegen as cg
import esphome.config_validation as cv

from esphome.components import sensor


DEPENDENCIES = [
    "sensor",
]


AUTO_LOAD = [
    "sensor",
]


CONFIG_SCHEMA = cv.All(
    sensor.CONFIG_SCHEMA,
)
