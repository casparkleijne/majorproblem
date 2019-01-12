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

	for (int x = 0; x < 5; x++)
	{
		_display->Sprite(Sprites.table, x , x % 8, 0, 24, SpriteTransform::Default);
	}

	for (int x = 0; x < 5; x++)
	{
		_display->Sprite(Sprites.table, x, x % 8, 1, 24, SpriteTransform::Rotate90);
	}

	for (int x = 0; x < 5; x++)
	{
		_display->Sprite(Sprites.table, x, x % 8, 2, 24, SpriteTransform::Rotate180);
	}

	for (int x = 0; x < 5; x++)
	{
		_display->Sprite(Sprites.table, x, x % 8, 3, 24, SpriteTransform::Rotate270);
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
			_display->Sprite(Sprites.table, 0, 5, 1, 24, SpriteTransform::Rotate180);

			break;
		case 2:
			_display->Sprite(Sprites.table, 0, 5, 1, 24, SpriteTransform::Rotate270);

			break;
		case 4:
			_display->Sprite(Sprites.table, 0, 5, 1, 24, SpriteTransform::Rotate90);

			break;
		case 8:
			_display->Sprite(Sprites.table, 0, 5, 1, 24, SpriteTransform::Default);

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
