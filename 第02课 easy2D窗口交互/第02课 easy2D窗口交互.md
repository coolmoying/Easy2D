easy2D窗口交互

## 窗口交互主要分为 按键交互和鼠标交互，easy2D的交互方式主要有两种

+ 自己用监听器实现两种交互
+ 通过继承重写onUpdate()函数

**监听器实现**

```c
#include <easy2d/easy2d.h>
using namespace easy2d;
int main() 
{
	Logger::showConsole(false);
	if (Game::init(L"按键交互", 800, 600))
	{
		auto scene = gcnew Scene;
		auto text = gcnew Text(L"交互测试");
		text->setPosX(Window::getWidth() / 2);
		text->setPosY(Window::getHeight() / 2);
		auto callBack = [](Event* evt,Text* text)
		{
			if (evt->type == Event::KeyDown) 
			{
				if (Input::isDown(KeyCode::Up)) 
				{
					text->setPosY(text->getPosY() - 20);
				}
				if (Input::isDown(KeyCode::Down))
				{
					text->setPosY(text->getPosY()+ 20);
				}
				if (Input::isDown(KeyCode::Left))
				{
					text->setPosX(text->getPosX() - 20);
				}
				if (Input::isDown(KeyCode::Right))
				{
					text->setPosX(text->getPosX()+ 20);
				}
			}
			if (Input::isPress(MouseCode::Left))
			{
				bool state = text->isVisible();
				text->setVisible(!state);
			}	
		};
		text->addListener(std::bind(callBack,std::placeholders::_1,text));
		scene->addChild(text);
		SceneManager::enter(scene);
		Game::start();
	}
	Game::destroy();
	return 0;
}
```

**重写实现**

```c
#include <easy2d/easy2d.h>
using namespace easy2d;

// 人物类
class Man : public Sprite
{
public:
	Man()
	{
		// 加载图片
		this->open(L"man.png");
		// 居中显示在屏幕上
		this->setAnchor(0.5f, 0.5f);
		this->setPos(Window::getWidth() / 2, Window::getHeight() / 2);
		// 缩小图片大小
		this->setScale(0.5);
	}

	void onUpdate() override
	{
		if (Input::isDown(KeyCode::Up))
		{
			// Man 的 Y 坐标减少 2
			this->movePosY(-2);
		}
		else if (Input::isDown(KeyCode::Down))
		{
			// Man 的 Y 坐标增加 2
			this->movePosY(2);
		}

		if (Input::isDown(KeyCode::Left))
		{
			// Man 的 X 坐标减少 2
			this->movePosX(-2);
		}
		else if (Input::isDown(KeyCode::Right))
		{
			// Man 的 X 坐标增加 2
			this->movePosX(2);
		}

		// 按下鼠标左键，顺时针旋转小人
		if (Input::isDown(MouseCode::Left))
		{
			// 获取当前角度
			double rotation = this->getRotation();
			// 设置角度值+2
			this->setRotation(rotation + 2);
		}

		// 点击鼠标右键，隐藏或显示小人
		if (Input::isPress(MouseCode::Right))
		{
			// 获取当前显示状态
			bool state = this->isVisible();
			// 设置相反的显示状态
			this->setVisible(!state);
		}
	}
};

int main()
{
	// 关闭控制台
	Logger::showConsole(false);

	if (Game::init())
	{
		// 设置窗口标题和窗口大小
		Window::setTitle(L"Moving Man");
		Window::setSize(640, 480);

		// 创建场景
		auto scene = gcnew Scene;
		// 进入该场景
		SceneManager::enter(scene);

		// 创建一个 Man 对象
		auto hero = gcnew Man;
		// 将 Man 添加到场景中
		scene->addChild(hero);

		// 创建说明文字
		auto text = gcnew Text(L"按下上下左右键移动\n按鼠标左键旋转\n点击鼠标右键隐藏");
		// 设置文字位置
		text->setAnchor(0.5, 0.5);
		text->setPosX(Window::getWidth() / 2);
		text->setPosY(Window::getHeight() - 50);
		scene->addChild(text);

		Game::start();
	}
	Game::destroy();
	return 0;
}
```

## Listener 监听器

Listener 监听器类用于监听某个事件的发生，并作出相应的处理。

例如，下面的代码创建了一个监听鼠标按下的事件：

```c++
// 监听器的回调函数
auto callback = [](Event* evt)
{
    // 判断事件类型是否是鼠标按下
    if (evt->type == Event::MouseDown)
    {
        // 鼠标按下事件发生了
        // 作出相应处理
    }
};

// 创建监听器
auto lis = gcnew Listener(callback);
// 让某个节点使用这个监听器
node->addListener(lis);
```

上面的代码也许晦涩难懂，简单来说，当一个事件发生时，事件会逐一发送给每一个节点（node），节点再将事件转发给监听器，监听器收到事件时会调用回调函数（callback）来处理这个事件。

监听器可以监听到的事件有以下几种：

```c++
// 事件类型枚举
enum Type
{
    MouseMove,  // 鼠标移动
    MouseDown,  // 鼠标按下
    MouseUp,    // 鼠标抬起
    MouseWheel, // 鼠标滚轮滑动
    KeyDown,    // 按键按下
    KeyUp       // 按键抬起
};
```

下面的回调函数示例给出了每种类型事件的处理方式：

```c++
// 监听器的回调函数
// 展示了所有事件的处理方式
auto callback = [](Event* evt)
{
    if (evt->type == Event::MouseMove)
    {
        // 鼠标移动事件发生了
        // 将事件类型转换为事件的实际类型
        auto mouseEvt = (MouseMoveEvent*)evt;
        mouseEvt->x;    // 鼠标 x 坐标
        mouseEvt->y;    // 鼠标 y 坐标
    }
    else if (evt->type == Event::MouseDown)
    {
        // 鼠标按下事件发生了
        // 将事件类型转换为事件的实际类型
        auto mouseEvt = (MouseDownEvent*)evt;
        mouseEvt->x;        // 鼠标 x 坐标
        mouseEvt->y;        // 鼠标 y 坐标
        mouseEvt->button;   // 鼠标按键键值 MouseCode
    }
    else if (evt->type == Event::MouseUp)
    {
        // 鼠标抬起事件发生了
        // 将事件类型转换为事件的实际类型
        auto mouseEvt = (MouseUpEvent*)evt;
        mouseEvt->x;        // 鼠标 x 坐标
        mouseEvt->y;        // 鼠标 y 坐标
        mouseEvt->button;   // 鼠标按键键值 MouseCode
    }
    else if (evt->type == Event::MouseWheel)
    {
        // 鼠标滚轮滑动事件发生了
        // 将事件类型转换为事件的实际类型
        auto mouseEvt = (MouseWheelEvent*)evt;
        mouseEvt->x;        // 鼠标 x 坐标
        mouseEvt->y;        // 鼠标 y 坐标
        mouseEvt->delta;    // 鼠标滚轮滑动幅度
    }
    else if (evt->type == Event::KeyDown)
    {
        // 键盘按下事件发生了
        // 将事件类型转换为事件的实际类型
        auto keyEvt = (KeyDownEvent*)evt;
        keyEvt->key;    // 键盘按键键值 KeyCode
        keyEvt->count;  // 按键触发次数
    }
    else if (evt->type == Event::KeyUp)
    {
        // 键盘抬起事件发生了
        // 将事件类型转换为事件的实际类型
        auto keyEvt = (KeyUpEvent*)evt;
        keyEvt->key;    // 键盘按键键值 KeyCode
        keyEvt->count;  // 按键触发次数
    }
};
```

### 监听器的启动和暂停

创建监听器后，可以调用 `start` 和 `stop` 函数启动和暂停一个监听器

```c++
auto lis = gcnew Listener();
// 启动监听器（默认就是启动状态）
lis->start();
// 暂停监听器
lis->stop();
```

### 监听器的添加和移除

创建监听器后，需要将其添加到节点上，才可以接收发送到该节点的事件：

```
auto lis = gcnew Listener();
// 添加监听器
node->addListener(lis);
// 移除监听器
node->removeListener(lis);
```

监听器可以有名字，通过名字可以启动、暂停、移除指定的监听器

```c++
auto lis = gcnew Listener();
node->addListener(lis);

// 设置监听器的名称
lis->setName(L"my_listener");
// 启动名称为 my_listener 的监听器
node->startListener(L"my_listener");
// 暂停名称为 my_listener 的监听器
node->stopListener(L"my_listener");
// 移除名称为 my_listener 的监听器
node->removeListener(L"my_listener");
```

也可以启动、暂停、移除一个节点上的所有监听器

```c++
// 启动所有监听器
node->startAllListeners();
// 暂停所有监听器
node->stopAllListeners();
// 移除所有监听器
node->removeAllListeners();
```

### 自定义事件

出了上面几种预先定义的事件，用户也可以自己定义事件。

下面的代码展示了如何创建自定义的事件：

```c++
// 自定义事件类型
enum MyEventType
{
    // 第一个类型，为预定义事件类型最后一个值 + 1
    First = Event::Type::Last + 1
};

// 自定义事件
struct MyEvent
	: public Event
{
    // 自定义事件的类型为 First
    MyEvent() : Event(MyEventType::First) {}

    // 自定义事件的成员变量
    int value = 0;
};
```

使用下面的代码将自定义事件分发给节点及其所有子节点：

```c++
// 创建自定义事件
MyEvent* evt = gcnew MyEvent;
// 设置自定义事件的成员变量
evt->value = 3;
// 分发该事件，事件会发送给节点及其所有子节点
node->dispatch(evt);
```

在监听器中处理自定义事件：

```c++
// 回调函数处理
auto callback = [](Event* evt)
{
    // 判断事件类型是否是鼠标按下
    if (evt->type == Event::MouseDown)
    {
        // 自定义事件发生了
        // 将事件类型转换为事件的实际类型
        auto myEvt = (MyEvent*)evt;
        myEvt->value;   // 获取自定义事件的成员变量
    }
};
```
