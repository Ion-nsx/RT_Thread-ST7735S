/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-05-19     Administrator       the first version
 */
//
// Created by shchl on 2024/2/28.
//
#include "st7735s_conf.h"


struct ST7735S ST7735S_DEV = {
        .CNF={
                .screen_mode =ST7735S_SCREEN_MODE,
                .width=ST7735S_SCREEN_WIDTH,
                .height = ST7735S_SCREEN_HIGH,
                .back_color = ST7735S_BACK_COLOR,
                .point_color = ST7735S_POINT_COLOR,
        },
        .SPI={NULL},
        .CS ={NULL, NULL},
        .DC={NULL, NULL},
        .CRIS={NULL, NULL}
};


void reg_st7735s_cris_cbfunc(void(*cris_en)(void), void(*cris_ex)(void)) {
    ST7735S_DEV.CRIS._enter = cris_en;
    ST7735S_DEV.CRIS._exit = cris_ex;
}

void reg_st7735s_cs_cbfunc(void(*cs_sel)(void), void(*cs_desel)(void)) {
    ST7735S_DEV.CS._select = cs_sel;
    ST7735S_DEV.CS._deselect = cs_desel;
}

void reg_st7735s_dc_cbfunc(void(*dc_dat)(void), void(*dc_reg)(void)) {
    ST7735S_DEV.DC._select_reg = dc_reg;
    ST7735S_DEV.DC._select_data = dc_dat;
}

void reg_st7735s_spi_cbfunc(void(*spi_write_byte)(uint8_t data)) {
    ST7735S_DEV.SPI._write_byte = spi_write_byte;
}


