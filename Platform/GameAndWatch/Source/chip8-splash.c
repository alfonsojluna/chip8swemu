#include "chip8-splash.h"
#include "chip8-lcd.h"
#include "stm32h7xx_hal.h"


static const uint8_t splash[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x03, 0xc0, 0x1e, 0x00, 0x03, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0x9f, 0xfc,
    0x00, 0x03, 0xc0, 0x1e, 0x00, 0x03, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0x9f, 0xfc,
    0x00, 0x03, 0xc0, 0x1e, 0x00, 0x03, 0xff, 0x80, 0x00, 0xf0, 0x00, 0x00, 0x03, 0xff, 0x9f, 0xfc,
    0x00, 0x03, 0xc0, 0x1e, 0x00, 0x03, 0xff, 0x80, 0x00, 0xf0, 0x00, 0x00, 0x03, 0xff, 0x9f, 0xfc,
    0x00, 0x03, 0xc0, 0x00, 0x00, 0x03, 0xc7, 0x80, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x07, 0x80, 0x3c,
    0x00, 0x03, 0xc0, 0x00, 0x00, 0x03, 0xc7, 0x80, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x07, 0x80, 0x3c,
    0x7f, 0xf3, 0xff, 0x9e, 0x7f, 0xf3, 0xc7, 0x9f, 0xfc, 0xff, 0x9f, 0xff, 0xe0, 0x07, 0x80, 0x3c,
    0x7f, 0xf3, 0xff, 0x9e, 0x7f, 0xf3, 0xc7, 0x9f, 0xfc, 0xff, 0x9f, 0xff, 0xe0, 0x07, 0x80, 0x3c,
    0x7f, 0xf3, 0xff, 0x9e, 0x7f, 0xf3, 0xff, 0x9f, 0xfc, 0xff, 0x9f, 0xff, 0xe0, 0x07, 0x80, 0x3c,
    0x7f, 0xf3, 0xff, 0x9e, 0x7f, 0xf3, 0xff, 0x9f, 0xfc, 0xff, 0x9f, 0xff, 0xe3, 0xff, 0x9f, 0xfc,
    0x78, 0xf3, 0xc7, 0x9e, 0x78, 0xf3, 0xff, 0x9e, 0x00, 0xf0, 0x1e, 0x79, 0xe3, 0xff, 0x9f, 0xfc,
    0x78, 0xf3, 0xc7, 0x9e, 0x78, 0xf3, 0xff, 0x9e, 0x00, 0xf0, 0x1e, 0x79, 0xe3, 0xff, 0x9f, 0xfc,
    0x78, 0x03, 0xc7, 0x9e, 0x78, 0xf3, 0xc7, 0x9f, 0xfc, 0xf0, 0x1e, 0x79, 0xe3, 0xff, 0x9f, 0xfc,
    0x78, 0x03, 0xc7, 0x9e, 0x78, 0xf3, 0xc7, 0x9f, 0xfc, 0xf0, 0x1e, 0x79, 0xe0, 0x07, 0x9e, 0x00,
    0x78, 0x03, 0xc7, 0x9e, 0x78, 0xf3, 0xc7, 0x9f, 0xfc, 0xf0, 0x1e, 0x79, 0xe0, 0x07, 0x9e, 0x00,
    0x78, 0xf3, 0xc7, 0x9e, 0x78, 0xf3, 0xc7, 0x80, 0x3c, 0xf0, 0x1e, 0x79, 0xe0, 0x07, 0x9e, 0x00,
    0x78, 0xf3, 0xc7, 0x9e, 0x78, 0xf3, 0xc7, 0x80, 0x3c, 0xf0, 0x1e, 0x79, 0xe0, 0x07, 0x9e, 0x00,
    0x7f, 0xf3, 0xc7, 0x9e, 0x7f, 0xf3, 0xff, 0x9f, 0xfc, 0xff, 0x9e, 0x79, 0xe3, 0xff, 0x9f, 0xfc,
    0x7f, 0xf3, 0xc7, 0x9e, 0x7f, 0xf3, 0xff, 0x9f, 0xfc, 0xff, 0x9e, 0x79, 0xe3, 0xff, 0x9f, 0xfc,
    0x7f, 0xf3, 0xc7, 0x9e, 0x7f, 0xf3, 0xff, 0x9f, 0xfc, 0xff, 0x9e, 0x79, 0xe3, 0xff, 0x9f, 0xfc,
    0x7f, 0xf3, 0xc7, 0x9e, 0x7f, 0xf3, 0xff, 0x9f, 0xfc, 0xff, 0x9e, 0x79, 0xe3, 0xff, 0x9f, 0xfc,
    0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x7d, 0xf7, 0x7c, 0x3f, 0x6f, 0x00, 0x00, 0x00, 0x06, 0xc0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x7d, 0xf7, 0x7c, 0x3f, 0x6f, 0x00, 0x00, 0x00, 0x06, 0xc0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x0d, 0xb3, 0x0c, 0x33, 0x6c, 0x00, 0x00, 0x00, 0x06, 0xc0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x0d, 0xb3, 0x0c, 0x33, 0x6f, 0x7d, 0xf7, 0xdf, 0x06, 0xc3, 0x6f, 0xbe, 0x00, 0x00,
    0x00, 0x00, 0x7d, 0xb3, 0x0c, 0x3f, 0x6f, 0x7d, 0xf7, 0xdf, 0x06, 0xc3, 0x6f, 0xbe, 0x00, 0x00,
    0x00, 0x00, 0x7d, 0xb3, 0x0c, 0x3f, 0x6c, 0x6d, 0xb6, 0x1b, 0x66, 0xc3, 0x6d, 0x86, 0x00, 0x00,
    0x00, 0x00, 0x61, 0xb3, 0x0c, 0x33, 0x6c, 0x6d, 0xb7, 0xdb, 0x66, 0xc3, 0x6d, 0xbe, 0x00, 0x00,
    0x00, 0x00, 0x61, 0xb3, 0x0c, 0x33, 0x6c, 0x6d, 0xb0, 0xdb, 0x66, 0xc3, 0x6d, 0xb6, 0x00, 0x00,
    0x00, 0x00, 0x7d, 0xf3, 0x0c, 0x33, 0x6c, 0x7d, 0xb7, 0xdf, 0x7e, 0xfb, 0xed, 0xbe, 0x00, 0x00,
    0x00, 0x00, 0x7d, 0xf3, 0x0c, 0x33, 0x6c, 0x7d, 0xb7, 0xdf, 0x7e, 0xfb, 0xed, 0xbe, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


void splashScreenShow()
{
    displayRefresh(splash);
    HAL_Delay(3000);
}
