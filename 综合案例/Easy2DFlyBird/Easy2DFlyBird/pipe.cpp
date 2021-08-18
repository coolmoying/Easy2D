#include "pipe.h"

Pipe::Pipe()
{
	scored = false;
	float height = Random::range(120.0f, 150.0f);
	// 创建上水管
	auto pipe1 = gcnew Sprite(new Image(L"res/down.png"));
	pipe1->crop(Rect(0, 300 - height,52,320));
	pipe1->setPosY(0);

	// 创建下水管
	auto pipe2 = gcnew Sprite(new Image(L"res/up.png"));
	pipe2->setAnchor(0, 0);
	pipe2->crop(Rect(0, 0, 52, height));
	pipe2->setPosY(512-height);

	// 把上下水管添加为子成员
	this->addChild(pipe1);
	this->addChild(pipe2);
}

Pipe::~Pipe()
{

}
