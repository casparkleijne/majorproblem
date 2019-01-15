#include "Maze.h"
#include <Arduino.h>


const uint8_t VISITED = 0x10;
const Directions _dirs[4] = { { 0, -1, 1, 4 }, { 1, 0, 2, 8 }, { 0, 1, 4, 1 }, { -1, 0, 8, 2 } };
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
	Directions options[4];
	int n = SelectRandomDirection(pos, options);
	return n == -1 ? -1 : UpdateMap(pos, options[n]);
}

int Maze::SelectRandomDirection(int pos, Directions * options)
{
	int optionslength = 0;
	for (int i = 0; i < 4; i++)
	{
		if ((pos % _width) + _dirs[i].x >= 0 && (pos % _width) + _dirs[i].x < _width && (pos / _width) + _dirs[i].y >= 0 && (pos / _width) + _dirs[i].y < _width && (_map[(pos % _width) + _dirs[i].x + ((pos / _width) + _dirs[i].y) * _width] & VISITED) != VISITED)
		{
			options[optionslength++] = _dirs[i];
		}
	}
	return optionslength == 0 ? -1 : rand() % optionslength;
}

int Maze::UpdateMap(int pos, Directions option)
{
	int npos = (pos % _width) + option.x + ((pos / _width) + option.y) * _width;
	_map[pos] |= option.news;
	_map[npos] |= option.snew;
	return npos;
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
