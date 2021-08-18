#pragma once
#include "common.h"
class Pipe :public Node 
{
public :
	Pipe();
	~Pipe();
public:
	bool scored;		// 标志小鸟是否飞过了该水管
};