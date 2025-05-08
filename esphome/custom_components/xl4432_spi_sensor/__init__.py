import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, spi
from esphome.const import CONF_ID

DEPENDENCIES = ['spi']
CODEOWNERS = ['@your_github_username']

xl4432_spi_sensor_ns = cg.esphome_ns.namespace('xl4432_spi_sensor')
Xl4432SPISensor = xl4432_spi_sensor_ns.class_('Xl4432SPISensor', sensor.Sensor, spi.SPIDevice)

CONFIG_SCHEMA = sensor.SENSOR_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(Xl4432SPISensor),
    cv.Optional('meter_id'): cv.ensure_list(cv.hex_uint8_t, cv.Length(min=3, max=3)),
}).extend(spi.spi_device_schema(cs_pin_required=True))

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield spi.register_spi_device(var, config)
    yield sensor.register_sensor(var, config)
    
    if 'meter_id' in config:
        meter_id = config['meter_id']
        cg.add(var.set_meter_id(meter_id))
