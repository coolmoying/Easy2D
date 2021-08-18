#include "music.h"
std::map<MusicType, Music*> MusicLoader::musicMap;
void MusicLoader::init()
{
	// 使用播放器预加载音频
	Music* click = MusicPlayer::preload(L"res/sound/click.wav");
	musicMap.insert(std::make_pair(MusicType::Click, click));

	Music* fly = MusicPlayer::preload(L"res/sound/fly.wav");
	musicMap.insert(std::make_pair(MusicType::Fly, fly));

	Music* hit = MusicPlayer::preload(L"res/sound/hit.wav");
	musicMap.insert(std::make_pair(MusicType::Hit, hit));

	Music* point = MusicPlayer::preload(L"res/sound/point.wav");
	musicMap.insert(std::make_pair(MusicType::Point, point));

	Music* swoosh = MusicPlayer::preload(L"res/sound/swoosh.wav");
	musicMap.insert(std::make_pair(MusicType::Swoosh, swoosh));

}
void MusicLoader::playMusic(MusicType musicType)
{
	Music* music = musicMap[musicType];
	if (music)
	{
		music->play();
	}
}
