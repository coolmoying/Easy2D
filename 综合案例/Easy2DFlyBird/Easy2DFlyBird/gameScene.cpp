#include "gameScene.h"
GameScene::GameScene()
{
	//����
	auto background = gcnew Sprite(new Image(L"res/background.bmp"));
	background->setAnchor(0, 0);
	this->addChild(background);

	// ���ˮ��
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
		// �������������¿ո��
	if (Input::isPress(MouseCode::Left) ||
		Input::isPress(KeyCode::Space))
	{
		this->jump();
	}
	// �ж���Ϸ�Ƿ��Ѿ���ʼ
	if (started)
	{
		// ģ��С������
		bird->movePosY(bird->speed);
		// ģ��С����������
		bird->speed += 0.4f;
		// ��С��������С�� 0���������������Ϸ�
		if (bird->getPosY() < 0)
		{
			bird->setPosY(0);
			bird->speed = 0;
		}

		// �ж�С���Ƿ�ɹ���ˮ��
		if (!pipes->pipes[0]->scored &&
			pipes->pipes[0]->getPosX() <= bird->getPosX())
		{
			// ���
			pipes->pipes[0]->scored = true;
			// ������Ч
			MusicLoader::playMusic(MusicType::Point);
		}

		// �ж���ײ
		if (bird->living)
		{
			for (auto pipe : pipes->pipes)
			{
				auto box = bird->getBoundingBox();  // ��ȡС�����Χ��
				for (auto child : pipe->getAllChildren())
				{
					if (child->getBoundingBox().intersects(box))
					{  // �ж�С���Χ���Ƿ��ˮ���ཻ
						this->die();
					}
				}
			}
		}
		// ��С��������С�ڵ��棬��Ϸ����
		if (Window::getHeight() - bird->getPosY() <= 123)
		{
			this->die();
			// ��С��ֹͣ
			bird->setPosY(Window::getHeight() - 123);
			bird->setStatus(Bird::Status::Still);
			// ��С��������
			bird->setRotation(90);
			// ��ʾ��Ϸ��������
			this->die();
		}
	}
}
void GameScene::start()
{	
	// ��ʼ�ƶ�ˮ��
	pipes->start();
	bird->setStatus(Bird::Status::StartToFly);
}
void GameScene::jump()
{
	if (!started)
	{
		// ����Ϸ��û�п�ʼ����ʼ��Ϸ
		started = true;
		start();
	}
	if (bird->living)
	{
		// ���С�񻹻��ţ���С��һ�����ϵ��ٶ�
		bird->speed = -7.2f;
		// ����С��״̬
		bird->setStatus(Bird::Status::Fly);
		// ������Ч
		MusicLoader::playMusic(MusicType::Fly);
	}
}
void GameScene::die()
{
	if (!bird->living) 
		return;
	// С������
	bird->living = false;
	// ������Ч
	MusicLoader::playMusic(MusicType::Hit);
	// ֹͣˮ��
	pipes->stop();
	// ��������
	//auto white = gcnew Sprite();
	//white->setAnchor(0, 0);
	//white->setOpacity(0);
	//white->setScale(16, 16);
	//white->runAction(gcnew Sequence({ gcnew FadeIn(0.1f), gcnew FadeOut(0.1f) }));
	//this->addChild(white);
}
