#include "ButtonPad.h"

#define BUTTON_PIN A1




ButtonPad::ButtonPad()
{
	pinMode(BUTTON_PIN, INPUT_PULLUP);
}


ButtonPad::~ButtonPad()
{

}

uint8_t ButtonPad::Listen()
{
	uint8_t  button = 0;;
	int  z = 0;
	for (uint8_t  i = 0; i < 100; i++)
	{
		z =  (z + analogRead(BUTTON_PIN)) / 2;
	}
	if (z > 1021) button = 0;
	else if (z < 40) button = 16;
	else if (z > 50 && z < 100) button = 1;
	else if (z > 100 && z < 150) button = 4;
	else if (z > 150 && z < 200) button = 8;
	else if (z > 200 && z < 300) button = 2;
	else button = 0;
	if (button != 0)
	{
		//Serial.println(z);
		//Serial.println(button);
	}
	return button;
}
