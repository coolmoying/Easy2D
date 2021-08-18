#pragma once
#include "common.h"
class Bird :public Sprite 
{
public:
	enum class Status
	{
		Still,		//小鸟不动
		Idle,		//上下浮动
		StartToFly,	//开始飞
		Fly			//向上飞
	};
public:
	Bird();
	~Bird();


	void setStatus(Status status);
	bool living;
	float speed;
	Action* fly;				//飞翔动作
	Animation* animation;		//帧动画
	Action* rotate;				//旋转
};