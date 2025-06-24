/*
 * lib_GAmeStruct.c
 *
 *  Created on: Apr 21, 2025
 *      Author: Nelson Lima
 */


#include "usr/lib_GameStruct.h"
#include "usr/lib_J3_ST7789VW.h"



TPaletaCor gamePaleta = {
		 COLOR_BLACK, COLOR_WHITE, COLOR_BLUE, COLOR_BEIGE, COLOR_BROWN, COLOR_CYAN, COLOR_DARK_BLUE, COLOR_RED,
		 COLOR_DARK_GRAY, COLOR_DARK_GREEN, COLOR_DARK_RED, COLOR_GOLD, COLOR_GRAY, COLOR_GREEN, COLOR_LIGHT_BLUE,
		 COLOR_LIGHT_GRAY
};

void J3GameEngine_SetPaleta(TPaletaCor _paleta){
  gamePaleta = _paleta;
}

uint16_t J3GameEngine_GetCorPaleta(uint8_t _idxCor){
	return gamePaleta.corRGB565[_idxCor];
}


void J3GameEngine_DesenhaTile(TTile _tile, uint8_t _posX, uint8_t _posY){
uint8_t idxCorPaleta = 0;
uint16_t auxCor;
uint8_t auxY = 0;
uint8_t auxX = 0;
for(uint8_t i = 0; i < TILE_TAMANHO*TILE_TAMANHO; i++){

	idxCorPaleta = _tile.tile_pixel[i];
	auxCor = J3GameEngine_GetCorPaleta(idxCorPaleta);
	ST7789VW_DrawPixel(_posX + auxX,  _posY + auxY, auxCor);
	auxX++;
	if(auxX == 8){
		auxX = 0;
		auxY++;
	}
}



void J3GameEngine_DesenhaMapa(TMapTile _mapa, uint8_t _posX, uint8_t _posY){
/*
uint8_t idxCorPaleta = 0;
uint16_t auxCor;
uint8_t auxY = 0;
uint8_t auxX = 0;
for(uint8_t i = 0; i < TELA_TAMANHO_TILE_X * TELA_TAMANHO_TILE_Y; i++){

	auxTile = _mapa.map.tile_pixel[i];
	auxCor = J3GameEngine_GetCorPaleta(idxCorPaleta);  // Azul
	ST7789VW_DrawPixel(_posX + auxX,  _posY + auxY, auxCor);
	auxX++;
	if(auxX == 8){
		auxX = 0;
		auxY++;
	}
	*/
}





}
