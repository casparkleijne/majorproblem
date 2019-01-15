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
	_display->Image(Splash.table);
	_display->Show();
	//int trigger = 0;
	//while (trigger == 0)
	//{
	//	trigger = _buttonpad->Listen();
	//}
}



void Game::UpdateDisplay()
{
	delay(100);

	unsigned char buffer[64];
	_maze->Generate(buffer);

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
		default:
			_display->Sprite(Sprites.table, 5, c % 8, c / 8, 24, SpriteTransform::Default);
			break;
		}
	}
	_display->Show();
}



void Game::Run()
{

	int trigger = 0;
	UpdateDisplay();

	while (trigger == 0)
	{
		trigger = _buttonpad->Listen();

		switch (trigger)
		{
		case 1:

			break;
		case 2:

			break;
		case 4:

			break;
		case 8:

			break;
		case 16:

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
