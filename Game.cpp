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

	_display->Sprite(Sprites.table, 0, 1, 1, 24, SpriteTransform::Default);
	_display->Sprite(Sprites.table, 0, 1, 3, 24, SpriteTransform::FlipHorizontal);
	_display->Sprite(Sprites.table, 0, 1, 5, 24, SpriteTransform::FlipVertical);
	_display->Sprite(Sprites.table, 0, 3, 1, 24, SpriteTransform::Transpose);

	_display->Sprite(Sprites.table, 0, 5, 1, 24, SpriteTransform::Rotate90);
	_display->Sprite(Sprites.table, 0, 5, 3, 24, SpriteTransform::Rotate180);
	_display->Sprite(Sprites.table, 0, 5, 5, 24, SpriteTransform::Rotate270);

	Serial.println("start success");
	_display->Show();
}



void Game::UpdateDisplay()
{


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
			//player.y--;

			break;
		case 2:
			//player.x++;

			break;
		case 4:
			//player.x--;

			break;
		case 8:
			//player.y++;

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
