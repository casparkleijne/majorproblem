#include "Maze.h"
#include <Arduino.h>

const uint8_t VISITED = 0x10;
const int _dir[4][4] = { { 0, -1, 1, 4 }, { 1, 0, 2, 8 }, { 0, 1, 4, 1 }, { -1, 0, 8, 2 } };
unsigned char _map[64];
uint8_t _queue[64];
int _quepos = 0;
int _width = 8;
/* Add a wall during building phase */


int Maze::EnQueue(int value)
{
	_queue[++_quepos] = value;
	return value;
}

int Maze::DeQueue()
{
	return --_quepos < 0 ? -1 : _queue[_quepos];
}

int Maze::GenerateMaze(int pos)
{
	_map[pos] |= VISITED;

	int x = pos % _width;
	int y = pos / _width;

	int options[4][4];
	int optionslength = 0;


	for (int i = 0; i < 4; i++)
	{
		if (x + _dir[i][0] >= 0 && x + _dir[i][0] < _width && y + _dir[i][1] >= 0 && y + _dir[i][1] < _width && (_map[x + _dir[i][0] + (y + _dir[i][1]) * _width] & VISITED) != VISITED)
		{
			options[optionslength][0] = _dir[i][0];
			options[optionslength][1] = _dir[i][1];
			options[optionslength][2] = _dir[i][2];
			options[optionslength][3] = _dir[i][3];
			optionslength++;
		}
	}

	if (optionslength == 0)
	{
		return -1;
	}

	int n = rand() % optionslength;

	int newCell = x + options[n][0] + (y + options[n][1]) * _width;

	_map[pos] |= options[n][2];
	_map[newCell] |= options[n][3];
	
	return newCell;
}

void Maze::Generate(unsigned char * maze)
{

	for (int x = 0; x < 64; x++)
	{
		_map[x] = 0x00;
	}

	int pos = rand() % 64;

	while (pos != -1)
	{

		EnQueue(pos);
		pos = GenerateMaze(pos);

		if (pos == -1)
		{
			DeQueue();
			pos = DeQueue();
		}
	}

	for (int i = 0; i < 64; i++)
	{
		maze[i] = _map[i] ^ 0x10;
	}
}


Maze::Maze()
{
}


Maze::~Maze()
{
}
