#include "pipes.h"

Pipes::Pipes()
{
	number = 0;
	// 添加三根水管
	addPipe();
	addPipe();
	addPipe();
	// 关闭 onUpdate 函数
	this->setAutoUpdate(false);
}

Pipes::~Pipes()
{

}

void Pipes::onUpdate()
{
	for (int i = 0; i < number; i++)
	{
		pipes[i]->movePos(-2, 0);
	}
	// 判断最前面的水管是否移动到屏幕外
	if (pipes[0]->getPosX() <= -54)
	{
		// 若第一个水管在屏幕外，删除这个水管
		this->removeChild(pipes[0]);
		// 把原来下标为 1、2 的水管位置提前
		pipes[0] = pipes[1];
		pipes[1] = pipes[2];
		// 水管数量减一
		number--;
		// 添加一个新水管
		addPipe();
	}
}

void Pipes::addPipe()
{
	// 水管最大数量为 3
	if (number >= 3)
		return;

	// 创建水管
	auto pipe = gcnew Pipe();
	// 设置水管横坐标
	if (number == 0)
	{
		// 第一个水管在屏幕外130像素处
		pipe->setPosX(Window::getWidth() + 130);
	}
	else
	{
		// 其他水管在前一个水管后方200像素处
		pipe->setPosX(pipes[number - 1]->getPosX() + 200);
	}
	// 保存 pipe 的指针
	pipes[number] = pipe;
	// 水管数量加一
	number++;
	this->addChild(pipe);
}


void Pipes::start()
{
	this->setAutoUpdate(true);
}

void Pipes::stop()
{
	this->setAutoUpdate(false);
}
