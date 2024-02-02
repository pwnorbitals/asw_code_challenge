#pragma once
#include "lis3mdltr.h"
#include "stdio.h"

int lis3mdltr_test(lis3mdltr *instance) {

    // Read & write values needed during the tests
    uint8_t test_reg = 1;
    uint8_t test_val = 0b11111111;

    // Test I2C read from buffer
    i2c_read(instance->bus_address, CTRL_REG2, 1, &test_reg);
    assert(test_reg == 0);

    // Test I2C write to buffer
    i2c_write(instance->bus_address, CTRL_REG2, 1, &test_val);
    i2c_read(instance->bus_address, CTRL_REG2, 1, &test_reg);
    assert(test_reg == 0b11111111);

    // Test full scale configuration read in multiple different configurations
    uint8_t full_scale_config = 0;
    test_val = 0b11111111;
    i2c_write(instance->bus_address, CTRL_REG2, 1, &test_val);
    full_scale_config = lis3mdltr_get_full_scale_configuration(instance);
    assert(full_scale_config == 0b11);
    test_val = 0b00000000;
    i2c_write(instance->bus_address, CTRL_REG2, 1, &test_val);
    full_scale_config = lis3mdltr_get_full_scale_configuration(instance);
    assert(full_scale_config == 0b00);
    test_val = 0b01010101;
    i2c_write(instance->bus_address, CTRL_REG2, 1, &test_val);
    full_scale_config = lis3mdltr_get_full_scale_configuration(instance);
    assert(full_scale_config == 0b10);
    test_val = 0b10101010;
    i2c_write(instance->bus_address, CTRL_REG2, 1, &test_val);
    full_scale_config = lis3mdltr_get_full_scale_configuration(instance);
    assert(full_scale_config == 0b01);

    // Test getting the output data rate
    uint8_t odr_config = 0;
    test_val = 0b11111111;
    i2c_write(instance->bus_address, CTRL_REG1, 1, &test_val);
    odr_config = lis3mdltr_get_output_data_rate(instance);
    assert(odr_config == 0b111);
    test_val = 0b00000000;
    i2c_write(instance->bus_address, CTRL_REG1, 1, &test_val);
    odr_config = lis3mdltr_get_output_data_rate(instance);
    assert(odr_config == 0b000);
    test_val = 0b01010101;
    i2c_write(instance->bus_address, CTRL_REG1, 1, &test_val);
    odr_config = lis3mdltr_get_output_data_rate(instance);
    assert(odr_config == 0b101);
    test_val = 0b10101010;
    i2c_write(instance->bus_address, CTRL_REG1, 1, &test_val);
    odr_config = lis3mdltr_get_output_data_rate(instance);
    assert(odr_config == 0b010);

    // Test setting the output data rate
    test_val = 0b111;
    lis3mdltr_set_output_data_rate(instance, test_val);
    odr_config = lis3mdltr_get_output_data_rate(instance);
    assert(odr_config == 0b111);
    test_val = 0b000;
    lis3mdltr_set_output_data_rate(instance, test_val);
    odr_config = lis3mdltr_get_output_data_rate(instance);
    assert(odr_config == 0b000);
    test_val = 0b101;
    lis3mdltr_set_output_data_rate(instance, test_val);
    odr_config = lis3mdltr_get_output_data_rate(instance);
    assert(odr_config == 0b101);
    test_val = 0b010;
    lis3mdltr_set_output_data_rate(instance, test_val);
    odr_config = lis3mdltr_get_output_data_rate(instance);
    assert(odr_config == 0b010);

    // Test enabling and disabling the interrupt pin
    lis3mdltr_enable_int_pin_interrupt(instance);
    i2c_read(instance->bus_address, INT_CFG, 1, &test_reg);
    assert(test_reg == 0b1);
    lis3mdltr_disable_int_pin_interrupt(instance);
    i2c_read(instance->bus_address, INT_CFG, 1, &test_reg);
    assert(test_reg == 0b0);

    // TODO : Check with Systems if we need to change the interrupt threshold level in flight. If so, we need to implement functions to set the threshold levels (looks easy but would add maintenance burden if useless)

    // Test reading data from the different axes
    int16_t example_value = 0;
    example_value = 100;
    uint8_t (*example_value_bytes)[2]  = (uint8_t (*)[2]) &example_value;
    i2c_write(instance->bus_address, 0x28, 2, *example_value_bytes);
    int16_t read_value = lis3mdltr_read_axis_value(AXIS_X, instance);
    assert(read_value == example_value);
    example_value = -100;
    i2c_write(instance->bus_address, 0x28, 2, *example_value_bytes);
    read_value = lis3mdltr_read_axis_value(AXIS_X, instance);
    assert(read_value == example_value);
    example_value = 100;
    i2c_write(instance->bus_address, 0x2A, 2, *example_value_bytes);
    read_value = lis3mdltr_read_axis_value(AXIS_Y, instance);
    assert(read_value == example_value);
    example_value = -100;
    i2c_write(instance->bus_address, 0x2A, 2, *example_value_bytes);
    read_value = lis3mdltr_read_axis_value(AXIS_Y, instance);
    assert(read_value == example_value);
    example_value = 100;
    i2c_write(instance->bus_address, 0x2C, 2, *example_value_bytes);
    read_value = lis3mdltr_read_axis_value(AXIS_Z, instance);
    assert(read_value == example_value);
    example_value = -100;
    i2c_write(instance->bus_address, 0x2C, 2, *example_value_bytes);
    read_value = lis3mdltr_read_axis_value(AXIS_Z, instance);
    assert(read_value == example_value);
    





    printf("Test passed\n");
    return 0;
};