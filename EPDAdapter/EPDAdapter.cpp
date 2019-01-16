/*
 Name:		EPDAdapter.cpp
 Created:	1/16/2019 4:03:00 PM
 Author:	CasparKleijne
 Editor:	http://www.visualmicro.com
*/

#include "EPDAdapter.h"
#include <stdlib.h>

const unsigned char lut_full_update[] =
{
	0x02, 0x02, 0x01, 0x11, 0x12, 0x12, 0x22, 0x22,
	0x66, 0x69, 0x69, 0x59, 0x58, 0x99, 0x99, 0x88,
	0x00, 0x00, 0x00, 0x00, 0xF8, 0xB4, 0x13, 0x51,
	0x35, 0x51, 0x51, 0x19, 0x01, 0x00
};

const unsigned char lut_partial_update[] =
{
	0x10, 0x18, 0x18, 0x08, 0x18, 0x18, 0x08, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x13, 0x14, 0x44, 0x12,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

EPDAdapter::EPDAdapter()
{
	reset_pin = RST_PIN;
	dc_pin = DC_PIN;
	cs_pin = CS_PIN;
	busy_pin = BUSY_PIN;
	width = EPD_WIDTH;
	height = EPD_HEIGHT;
}


EPDAdapter::~EPDAdapter()
{
}

void EPDAdapter::SetLut(const unsigned char * lut)
{
	this->lut = lut;
	SendCommand(WRITE_LUT_REGISTER);
	/* the length of look-up table is 30 bytes */
	for (int i = 0; i < 30; i++) {
		SendData(this->lut[i]);
	}
}

void EPDAdapter::SetMemoryArea(int x_start, int y_start, int x_end, int y_end)
{
	SendCommand(SET_RAM_X_ADDRESS_START_END_POSITION);
	/* x point must be the multiple of 8 or the last 3 bits will be ignored */
	SendData((x_start >> 3) & 0xFF);
	SendData((x_end >> 3) & 0xFF);
	SendCommand(SET_RAM_Y_ADDRESS_START_END_POSITION);
	SendData(y_start & 0xFF);
	SendData((y_start >> 8) & 0xFF);
	SendData(y_end & 0xFF);
	SendData((y_end >> 8) & 0xFF);
}

void EPDAdapter::SetMemoryPointer(int x, int y)
{
	SendCommand(SET_RAM_X_ADDRESS_COUNTER);
	/* x point must be the multiple of 8 or the last 3 bits will be ignored */
	SendData((x >> 3) & 0xFF);
	SendCommand(SET_RAM_Y_ADDRESS_COUNTER);
	SendData(y & 0xFF);
	SendData((y >> 8) & 0xFF);
	WaitUntilIdle();
}

int EPDAdapter::Init(const unsigned char * lut)
{
	/* this calls the peripheral hardware interface, see epdif */
	if (IfInit() != 0) {
		return -1;
	}
	/* EPD hardware init start */
	this->lut = lut;
	Reset();
	SendCommand(DRIVER_OUTPUT_CONTROL);
	SendData((EPD_HEIGHT - 1) & 0xFF);
	SendData(((EPD_HEIGHT - 1) >> 8) & 0xFF);
	SendData(0x00);                     // GD = 0; SM = 0; TB = 0;
	SendCommand(BOOSTER_SOFT_START_CONTROL);
	SendData(0xD7);
	SendData(0xD6);
	SendData(0x9D);
	SendCommand(WRITE_VCOM_REGISTER);
	SendData(0xA8);                     // VCOM 7C
	SendCommand(SET_DUMMY_LINE_PERIOD);
	SendData(0x1A);                     // 4 dummy lines per gate
	SendCommand(SET_GATE_TIME);
	SendData(0x08);                     // 2us per line
	SendCommand(DATA_ENTRY_MODE_SETTING);
	SendData(0x03);                     // X increment; Y increment
	SetLut(this->lut);
	/* EPD hardware init end */
	return 0;
}

void EPDAdapter::SendCommand(unsigned char command)
{
	DigitalWrite(dc_pin, LOW);
	SpiTransfer(command);
}

void EPDAdapter::SendData(unsigned char data)
{
	DigitalWrite(dc_pin, HIGH);
	SpiTransfer(data);
}

void EPDAdapter::WaitUntilIdle(void)
{
	while (DigitalRead(busy_pin) == HIGH) {      //LOW: idle, HIGH: busy
		DelayMs(100);
	}
}

void EPDAdapter::Reset(void)
{
	DigitalWrite(reset_pin, LOW);                //module reset    
	DelayMs(200);
	DigitalWrite(reset_pin, HIGH);
	DelayMs(200);
}

void EPDAdapter::SetFrameMemory(const unsigned char * image_buffer, int x, int y, int image_width, int image_height)
{
	int x_end;
	int y_end;

	if (
		image_buffer == NULL ||
		x < 0 || image_width < 0 ||
		y < 0 || image_height < 0
		) {
		return;
	}
	/* x point must be the multiple of 8 or the last 3 bits will be ignored */
	x &= 0xF8;
	image_width &= 0xF8;
	if (x + image_width >= this->width) {
		x_end = this->width - 1;
	}
	else {
		x_end = x + image_width - 1;
	}
	if (y + image_height >= this->height) {
		y_end = this->height - 1;
	}
	else {
		y_end = y + image_height - 1;
	}
	SetMemoryArea(x, y, x_end, y_end);
	SetMemoryPointer(x, y);
	SendCommand(WRITE_RAM);
	/* send the image data */
	for (int j = 0; j < y_end - y + 1; j++) {
		for (int i = 0; i < (x_end - x + 1) / 8; i++) {
			SendData(image_buffer[i + j * (image_width / 8)]);
		}
	}
}



void EPDAdapter::SetFrameMemory(const unsigned char * image_buffer)
{
	SetMemoryArea(0, 0, this->width - 1, this->height - 1);
	SetMemoryPointer(0, 0);
	SendCommand(WRITE_RAM);
	/* send the image data */
	for (int i = 0; i < this->width / 8 * this->height; i++) {
		SendData(pgm_read_byte(&image_buffer[i]));
	}
}

void EPDAdapter::ClearFrameMemory(unsigned char color)
{
	SetMemoryArea(0, 0, this->width - 1, this->height - 1);
	SetMemoryPointer(0, 0);
	SendCommand(WRITE_RAM);
	/* send the color data */
	for (int i = 0; i < this->width / 8 * this->height; i++) {
		SendData(color);
	}
}



void EPDAdapter::DisplayFrame(void)
{
	SendCommand(DISPLAY_UPDATE_CONTROL_2);
	SendData(0xC4);
	SendCommand(MASTER_ACTIVATION);
	SendCommand(TERMINATE_FRAME_READ_WRITE);
	WaitUntilIdle();
}

void EPDAdapter::Sleep(void)
{
	SendCommand(DEEP_SLEEP_MODE);
	WaitUntilIdle();
}
