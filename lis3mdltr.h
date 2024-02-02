#pragma once
struct lis3mdltr_t {
    uint8_t bus_address;
};
typedef struct lis3mdltr_t lis3mdltr;

#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define INT_CFG 0x30

#define FULLSCALE_OFFSET 5
#define FULLSCALE_BITS 2
uint8_t lis3mdltr_get_full_scale_configuration(lis3mdltr *instance) {
    uint8_t ctrl_reg2 = 0;
    i2c_read(instance->bus_address, CTRL_REG2, 1, &ctrl_reg2);

    uint8_t full_scale_config = (ctrl_reg2 >> FULLSCALE_OFFSET) & ((1 << FULLSCALE_BITS) - 1);
    
    return full_scale_config;
}

#define ODR_OFFSET 2
#define ODR_BITS 3
uint8_t lis3mdltr_get_output_data_rate(lis3mdltr *instance) {
    uint8_t ctrl_reg1 = 0;
    i2c_read(instance->bus_address, CTRL_REG1, 1, &ctrl_reg1);
    uint8_t odr_config = (ctrl_reg1 >> ODR_OFFSET) & ((1 << ODR_BITS) - 1);
    
    return odr_config;
}
uint8_t lis3mdltr_set_output_data_rate(lis3mdltr *instance, uint8_t odr_config) {
    uint8_t ctrl_reg1 = 0;
    i2c_read(instance->bus_address, CTRL_REG1, 1, &ctrl_reg1);
    ctrl_reg1 &= ~(0b111 << ODR_OFFSET);
    ctrl_reg1 |= (odr_config << ODR_OFFSET);
    i2c_write(instance->bus_address, CTRL_REG1, 1, &ctrl_reg1);
    return 0;
}

#define IEN_OFFSET 0
#define IEN_BITS 1
void lis3mdltr_enable_int_pin_interrupt(lis3mdltr *instance) {
    uint8_t int_cfg = 0;
    i2c_read(instance->bus_address, INT_CFG, 1, &int_cfg);
    int_cfg |= (1 << IEN_OFFSET);
    i2c_write(instance->bus_address, INT_CFG, 1, &int_cfg);
}
void lis3mdltr_disable_int_pin_interrupt(lis3mdltr *instance) {
    uint8_t int_cfg = 0;
    i2c_read(instance->bus_address, INT_CFG, 1, &int_cfg);
    int_cfg &= ~(1 << IEN_OFFSET);
    i2c_write(instance->bus_address, INT_CFG, 1, &int_cfg);
}

#define AXIS_X 0
#define AXIS_Y 1
#define AXIS_Z 2
int16_t lis3mdltr_read_axis_value(uint8_t axis, lis3mdltr *instance) {
    uint8_t low_address = 0;
    uint8_t high_address = 0;
    if(axis == AXIS_X) {
        low_address = 0x28;
        high_address = 0x29;
    } else if(axis == AXIS_Y) {
        low_address = 0x2A;
        high_address = 0x2B;
    } else if(axis == AXIS_Z) {
        low_address = 0x2C;
        high_address = 0x2D;
    }

    uint8_t low = 0;
    uint8_t high = 0;
    i2c_read(instance->bus_address, low_address, 1, &low);
    i2c_read(instance->bus_address, high_address, 1, &high);

    // We read the bytes as raw data (unsigned) but combine them into a signed, two's complement value
    int16_t value = (high << 8) | low; 
    return value;
}