/*
 * lib_GameStruct.h
 *
 *  Created on: Apr 21, 2025
 *      Author: Nelson Lima
 */

#ifndef INC_USR_LIB_GAMESTRUCT_H_
#define INC_USR_LIB_GAMESTRUCT_H_

#include <stdint.h>
#include "usr/cores_RGB565.h"

/*
Usando display 320x240 => ST7789
*/
#define TELA_TAMANHO_TILE_X 40
#define TELA_TAMANHO_TILE_Y 30

#define TILE_TAMANHO 8 /* 8 x 8 Pixels => 64 bytes por Tile*/

#define MAX_TILES 32 /* Qtd max de tiles q uma game pode ter 32 x 64 => 2048 => 2KB de Tiles */

typedef struct {
	uint16_t corRGB565[16];
} TPaletaCor;

typedef struct {
	uint8_t tile_pixel[TILE_TAMANHO * TILE_TAMANHO];
} TTile;

typedef struct {
	uint8_t idxTile[TELA_TAMANHO_TILE_X * TELA_TAMANHO_TILE_Y];
} TMapTile;

void J3GameEngine_SetPaleta(TPaletaCor _paleta);
uint16_t J3GameEngine_GetCorPaleta(uint8_t _idxCor);
void J3GameEngine_DesenhaTile(TTile _tile, uint8_t _posX, uint8_t _posY);
void J3GameEngine_DesenhaMapa(TMapTile _mapa, uint8_t _posX, uint8_t _posY);


#endif /* INC_USR_LIB_GAMESTRUCT_H_ */
