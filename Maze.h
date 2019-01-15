#pragma once

typedef struct _directions
{
	int x;
	int y;
	unsigned int news; 
	unsigned int snew;

} Directions;

class Maze
{

	int EnQueue(int value);
	int DeQueue();
	int GenerateMaze(int pos);
	int SelectRandomDirection(int pos, Directions * options);
	int UpdateMap(int pos, Directions options);

public:


	void Generate(unsigned char * maze);
	
	Maze();
	~Maze();
};

