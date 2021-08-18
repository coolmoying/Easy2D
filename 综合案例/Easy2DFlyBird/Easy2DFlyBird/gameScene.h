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
	void start();		// 开始游戏
	void jump();		// 小鸟跳跃
	void die();			// 小鸟死亡
protected:
	bool started;
	int score;
	Bird* bird;
	Pipes* pipes;
};