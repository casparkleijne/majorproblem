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
	DisplayFrame();
}

void DisplayAdapter::Sprite(const unsigned char * data, int index, uint8_t x, uint8_t y, uint8_t size, void transform (unsigned char *))
{

	unsigned int char_offset = index * size;

	for (int i = 0; i < 72; i++)
	{
		_sprite[i] = ~(pgm_read_byte(&data[i + char_offset]));
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
