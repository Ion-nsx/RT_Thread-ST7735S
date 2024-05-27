//
// Created by shchl on 2024/2/28.
//

#ifndef ST7735S_H
#define ST7735S_H

#include "st7735s_conf.h"




void ST7735S_write_dat_u8(uint8_t dat);

void ST7735S_write_dat_u16(uint16_t dat);

void ST7735S_write_reg_val(uint16_t reg, uint16_t dat);

void ST7735S_write_reg(uint8_t dat);

void LCD_Init(void);//初始化
void LCD_SoftRest(void); //软复位
void LCD_DisplayOn(void);   //开显示
void LCD_DisplayOff(void);  //关显示
void LCD_Clear(uint16_t Color); //清屏
void LCD_Display_Dir(ST7735S_DIR_MODE dir);//设置屏幕显示方向
void LCD_WriteRAM_Prepare(void);  //开始写GRAM  命令
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);    //设置光标
void LCD_DrawPoint(uint16_t x, uint16_t y);//画点--使用设置的笔尖颜色
void LCD_Set_Window(uint16_t sx, uint16_t sy, uint16_t width, uint16_t height); //设置窗口
void LCD_Fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color);//填充指定颜色
void LCD_WriteRAM(uint16_t RGB_Code);//LCD写GRAM
void LCD_Fast_DrawPoint(uint16_t x,uint16_t y,uint16_t color);  //快速画点--使用当前输入颜色参数
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t Color);
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t Color);  //画线
void LCD_Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r, uint16_t Color);          //画圆
void LCD_ShowNum(u16 x,u16 y,int32_t num,u8 len,u8 size);
void LCD_ShowChar(unsigned short x, unsigned short y, unsigned char num, unsigned char size, unsigned char mode, unsigned short pen_color, unsigned short back_color);
void LCD_ShowString(unsigned short x, unsigned short y, unsigned short width, unsigned short height, unsigned char size, unsigned char* p, unsigned short pen_color, unsigned short back_color);

#endif //STM32F407V4T6_RTOS_ST7735S_H


