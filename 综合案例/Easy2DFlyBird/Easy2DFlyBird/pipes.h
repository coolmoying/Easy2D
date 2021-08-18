#pragma once
#include "common.h"
#include "pipe.h"
class Pipes :public Sprite 
{
public:
	Pipes();
	~Pipes();

	void onUpdate()override;
	void addPipe();
	void start();
	void stop();
public:
	int number;
	Pipe* pipes[3];
};