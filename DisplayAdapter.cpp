#include "DisplayAdapter.h"


void DisplayAdapter::Clear()
{
	if (Init(lut_full_update) != 0) {
		return;
	}
	Reset();
	ClearFrameMemory(0xFF);
	DisplayFrame();
	ClearFrameMemory(0xFF);
	DisplayFrame();
	if (Init(lut_partial_update) != 0) {
		return;
	}
}

void DisplayAdapter::Show()
{

	DisplayFrame();
}

void DisplayAdapter::Image(const unsigned char * data)
{
	if (Init(lut_full_update) != 0) {
		return;
	}
	SetFrameMemory(data);
	if (Init(lut_partial_update) != 0) {
		return;
	}
}

void DisplayAdapter::Sprite(const unsigned char * data, int index, uint8_t x, uint8_t y, uint8_t size, void transform(unsigned char *))
{

	for (int r = 0; r < 72; r++)
	{
		_sprite[r] = ~(pgm_read_byte(&data[index * 72 + r]));
	}

	transform(_sprite);

	SetFrameMemory(_sprite, x * size, y * size, size, size);
}

DisplayAdapter::DisplayAdapter()
{

}


DisplayAdapter::~DisplayAdapter()
{
}
