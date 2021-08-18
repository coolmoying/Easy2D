#pragma once
#include "common.h"
#include "bird.h"
#include "music.h"
#include "pipes.h"
class GameScene :public Scene
{

public:
	GameScene();
	void onUpdate() override;
	void start();		// ��ʼ��Ϸ
	void jump();		// С����Ծ
	void die();			// С������
protected:
	bool started;
	int score;
	Bird* bird;
	Pipes* pipes;
};