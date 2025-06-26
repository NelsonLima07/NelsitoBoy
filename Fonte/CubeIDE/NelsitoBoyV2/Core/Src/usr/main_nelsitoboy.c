/*
 * main_nelsitoboy.c
 *
 *  Created on: Apr 19, 2025
 *      Author: Nelson Lima
 */


#include "usr/main_nelsitoboy.h"
#include "usr/lib_J3_ST7789VW.h"
#include "spi.h"
#include "usr/cores_RGB565.h"

#include "usr/game_01_breakout.h"

#include <stdlib.h>
#include <time.h>


int main_nelsitoboy(void){

	// Inicialize o display
    ST7789VW_Init(&hspi1);

    // Exemplo: desenhar algo no display
    //ST7789VW_DrawPixel(100,100, 0xFFFF); // Branco

    // Inicializa o gerador de números aleatórios com base no tempo
    //srand(time(NULL));


    while(1){
        ST7789VW_FillScreen2(COLOR_LIGHT_GRAY);
        HAL_Delay(5000);

       // main_game();

        //ST7789VW_DrawChar(50, 50, "N", COLOR_ORANGE, COLOR_LIGHT_GRAY);

        HAL_Delay(5000);

        ST7789VW_DrawStringBig(0, 50, "abcdefghijklmnopqrstuvxz", COLOR_BLACK, COLOR_BLUE);
        ST7789VW_DrawStringBig(0, 70, "1234567890ñ", COLOR_RED, COLOR_LIGHT_GRAY);

        HAL_Delay(5000);


    	//ST7789VW_FillScreen(COLOR_LIGHT_GRAY);
    	/*ST7789VW_FillWindow(x, y, x+7, y+7, COLOR_BLUE);
    	x = x + 8;
    	if(x >= 320){ x = 0; y = y + 8; };
    	if(y >= 240) y = 0;
    	HAL_Delay(20);
    	*/
    	/*ST7789VW_FillWindow(9, 1, 16, 8, COLOR_BROWN);
    	ST7789VW_FillWindow(17, 1, 24, 8, COLOR_DARK_GREEN);
    	ST7789VW_FillWindow(25, 1, 32, 8, COLOR_GREEN);
    	ST7789VW_FillWindow(33, 1, 40, 8, COLOR_BLACK);
    	ST7789VW_FillWindow(41, 1, 48, 8, COLOR_BEIGE);
    	ST7789VW_FillWindow(49, 1, 56, 8, COLOR_CYAN);
    	ST7789VW_FillWindow(57, 1, 64, 8, COLOR_DARK_RED);
    	*/
    	//HAL_Delay(5000);

    }





}
