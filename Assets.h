#ifdef __cplusplus
extern "C" {
#endif

	/* Includes ------------------------------------------------------------------*/

#include <avr/pgmspace.h>
#include <stdint.h>

	typedef struct _memData8
	{
		unsigned char *table;

	} MemData8;

	extern MemData8 Splash;
	extern MemData8 Sprites;
	extern MemData8 Maze;
	extern MemData8 Props;
	extern MemData8 Music;

#ifdef __cplusplus
}
#endif

