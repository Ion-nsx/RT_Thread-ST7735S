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

#ifndef ST7735S_CONF_H
#define ST7735S_CONF_H

#include <rtdevice.h>
#include "drv_common.h"
#include "stdint.h"
#include "stdio.h"


#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t

#ifndef ST7735S_SCREEN_MODE
#define ST7735S_SCREEN_MODE           VER_0_MODE
#endif
#ifndef ST7735S_SCREEN_WIDTH
#define ST7735S_SCREEN_WIDTH           128
#endif
#ifndef ST7735S_SCREEN_HIGH
#define ST7735S_SCREEN_HIGH           160
#endif
/*背景色*/
#ifndef ST7735S_BACK_COLOR
#define ST7735S_BACK_COLOR           0xFFFF
#endif
/*画笔颜色*/
#ifndef ST7735S_POINT_COLOR
#define ST7735S_POINT_COLOR           0x0000
#endif



#define ST7735S_SPI_BUS             "spi2"     //spi2总线
#define ST7735S_SPI_DEVICE_NAME     "spi20"

#define ST7735S_DC_PIN    GET_PIN(A, 5)  /*寄存器或数据引脚*/
#define ST7735S_RST_PIN   GET_PIN(A, 3) /*复位引脚*/
#define ST7735S_CS_PIN    GET_PIN(B, 12)    /*使能引脚*/
#define ST7735S_BLK_PIN   GET_PIN(A,4)   /*背光引脚*/



//扫描方向定义--扫描方式有不同规格，可能定义不左右和上下的参照方向不同，总结方式，只有一下八种

#define L2R_U2D  0 //从左到右,从上到下
#define L2R_D2U  1 //从左到右,从下到上
#define R2L_U2D  2 //从右到左,从上到下
#define R2L_D2U  3 //从右到左,从下到上

#define U2D_L2R  4 //从上到下,从左到右
#define U2D_R2L  5 //从上到下,从右到左
#define D2U_L2R  6 //从下到上,从左到右
#define D2U_R2L  7 //从下到上,从右到左


//画笔颜色
#define WHITE             0xFFFF
#define BLACK             0x0000
#define BLUE             0x001F
#define BRED             0xF81F
#define GRED             0xFFE0
#define GBLUE             0x07FF
#define RED             0xF800
#define MAGENTA         0xF81F
#define GREEN             0x07E0
#define CYAN             0x7FFF
#define YELLOW             0xFFE0
#define BROWN             0xBC40 //棕色
#define BRRED             0xFC07 //棕红色
#define GRAY             0x8430 //灰色
//GUI颜色
#define DARKBLUE         0x01CF    //深蓝色
#define LIGHTBLUE         0x7D7C    //浅蓝色
#define GRAYBLUE         0x5458 //灰蓝色
//以上三色为PANEL的颜色
#define LIGHTGREEN         0x841F //浅绿色
//#define LIGHTGRAY        0XEF5B //浅灰色(PANNEL)
#define LGRAY             0xC618 //浅灰色(PANNEL),窗体背景色
#define GRAY0            0xEF7D        //灰色0
#define GRAY1            0x8410        //灰色1
#define GRAY2            0x4208        //灰色2
#define LGRAYBLUE        0xA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0x2B12 //浅棕蓝色(选择条目的反色)

typedef enum {
    VER_0_MODE, /*竖屏模式0: 从上至下*/
    VER_1_MODE, /*竖屏模式1: 从下至上*/
    HOR_0_MODE, /*横屏屏模式0: 从左至右*/
    HOR_1_MODE  /*横屏屏模式1: 从右至左*/
} ST7735S_DIR_MODE;
struct ST7735S { /*ST7735S 总结构体*/
    struct {
        ST7735S_DIR_MODE screen_mode;
        uint16_t width; /*宽*/
        uint16_t height;  /*高*/
        uint16_t back_color; /*背景色*/
        uint16_t point_color; /*画笔颜色*/
        struct {
            uint16_t wramcmd; //开始写gram指令
            uint16_t setxcmd; //设置x坐标指令
            uint16_t setycmd; //设置y坐标指令
        } CMD;
    } CNF;

    struct {
        void (*_enter)(void);  ///< crtical section enter
        void (*_exit)(void);    ///< critial section exit
    } CRIS;

    struct {
        void (*_select)(void);

        void (*_deselect)(void);
    } CS; /*CS引脚*/
    struct {
        void (*_select_data)(void);

        void (*_select_reg)(void);
    } DC; /*数据或寄存器选择引脚*/
    struct {
        void (*_write_byte)(uint8_t dat); /*写字节*/
    } SPI; /*SPI数据接口*/

};
extern struct ST7735S ST7735S_DEV;

/*-----------------------------------ST7735S回调函数注册------------------------------------------------*/
void reg_st7735s_cris_cbfunc(void(*cris_en)(void), void(*cris_ex)(void));

void reg_st7735s_cs_cbfunc(void(*cs_sel)(void), void(*cs_desel)(void));

void reg_st7735s_dc_cbfunc(void(*dc_dat)(void), void(*dc_reg)(void));

void reg_st7735s_spi_cbfunc(void(*spi_write_byte)(uint8_t data));


/*-----------------------------------ST7735S回调函数注册--------END----------------------------------------*/
void st7735s_init(void);

#endif //STM32F407V4T6_RTOS_ST7735S_CONF_H


