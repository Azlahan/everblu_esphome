import esphome.codegen as cg
import esphome.config_validation as cv

from esphome.components import spi

from . import sensor


DEPENDENCIES = [
    "spi",
    "sensor",
]


AUTO_LOAD = [
    "sensor",
]


CONFIG_SCHEMA = sensor.CONFIG_SCHEMA
