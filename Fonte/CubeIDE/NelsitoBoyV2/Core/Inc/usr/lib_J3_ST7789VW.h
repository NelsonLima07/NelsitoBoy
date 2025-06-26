/*
 * lib_J3_ST7789VW.h
 *
 *  Created on: Apr 19, 2025
 *      Author: Nelson Lima
 */

#ifndef INC_USR_LIB_J3_ST7789VW_H_
#define INC_USR_LIB_J3_ST7789VW_H_

#include "stm32g4xx_hal.h"

// Definições de pinos para o display (ajuste conforme sua conexão)
#define ST7789VW_RST_Pin GPIO_PIN_2
#define ST7789VW_RST_GPIO_Port GPIOA
#define ST7789VW_DC_Pin GPIO_PIN_1
#define ST7789VW_DC_GPIO_Port GPIOA
#define ST7789VW_CS_Pin GPIO_PIN_0
#define ST7789VW_CS_GPIO_Port GPIOA

// Definições de resolução do display (comum para ST7789VW)
#define ST7789VW_WIDTH 320
#define ST7789VW_HEIGHT 240
#define ST7789VW_ORIENTACAO 1


// Funções da biblioteca
void ST7789VW_Init(SPI_HandleTypeDef *hspi);
void ST7789VW_SetRotation(uint8_t rotation);
void ST7789VW_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void ST7789VW_FillScreen(uint16_t color);
void ST7789VW_FillWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t _cor);

void ST7789VW_DrawChar(uint16_t x, uint16_t y, char ch, uint16_t textColor, uint16_t bgColor);
void ST7789VW_DrawString(uint16_t x, uint16_t y, const char* str, uint16_t textColor, uint16_t bgColor);




#endif /* INC_USR_LIB_J3_ST7789VW_H_ */
