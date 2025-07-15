# components/lumentree_ble_sensor/sensor.py

import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID, CONF_VOLTAGE, CONF_CURRENT, CONF_POWER
from . import LumentreeBLESensor

CONFIG_SCHEMA = sensor.PLATFORM_SCHEMA.extend({
    cv.GenerateID(CONF_ID): cv.use_id(LumentreeBLESensor),
    cv.Optional(CONF_VOLTAGE): sensor.sensor_schema(),
    cv.Optional(CONF_CURRENT): sensor.sensor_schema(),
    cv.Optional(CONF_POWER): sensor.sensor_schema(),
})

async def to_code(config):
    hub = await cg.get_variable(config[CONF_ID])

    if CONF_VOLTAGE in config:
        conf = config[CONF_VOLTAGE]
        sens = await sensor.new_sensor(conf)
        cg.add(hub.voltage_sensor, sens)

    if CONF_CURRENT in config:
        conf = config[CONF_CURRENT]
        sens = await sensor.new_sensor(conf)
        cg.add(hub.current_sensor, sens)

    if CONF_POWER in config:
        conf = config[CONF_POWER]
        sens = await sensor.new_sensor(conf)
        cg.add(hub.power_sensor, sens)
