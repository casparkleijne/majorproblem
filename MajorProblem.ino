/*
 Name:		MajorProblem.ino
 Created:	1/2/2019 3:45:23 PM
 Author:	CasparKleijne
*/
#include "Game.h";

DisplayAdapter display;
Game game;
ButtonPad buttonpad;

void setup() {

	Serial.begin(9600);
	game.Init(&display,&buttonpad);
	game.Start();
}  

// the loop function runs over and over again until power down or reset
void loop()
{
	game.Run();
}
