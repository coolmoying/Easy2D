#pragma once
#include "common.h"
enum class MusicType
{
	Click,			//����
	Hit,			//����
	Fly,			//����
	Point,			//�÷�
	Swoosh			//ת��
};
class MusicLoader 
{
public:

	static void init();
	static void playMusic(MusicType musicType);
protected:
	static std::map<MusicType, Music*> musicMap;
};