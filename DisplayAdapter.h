#pragma once
#include "EPDAdapter.h"
class DisplayAdapter : EPDAdapter
{
private:
	unsigned char _sprite[72];
public:
	void Clear();
	void Show();
	void Image(const unsigned char * data);
	void Sprite(const unsigned char * data, int index, uint8_t x, uint8_t y, uint8_t size, void transform(unsigned char *));
	DisplayAdapter();
	~DisplayAdapter();
};

