import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_BLE_CLIENT_ID, CONF_UPDATE_INTERVAL
from esphome.components import ble_client

lumentree_ble_sensor_ns = cg.esphome_ns.namespace('lumentree_ble_sensor')
LumentreeBLESensor = lumentree_ble_sensor_ns.class_('LumentreeBLESensor', cg.Component, ble_client.BLEClientListener)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(LumentreeBLESensor),
    cv.Required(CONF_BLE_CLIENT_ID): cv.use_id(ble_client.BLEClient),
    cv.Optional(CONF_UPDATE_INTERVAL, default="10s"): cv.update_interval,
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    ble_client_ = await cg.get_variable(config[CONF_BLE_CLIENT_ID])
    cg.add(var.set_ble_client(ble_client_))
    
    cg.add(var.set_update_interval(config[CONF_UPDATE_INTERVAL]))