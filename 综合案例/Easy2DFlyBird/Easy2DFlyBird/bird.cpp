#include "bird.h"

Bird::Bird()
{
	living = true;
	speed = 0;

	// ����֡������0.1f ���л�һ��
	animation = gcnew Animation(0.1f);
	// ���С����ɫ
	int mode = Random::range(0, 2);

	switch (mode) 
	{

	case 0:
		this->open(new Image(L"res/bird_001.png"));
		animation->add(new Image(L"res/bird_001.png"));
		animation->add(new Image(L"res/bird_002.png"));
		animation->add(new Image(L"res/bird_001.png"));
		animation->add(new Image(L"res/bird_002.png"));
		break;
	case 1:
		this->open(new Image(L"res/bird_001.png"));
		animation->add(new Image(L"res/bird_001.png"));
		animation->add(new Image(L"res/bird_003.png"));
		animation->add(new Image(L"res/bird_001.png"));
		animation->add(new Image(L"res/bird_003.png"));
		break;
	case 2:
		this->open(new Image(L"res/bird_001.png"));
		animation->add(new Image(L"res/bird_001.png"));
		animation->add(new Image(L"res/bird_004.png"));
		animation->add(new Image(L"res/bird_001.png"));
		animation->add(new Image(L"res/bird_004.png"));
		break;
	}
	// ѭ������֡����
	this->runAction(gcnew Loop(gcnew Animate(animation)));

	// ��ʼ�����趯��������΢΢������
	auto moveBy = gcnew MoveBy(0.4f, Vector2(0, 8));
	fly = gcnew Loop(gcnew Sequence({ moveBy, moveBy->reverse() }));

	// ��ʼ����ת������С��׹��ʱ����̧ͷ�����ͷ��
	rotate = gcnew Sequence({
		gcnew RotateTo(0.2f, -15),	// 0.2f ������ת�� -15 ��
		gcnew Delay(0.2f),			// �ȴ� 0.2f ��
		gcnew RotateTo(0.5f, 90)	// 0.5f ������ת�� 90 �ȣ�С��ͷ���£�
		});
	// ���������������ֹ�����Զ�����
	rotate->retain();
	// ���ó�ʼ��״̬Ϊ 1
	this->setStatus(Status::Idle);
}

Bird::~Bird()
{
	// �ͷ����������Ķ���
	rotate->release();
}
void Bird::setStatus(Status status)
{
	switch (status)
	{
	case Status::Still:
	{
		this->stopAllActions();
		break;
	}
	case Status::Idle:
	{
		this->runAction(fly);
		break;
	}
	case Status::StartToFly:
	{
		fly->stop();						// ֹͣ���»ζ�����
		animation->setInterval(0.5f);		// ����С���ȶ������ٶ�
		// break;
	}
	case Status::Fly:
	{
		this->stopAction(L"rotate");		// ֹͣǰһ����ת����
		auto newRotate = rotate->clone();
		newRotate->setName(L"rotate");
		this->runAction(newRotate);
		break;
	}
	default:
		break;
	}
}
