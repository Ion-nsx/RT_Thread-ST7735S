/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-05-19     Administrator       the first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include <drv_common.h>
#include <board.h>
#include "drv_spi.h"
#include "st7735s.h"
#define DBG_LVL DBG_LOG
#define DBG_TAG  "main"
#include <rtdbg.h>

static struct rt_spi_device *spi_dev_st7735s=NULL; //设备句柄
static void spi_cris_enter(void) { rt_spi_take_bus(spi_dev_st7735s); }
static void spi_cris_exit(void) { rt_spi_release_bus(spi_dev_st7735s); }
static void spi_cs_deselect(void) { rt_spi_release(spi_dev_st7735s); }
static void spi_cs_select(void) { rt_spi_take(spi_dev_st7735s); }
static void dc_dat_select(void) { rt_pin_write(ST7735S_DC_PIN, PIN_HIGH); }
static void dc_reg_select(void) { rt_pin_write(ST7735S_DC_PIN, PIN_LOW); }
static void spi_write_byte(uint8_t data) { rt_spi_send(spi_dev_st7735s, &data, 1); }

rt_err_t st7735s_device_init(const char *spi_dev_name) {
    //将spi设备挂载到总线
    rt_hw_spi_device_attach(ST7735S_SPI_BUS, ST7735S_SPI_DEVICE_NAME, GPIOB, GPIO_PIN_12);

    /* 查找 spi 设备获取设备句柄 */
    spi_dev_st7735s = (struct rt_spi_device *) rt_device_find(ST7735S_SPI_DEVICE_NAME);
    if (spi_dev_st7735s == NULL) {
        LOG_E("Failed to attach the spi device.");
        return -RT_ERROR;
    } else {
        LOG_D("find device ok.");
        //配置spi参数
        struct rt_spi_configuration cfg;
        {
            cfg.data_width = 8;//数据宽度为八位
            cfg.mode = RT_SPI_MASTER | RT_SPI_MODE_0 | RT_SPI_MSB;
            cfg.max_hz = 21 * 1000 * 1000;//最大波特率,因为在cubemx配置分频后，spi2的波特率是4.5M，所以这里最大就写5了
        }

        rt_spi_configure(spi_dev_st7735s, &cfg);
    }
    return RT_EOK;
}

static void st7735s_callback_register() {
    /* register critical section callback function */
    reg_st7735s_cris_cbfunc(spi_cris_enter, spi_cris_exit);
    /* register SPI device CS select callback function */
    reg_st7735s_cs_cbfunc(spi_cs_select, spi_cs_deselect);

    /* register DC select callback function */
    reg_st7735s_dc_cbfunc(dc_dat_select, dc_reg_select);
    /* register SPI write data callback function */
    reg_st7735s_spi_cbfunc(spi_write_byte);
}
//********************************************************************************/
//函数：void LCD_SoftRest(void)
//函数功能：给屏幕发命令，执行软复位命令
//LCD开启显示
//*******************************************************************/
void LCD_SoftRest(void) {
    rt_pin_write(ST7735S_RST_PIN, PIN_LOW);
    rt_thread_mdelay(100);
    rt_pin_write(ST7735S_RST_PIN, PIN_HIGH);
    rt_pin_write(ST7735S_BLK_PIN, PIN_HIGH);
    rt_thread_mdelay(1000);
}


void st7735s_init(void) {
    rt_err_t result = RT_EOK;
    /*初始化对应的引脚*/
    rt_pin_mode(ST7735S_DC_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(ST7735S_RST_PIN, PIN_MODE_OUTPUT);
    //rt_pin_mode(ST7735S_CS_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(ST7735S_BLK_PIN, PIN_MODE_OUTPUT);

    result = st7735s_device_init(ST7735S_SPI_DEVICE_NAME);
    if (result != RT_EOK) goto __exit;

    /* 回调函数注册 */
    st7735s_callback_register();

    __exit:
    if (result == RT_EOK) {
        LOG_I("st7735s_init initialize success.");
    } else {
        LOG_I("st7735s_init initialize err:%d.", result);
    }
}
