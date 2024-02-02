# AAC-Clydespace Avionics Software Challenge
You are given the LIS3MDLTR 3-Axis Magnetometer sensor. The data sheet is
located at `doc/lism3mdl.pdf`

## Task Description
You must use the C API defined in `i2c.h` to operate on an I2C bus.

We provide example stub implementations of this API in `i2c.c`. You are free to
extend the provided stub functions for the API.

Please write a device driver that implements the following API:

- [x] Get the full-scale configuration
- [x] Get and set the output data rate
- [x] Enable or disable the interrupt pin
- [x] Read the output data of a specified axis

## Development
You are provided this minimal repository, `aac-code-challenge`, please perform
your work on branch `<candidate_name>`

- [x] Created and provided the chris_de_claverie branch

Documentation can be found in `aac-code-challenge/doc`

Once complete, please repackage and email back this repo to your interviewers

## Scope
You shouldn't need to spend more than a couple of hours on the task.

This is not a closed book assessment.

## Extra Thoughts
If you have time, answer the following questions:
- What changes you would make to this interfaces for use in an RTOS
environment?
    - First and foremost the I2C bus or device should be protected against race conditions. I can see two main possibilities :
        - Use a dedicated thread for I2C communication and get/receive data through RTOS inter-thread-communication primitives
        - Use a mutex or other locking mecanism in the I2C access functions
        - Answering this trade-off is out-of-scope here and would need additional context
    - The I2C API could be made asynchronous to avoid blocking the calling thread. This might also be imposed depending on the I2C implementation (e.g. DMA)
- How might the I2C API be improved
    - The I2C API could be by acting on I2C bus objects instead of having to pass the bus address to each function. This would hide the implementation details and help in the review process
    - A timeout parameter would be a good addition to the I2C read/write functions. The default timeout (either fixed or infinity) might not be safe or fit the needs of the caller

