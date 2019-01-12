#include "Game.h"
#include "SpriteTransform.h"
void Game::Init(DisplayAdapter * display, ButtonPad * buttonPad)
{
	_display = display;
	_buttonpad = buttonPad;
	_display->Clear();
	_display->Clear();
	Serial.print("init success");
}


void Game::Start()
{

	//_display->Image(Splash.table);


}



void Game::UpdateDisplay()
{
	delay(100);

	unsigned char maze[100];
	
	for (int i = 0; i < 100; i++)
	{
		maze[i] = rand() % 2 ;
	}

	unsigned char buffer[64];

	for (int c = 0; c < 64; c++)
	{
		buffer[c] = 0x0;
	}

	for (int y = 1; y < 9; y++)
	{
		for (int x = 1; x < 9; x++)
		{
			if (maze[y * 10 + x] != 0)
			{
				buffer[(y-1) * 8 + (x-1)] = maze[(y - 1) * 10 + x] * 1 | maze[y * 10 + x + 1] * 2 | maze[(y + 1) * 10 + x] * 4 | maze[y * 10 + x - 1] * 8;
			}
		}
	}


	Serial.println("");
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			Serial.print(buffer[y * 8 + x]);
			Serial.print(",");

		}
		Serial.println("");
	}

	for (int c = 0; c < 64; c++)
	{
		unsigned int index = buffer[c];

		switch (index)
		{
		case 0:
			_display->Sprite(Sprites.table, 7, c % 8, c / 8, 24, SpriteTransform::Default);
			break;
		case 1:
			_display->Sprite(Sprites.table, 3, c % 8, c / 8, 24, SpriteTransform::Default);
			break;
		case 2:
			_display->Sprite(Sprites.table, 3, c % 8, c / 8, 24, SpriteTransform::Rotate270);
			break;
		case 3:
			_display->Sprite(Sprites.table, 4, c % 8, c / 8, 24, SpriteTransform::Rotate270);
			break;
		case 4:
			_display->Sprite(Sprites.table, 3, c % 8, c / 8, 24, SpriteTransform::Rotate180);
			break;
		case 5:
			_display->Sprite(Sprites.table, 1, c % 8, c / 8, 24, SpriteTransform::Default);
			break;
		case 6:
			_display->Sprite(Sprites.table, 4, c % 8, c / 8, 24, SpriteTransform::Rotate180);
			break;
		case 7:
			_display->Sprite(Sprites.table, 2, c % 8, c / 8, 24, SpriteTransform::Rotate270);
			break;
		case 8:
			_display->Sprite(Sprites.table, 3, c % 8, c / 8, 24, SpriteTransform::Rotate90);
			break;
		case 9:
			_display->Sprite(Sprites.table, 4, c % 8, c / 8, 24, SpriteTransform::Default);
			break;
		case 10:
			_display->Sprite(Sprites.table, 1, c % 8, c / 8, 24, SpriteTransform::Rotate90);
			break;
		case 11:
			_display->Sprite(Sprites.table, 2, c % 8, c / 8, 24, SpriteTransform::Default);
			break;
		case 12:
			_display->Sprite(Sprites.table, 4, c % 8, c / 8, 24, SpriteTransform::Rotate90);
			break;
		case 13:
			_display->Sprite(Sprites.table, 2, c % 8, c / 8, 24, SpriteTransform::Rotate90);
			break;
		case 14:
			_display->Sprite(Sprites.table, 2, c % 8, c / 8, 24, SpriteTransform::Rotate180);
			break;
		case 15:
			_display->Sprite(Sprites.table, 0, c % 8, c / 8, 24, SpriteTransform::Default);
			break;
		}



	}




	Serial.println("start success");
	_display->Show();
}



void Game::Run()
{
	UpdateDisplay();
	int trigger = 0;


	while (trigger == 0)
	{
		trigger = _buttonpad->Listen();

		switch (trigger)
		{
		case 1:
			_display->Sprite(Sprites.table, 2, 5, 1, 24, SpriteTransform::Rotate180);

			break;
		case 2:
			_display->Sprite(Sprites.table, 2, 5, 1, 24, SpriteTransform::Rotate270);

			break;
		case 4:
			_display->Sprite(Sprites.table, 2, 5, 1, 24, SpriteTransform::Rotate90);

			break;
		case 8:
			_display->Sprite(Sprites.table, 2, 5, 1, 24, SpriteTransform::Default);

			break;
		case 16:
			//player = { 4,4 };

			break;
		default:
			break;
		}
	}

}




Game::Game()
{

}


Game::~Game()
{

}
