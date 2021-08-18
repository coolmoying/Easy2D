#include "gameScene.h"
GameScene::GameScene()
{
	//背景
	auto background = gcnew Sprite(new Image(L"res/background.bmp"));
	background->setAnchor(0, 0);
	this->addChild(background);

	// 添加水管
	pipes = gcnew Pipes();
	this->addChild(pipes);

	bird = gcnew Bird();
	bird->setPos(60, Window::getHeight() / 2);
	this->addChild(bird);	
	//MusicLoader::playMusic(MusicType::Swoosh);
	started = false;
	score = 0;
}
void GameScene::onUpdate()
{
		// 按下鼠标左键或按下空格键
	if (Input::isPress(MouseCode::Left) ||
		Input::isPress(KeyCode::Space))
	{
		this->jump();
	}
	// 判断游戏是否已经开始
	if (started)
	{
		// 模拟小鸟下落
		bird->movePosY(bird->speed);
		// 模拟小鸟所受重力
		bird->speed += 0.4f;
		// 若小鸟纵坐标小于 0，限制它继续往上飞
		if (bird->getPosY() < 0)
		{
			bird->setPosY(0);
			bird->speed = 0;
		}

		// 判断小鸟是否飞过了水管
		if (!pipes->pipes[0]->scored &&
			pipes->pipes[0]->getPosX() <= bird->getPosX())
		{
			// 标记
			pipes->pipes[0]->scored = true;
			// 播放音效
			MusicLoader::playMusic(MusicType::Point);
		}

		// 判断碰撞
		if (bird->living)
		{
			for (auto pipe : pipes->pipes)
			{
				auto box = bird->getBoundingBox();  // 获取小鸟外包围盒
				for (auto child : pipe->getAllChildren())
				{
					if (child->getBoundingBox().intersects(box))
					{  // 判断小鸟包围盒是否和水管相交
						this->die();
					}
				}
			}
		}
		// 若小鸟纵坐标小于地面，游戏结束
		if (Window::getHeight() - bird->getPosY() <= 123)
		{
			this->die();
			// 让小鸟停止
			bird->setPosY(Window::getHeight() - 123);
			bird->setStatus(Bird::Status::Still);
			// 让小鸟脸朝下
			bird->setRotation(90);
			// 显示游戏结束界面
			this->die();
		}
	}
}
void GameScene::start()
{	
	// 开始移动水管
	pipes->start();
	bird->setStatus(Bird::Status::StartToFly);
}
void GameScene::jump()
{
	if (!started)
	{
		// 若游戏还没有开始，开始游戏
		started = true;
		start();
	}
	if (bird->living)
	{
		// 如果小鸟还活着，给小鸟一个向上的速度
		bird->speed = -7.2f;
		// 设置小鸟状态
		bird->setStatus(Bird::Status::Fly);
		// 播放音效
		MusicLoader::playMusic(MusicType::Fly);
	}
}
void GameScene::die()
{
	if (!bird->living) 
		return;
	// 小鸟死亡
	bird->living = false;
	// 播放音效
	MusicLoader::playMusic(MusicType::Hit);
	// 停止水管
	pipes->stop();
	// 闪动白屏
	//auto white = gcnew Sprite();
	//white->setAnchor(0, 0);
	//white->setOpacity(0);
	//white->setScale(16, 16);
	//white->runAction(gcnew Sequence({ gcnew FadeIn(0.1f), gcnew FadeOut(0.1f) }));
	//this->addChild(white);
}
