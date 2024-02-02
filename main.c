#include <assert.h>

#include "i2c.h"
#include "lis3mdltr.h"
#include "test.h"

int main() {

    lis3mdltr sensor = (lis3mdltr) {
        .bus_address = 0x00,
    };

    int success = lis3mdltr_test(&sensor);
    assert(success == 0); 

    return success;
}