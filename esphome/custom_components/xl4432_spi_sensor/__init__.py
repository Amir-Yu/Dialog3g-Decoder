import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, spi
from esphome.const import CONF_ID, CONF_METER_ID

xl4432_spi_sensor_ns = cg.esphome_ns.namespace('xl4432_spi_sensor')
Xl4432SPISensor = xl4432_spi_sensor_ns.class_('Xl4432SPISensor', sensor.Sensor, spi.SPIDevice)

CONFIG_SCHEMA = sensor.SENSOR_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(Xl4432SPISensor),
}).extend(spi.spi_device_schema())

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield spi.register_spi_device(var, config)
    yield sensor.register_sensor(var, config)
    
    if CONF_METER_ID in config:
        meter_id = config[CONF_METER_ID]
        cg.add(var.set_meter_id(meter_id))
