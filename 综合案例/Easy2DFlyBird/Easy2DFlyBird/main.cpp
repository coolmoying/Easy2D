#include "common.h"
#include "resource.h"
#include "music.h"
#include "gameScene.h"
int main() 
{
	Logger::showConsole(false);
	if (Game::init((L"·ÉÏèÐ¡Äñ"), 288, 608)) 
	{
		Window::setIcon(IDI_ICON1);
		MusicLoader::init();
		auto scene = gcnew GameScene;
		SceneManager::enter(scene);
		Game::start();
	}
	Game::destroy();
	return 0;
}