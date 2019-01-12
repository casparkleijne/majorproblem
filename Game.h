#pragma once
#include "DisplayAdapter.h"
#include "Assets.h"
#include "ButtonPad.h"

class Game
{
	uint8_t  _map[64] = {};
	DisplayAdapter * _display;
	ButtonPad * _buttonpad;

public:
	void Init(DisplayAdapter * display, ButtonPad * buttonPad);
	void Start();
	void UpdateDisplay();
	void Run();
	Game();
	~Game();
};

