#pragma once



class Maze
{

	int EnQueue(int value);
	int DeQueue();
	int GenerateMaze(int pos);

public:
	void Generate(unsigned char * maze);
	
	Maze();
	~Maze();
};

