#pragma once
#include "common.h"
enum class MusicType
{
	Click,			//按键
	Hit,			//死亡
	Fly,			//飞翔
	Point,			//得分
	Swoosh			//转场
};
class MusicLoader 
{
public:

	static void init();
	static void playMusic(MusicType musicType);
protected:
	static std::map<MusicType, Music*> musicMap;
};