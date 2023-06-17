
#include "sw_i2c.h"

#include "rtos_pub.h"
#include "BkDriverGpio.h"



#define SW_I2C1_SCL_PIN     GPIO20
#define SW_I2C1_SDA_PIN     GPIO21

void ql_delay_us(uint32_t num)
{
    volatile INT32 i, j;

    for (i = 0; i < num; i++)
    {
        for (j = 0; j < 6; j++)
            ;
    }
}

static int sw_i2c_port_initial(void)
{
   
    BkGpioInitialize(SW_I2C1_SCL_PIN, OUTPUT_NORMAL);
    BkGpioInitialize(SW_I2C1_SDA_PIN, OUTPUT_NORMAL);
    BkGpioOutputHigh(SW_I2C1_SCL_PIN);
    BkGpioOutputHigh(SW_I2C1_SDA_PIN);
    ql_delay_us(SW_I2C_WAIT_TIME);
    return 0;
}

static void sw_i2c_port_delay_us(uint32_t us)
{
    ql_delay_us(us);
}

static int sw_i2c_port_io_ctl(uint8_t opt, void *param)
{
    int ret = -1;
    switch (opt)
    {
    case HAL_IO_OPT_SET_SDA_HIGH:
        BkGpioOutputHigh(SW_I2C1_SDA_PIN);
        break;
    case HAL_IO_OPT_SET_SDA_LOW:
        BkGpioOutputLow(SW_I2C1_SDA_PIN);
        break;
    case HAL_IO_OPT_GET_SDA_LEVEL:

        if (BkGpioInputGet(SW_I2C1_SDA_PIN))
        {
            ret = 1;
        }
        else
        {
            ret = 0;
        }

        break;
    case HAL_IO_OPT_SET_SDA_INPUT:
        BkGpioInitialize(SW_I2C1_SDA_PIN, INPUT_PULL_UP);
        break;
    case HAL_IO_OPT_SET_SDA_OUTPUT:
        BkGpioInitialize(SW_I2C1_SDA_PIN, OUTPUT_NORMAL);
        break;
    case HAL_IO_OPT_SET_SCL_HIGH:
        BkGpioOutputHigh(SW_I2C1_SCL_PIN);
        break;
    case HAL_IO_OPT_SET_SCL_LOW:
        BkGpioOutputLow(SW_I2C1_SCL_PIN);
        break;
    case HAL_IO_OPT_GET_SCL_LEVEL:
        if (BkGpioInputGet(SW_I2C1_SCL_PIN))
        {
            ret = 1;
        }
        else
        {
            ret = 0;
        }
        break;
    case HAL_IO_OPT_SET_SCL_INPUT:
        BkGpioInitialize(SW_I2C1_SCL_PIN, INPUT_PULL_UP);
        break;
    case HAL_IO_OPT_SET_SCL_OUTPUT:
        BkGpioInitialize(SW_I2C1_SCL_PIN, OUTPUT_NORMAL);
        break;
    default:
        break;
    }
    return ret;
}


sw_i2c_t sw_i2c_bk7231n = {
    .hal_init = sw_i2c_port_initial,
    .hal_io_ctl = sw_i2c_port_io_ctl,
    .hal_delay_us = sw_i2c_port_delay_us,
    };
