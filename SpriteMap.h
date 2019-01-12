#pragma once
#include <stdint.h>
typedef struct _spriteMap
{
	const unsigned char *table;
	uint16_t Width;
	uint16_t Height;
	uint8_t spriteWidth;
	uint8_t spriteHeight;

} spriteMap;