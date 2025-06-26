/*
 * lib_J3_ST7789VW.c
 *
 *  Created on: Apr 19, 2025
 *      Author: Nelson Lima
 */


#include "usr/lib_J3_ST7789VW.h"
#include "usr/font5x7.h"

// Handler para a interface SPI (será passado na inicialização)
static SPI_HandleTypeDef *hspi_ptr;

// Função para enviar um comando para o display
static void ST7789VW_SendCommand(uint8_t command) {
  HAL_GPIO_WritePin(ST7789VW_DC_GPIO_Port, ST7789VW_DC_Pin, GPIO_PIN_RESET); // DC = 0 para comando
  HAL_GPIO_WritePin(ST7789VW_CS_GPIO_Port, ST7789VW_CS_Pin, GPIO_PIN_RESET); // CS = 0 para selecionar
  HAL_SPI_Transmit(hspi_ptr, &command, 1, HAL_MAX_DELAY);
  HAL_GPIO_WritePin(ST7789VW_CS_GPIO_Port, ST7789VW_CS_Pin, GPIO_PIN_SET);   // CS = 1 para deselecionar
}

// Função para enviar dados para o display
static void ST7789VW_SendData(uint8_t *data, uint16_t size) {
  HAL_GPIO_WritePin(ST7789VW_DC_GPIO_Port, ST7789VW_DC_Pin, GPIO_PIN_SET); // DC = 1 para dados
  HAL_GPIO_WritePin(ST7789VW_CS_GPIO_Port, ST7789VW_CS_Pin, GPIO_PIN_RESET); // CS = 0 para selecionar
  HAL_SPI_Transmit(hspi_ptr, data, size, HAL_MAX_DELAY);
  HAL_GPIO_WritePin(ST7789VW_CS_GPIO_Port, ST7789VW_CS_Pin, GPIO_PIN_SET);   // CS = 1 para deselecionar
}

static void J3_ST7789VW_SetWindows(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2){
 if(x2 >= ST7789VW_WIDTH) x2 = ST7789VW_WIDTH-1;
 if(y2 >= ST7789VW_HEIGHT) y2 = ST7789VW_HEIGHT-1;
 if(x1 > x2)x2 = x1;
 if(y1 > y2)y2 = y1;



 ST7789VW_SendCommand(0x2A); // CASET - Column Address Set
 uint8_t data[4];
 data[0] = (x1 >> 8) & 0xFF;
 data[1] = x1 & 0xFF;
 data[2] = (x2 >> 8) & 0xFF;
 data[3] = x2 & 0xFF;
 ST7789VW_SendData(data, 4);

 ST7789VW_SendCommand(0x2B); // RASET - Row Address Set
 data[0] = (y1 >> 8) & 0xFF;
 data[1] = y1 & 0xFF;
 data[2] = (y2 >> 8) & 0xFF;
 data[3] = y2 & 0xFF;
 ST7789VW_SendData(data, 4);
}


// Função de inicialização do display ST7789VW
void ST7789VW_Init(SPI_HandleTypeDef *hspi) {
  hspi_ptr = hspi;

  // Reset do display
  HAL_GPIO_WritePin(ST7789VW_RST_GPIO_Port, ST7789VW_RST_Pin, GPIO_PIN_RESET);
  HAL_Delay(100);
  HAL_GPIO_WritePin(ST7789VW_RST_GPIO_Port, ST7789VW_RST_Pin, GPIO_PIN_SET);
  HAL_Delay(100);

  // Sequência de inicialização (baseada no datasheet do ST7789VW)
  ST7789VW_SendCommand(0x01); // SWRESET - Software reset
  HAL_Delay(150);

  ST7789VW_SendCommand(0x11); // SLPOUT - Leave sleep mode
  HAL_Delay(120);

  ST7789VW_SendCommand(0x3A); // COLMOD - Interface Pixel Format
  uint8_t color_mode = 0x55;   // 16 bits/pixel (RGB565)
  ST7789VW_SendData(&color_mode, 1);

  /*
  ST7789VW_SendCommand(0x36); // MADCTL - Memory Data Access Control
  uint8_t madctl = 0x00;       // Ajuste conforme a orientação desejada
  ST7789VW_SendData(&madctl, 1);
  */
  ST7789VW_SetRotation(ST7789VW_ORIENTACAO);




  ST7789VW_SendCommand(0x21); // DISPINV - Display Inversion ON (opcional)

  ST7789VW_SendCommand(0x13); // NORON - Normal display mode ON

  ST7789VW_SendCommand(0x29); // DISPON - Display ON
  HAL_Delay(10);
}

// Função para desenhar um pixel na tela
void ST7789VW_DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
  if (x >= ST7789VW_WIDTH || y >= ST7789VW_HEIGHT) return;

  ST7789VW_SendCommand(0x2A); // CASET - Column Address Set
  uint8_t data[4];
  data[0] = (x >> 8) & 0xFF;
  data[1] = x & 0xFF;
  data[2] = (x >> 8) & 0xFF;
  data[3] = x & 0xFF;
  ST7789VW_SendData(data, 4);

  ST7789VW_SendCommand(0x2B); // RASET - Row Address Set
  data[0] = (y >> 8) & 0xFF;
  data[1] = y & 0xFF;
  data[2] = (y >> 8) & 0xFF;
  data[3] = y & 0xFF;
  ST7789VW_SendData(data, 4);

  ST7789VW_SendCommand(0x2C); // RAMWR - Memory Write
  data[0] = (color >> 8) & 0xFF; // High byte
  data[1] = color & 0xFF;        // Low byte
  ST7789VW_SendData(data, 2);
}

// Função para preencher toda a tela com uma única cor
void ST7789VW_FillScreen(uint16_t color) {
  uint8_t data[2];
  data[0] = (color >> 8) & 0xFF; // High byte
  data[1] = color & 0xFF;        // Low byte

  ST7789VW_SendCommand(0x2A); // CASET - Column Address Set
  uint8_t col_data[4];
  col_data[0] = 0x00;
  col_data[1] = 0x00;
  col_data[2] = (ST7789VW_WIDTH - 1) >> 8;
  col_data[3] = (ST7789VW_WIDTH - 1) & 0xFF;
  ST7789VW_SendData(col_data, 4);

  ST7789VW_SendCommand(0x2B); // RASET - Row Address Set
  uint8_t row_data[4];
  row_data[0] = 0x00;
  row_data[1] = 0x00;
  row_data[2] = (ST7789VW_HEIGHT - 1) >> 8;
  row_data[3] = (ST7789VW_HEIGHT - 1) & 0xFF;
  ST7789VW_SendData(row_data, 4);

  ST7789VW_SendCommand(0x2C); // RAMWR - Memory Write

  // Envia a cor para todos os pixels
  for (uint32_t i = 0; i < (uint32_t)ST7789VW_WIDTH * ST7789VW_HEIGHT; i++) {
    ST7789VW_SendData(data, 2);
    //HAL_Delay(2);
  }
}

// Função para preencher toda a tela com uma única cor
void ST7789VW_FillScreen2(uint16_t color) {
  uint8_t data[2];
  data[0] = (color >> 8) & 0xFF; // High byte
  data[1] = color & 0xFF;        // Low byte

  ST7789VW_SendCommand(0x2A); // CASET - Column Address Set
  uint8_t col_data[4];
  col_data[0] = 0x00;
  col_data[1] = 0x00;
  col_data[2] = (ST7789VW_WIDTH - 1) >> 8;
  col_data[3] = (ST7789VW_WIDTH - 1) & 0xFF;
  ST7789VW_SendData(col_data, 4);

  ST7789VW_SendCommand(0x2B); // RASET - Row Address Set
  uint8_t row_data[4];
  row_data[0] = 0x00;
  row_data[1] = 0x00;
  row_data[2] = (ST7789VW_HEIGHT - 1) >> 8;
  row_data[3] = (ST7789VW_HEIGHT - 1) & 0xFF;
  ST7789VW_SendData(row_data, 4);

  ST7789VW_SendCommand(0x2C); // RAMWR - Memory Write

  HAL_GPIO_WritePin(ST7789VW_DC_GPIO_Port, ST7789VW_DC_Pin, GPIO_PIN_SET); // DC = 1 para dados


  // Envia a cor para todos os pixels
  for (uint32_t i = 0; i < (uint32_t)ST7789VW_WIDTH * ST7789VW_HEIGHT; i++) {
    //ST7789VW_SendData(data, 2);
	  HAL_GPIO_WritePin(ST7789VW_CS_GPIO_Port, ST7789VW_CS_Pin, GPIO_PIN_RESET); // CS = 0 para selecionar
	  HAL_SPI_Transmit(hspi_ptr, data, 2, HAL_MAX_DELAY);
	  HAL_GPIO_WritePin(ST7789VW_CS_GPIO_Port, ST7789VW_CS_Pin, GPIO_PIN_SET);   // CS = 1 para deselecionar
  }
}

// Função para preencher toda a tela com uma única cor
void ST7789VW_FillWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t _cor){
  uint8_t dataCor[2];
  dataCor[0] = (_cor >> 8) & 0xFF; // High byte
  dataCor[1] = _cor & 0xFF;        // Low byte

  J3_ST7789VW_SetWindows(x1, y1, x2, y2);

  ST7789VW_SendCommand(0x2C); // RAMWR - Memory Write

  // Envia a cor para todos os pixels
  for (uint32_t i = 0; i < (uint32_t)(x2-x1+1) * (y2-y1+1); i++) {
    ST7789VW_SendData(dataCor, 2);
    //HAL_Delay(2);
  }
}

void ST7789VW_SetRotation(uint8_t rotation) {
  uint8_t madctl = 0;

  switch (rotation) {
    case 0: // 0 degrees (Portrait)
      madctl = 0x00;
      break;
    case 1: // 90 degrees (Landscape)
      madctl = 0x60;
      break;
    case 2: // 180 degrees (Portrait inverted)
      madctl = 0xC0;
      break;
    case 3: // 270 degrees (Landscape inverted)
      madctl = 0xA0;
      break;
    default:
      break;
  }

  ST7789VW_SendCommand(0x36); // MADCTL
  ST7789VW_SendData(&madctl, 1);
}

void ST7789VW_DrawChar(uint16_t x, uint16_t y, char ch, uint16_t textColor, uint16_t bgColor) {
    if (ch < 32 || ch > 126) return; // Caracteres inválidos

    const uint8_t *bitmap = font5x7[ch - 32];

    for (uint8_t i = 0; i < 5; i++) { // largura da fonte
        uint8_t line = bitmap[i];
        for (uint8_t j = 0; j < 7; j++) { // altura da fonte
            if (line & 0x01) {
                ST7789VW_DrawPixel(x + i, y + j, textColor);
            } else {
            	ST7789VW_DrawPixel(x + i, y + j, bgColor);
            }
            line >>= 1;
        }
    }

    // Espaço entre caracteres
    for (uint8_t j = 0; j < 7; j++) {
    	ST7789VW_DrawPixel(x + 5, y + j, bgColor);
    }
}

void ST7789VW_DrawString(uint16_t x, uint16_t y, const char* str, uint16_t textColor, uint16_t bgColor) {
    while (*str) {
    	ST7789VW_DrawChar(x, y, *str, textColor, bgColor);
        x += 6; // 5 pixels de largura + 1 de espaço
        str++;
    }
}

void ST7789VW_DrawCharBig(uint16_t x, uint16_t y, char ch, uint16_t textColor, uint16_t bgColor) {
    if (ch < 32 || ch > 126) return;

    const uint8_t *bitmap = font5x7[ch - 32];

    for (uint8_t col = 0; col < 5; col++) {
        uint8_t line = bitmap[col];
        for (uint8_t row = 0; row < 7; row++) {
            uint16_t pixelColor = (line & 0x01) ? textColor : bgColor;

            // Desenha pixel em 2x2 (escala 2x)
            ST7789VW_DrawPixel(x + col * 2,     y + row * 2,     pixelColor);
            ST7789VW_DrawPixel(x + col * 2 + 1, y + row * 2,     pixelColor);
            ST7789VW_DrawPixel(x + col * 2,     y + row * 2 + 1, pixelColor);
            ST7789VW_DrawPixel(x + col * 2 + 1, y + row * 2 + 1, pixelColor);

            line >>= 1;
        }
    }

    // Espaço de 2 pixels entre caracteres
    for (uint8_t dy = 0; dy < 14; dy++) {
    	ST7789VW_DrawPixel(x + 10, y + dy, bgColor);
    	ST7789VW_DrawPixel(x + 11, y + dy, bgColor);
    }
}

void ST7789VW_DrawStringBig(uint16_t x, uint16_t y, const char* str, uint16_t textColor, uint16_t bgColor) {
    while (*str) {
    	ST7789VW_DrawCharBig(x, y, *str, textColor, bgColor);
        x += 12; // 10 pixels da letra + 2 de espaço
        str++;
    }
}



