<<<<<<< HEAD
# RT_Thread-ST7735S
=======
# 基于RT-Thread 驱动ST7735S 1.8寸TFT 显示屏
---
**这是基于RT-Thread驱动ST7735S 的驱动**<br>
**由于发现找不到现成的基于rt thread的ST7735S的驱动，所以自己参考网上的各种示例写了一个.**<br>
**用的开发板是立创的STM32F407VET6天空星青春版:point_right:[官方主页](https://item.szlcsc.com/23849165.html?kw=%E5%A4%A9%E7%A9%BA%E6%98%9F&fromZone=s)**
## 1. 硬件参数
- **型号: ST7735S**<br>
- **尺寸: 1.8寸**<br>
- **分辨率: 128*160**<br>
- **颜色: 262144**<br>
- **通信协议: SPI**<br>
---
## 2. 引脚定义  
|引脚|引脚名|引脚号|
|:---:|:---:|:---:|
|CS|片选|PB12|
|DC|数据/命令|PA5|
|RST|复位|PA3|
|BLK|背光|PA4|
|SCLK|时钟|PB13|
|MOSI|数据|PB15|
|MISO|数据|NULL|
---
## 3. 使用方法  :question:
### 3.1 **在st7735s_conf.h中修改宏定义**:point_down:
```c
#define ST7735S_SPI_BUS             "spi2"     //修改成你在CUBEMX配置的SPI模式名.
#define ST7735S_SPI_DEVICE_NAME     "spi20"

#define ST7735S_DC_PIN    GET_PIN(A, 5)        /*寄存器或数据引脚*/
#define ST7735S_RST_PIN   GET_PIN(A, 3)        /*复位引脚*/
#define ST7735S_CS_PIN    GET_PIN(B, 12)       /*使能引脚*/
#define ST7735S_BLK_PIN   GET_PIN(A,4)         /*背光引脚*/
```
### 3.2 **在st7735s_device.c中修改DC引脚配置**:point_down:
```c
rt_err_t st7735s_device_init(const char *spi_dev_name) {
//将引脚修改成你定义的DC引脚
rt_hw_spi_device_attach(ST7735S_SPI_BUS, ST7735S_SPI_DEVICE_NAME, GPIOB, GPIO_PIN_12);

}
```
### 3.3 **在main.c中添加头文件并调用初始化函数**:point_down:
```c
#include "st7735s.h"      
int main(void)
{
    LCD_Init(); //LCD初始化
    LCD_ShowString(10, 10, 128, 160, 12, "ST7735&RTTHREAD", BLACK, WHITE)
    return RT_EOK;
}
```
---
## 4. 补充
**至于rtthread的配置SPI的内容，网上都有教程:point_right:[RT_Thread使用SPI设备]([https://mp.weixin.qq.com/s/s5IhxV2ooX3JN_X416nidA](https://blog.csdn.net/tigerots/article/details/107423633))，这里就不赘述了:blush::blush:**<br>
**配置完RT Thread的SPI再移植本驱动即可.**<br>

**没有移植显示中文的内容，也没有中文字库，如有需要可自行移植添加**<br>

***如有错误欢迎指正，本人也是新手在网上各种例程中东拼西凑出来的，所以代码可能不是很优雅:sob::sob:，但是能跑通，希望对大家有所帮助。***
>>>>>>> 2b36641 (First)
