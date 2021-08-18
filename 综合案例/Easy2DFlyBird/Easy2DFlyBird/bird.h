#pragma once
#include "common.h"
class Bird :public Sprite 
{
public:
	enum class Status
	{
		Still,		//С�񲻶�
		Idle,		//���¸���
		StartToFly,	//��ʼ��
		Fly			//���Ϸ�
	};
public:
	Bird();
	~Bird();


	void setStatus(Status status);
	bool living;
	float speed;
	Action* fly;				//���趯��
	Animation* animation;		//֡����
	Action* rotate;				//��ת
};