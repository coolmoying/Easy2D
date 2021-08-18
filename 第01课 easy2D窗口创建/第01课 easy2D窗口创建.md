easy2D 创建窗口

## **创建窗口**

+ Game类:Game 类用来控制游戏主流程，它可以完成开始游戏、暂停游戏、退出游戏等一系列操作

+ Game::init()函数：游戏进行初始化,只能调用一次,当初始化失败时，init() 会返回 false
+ Game::start()函数:函数用来开始游戏，这个函数是阻塞的,只有当窗口关闭或退出游戏时，这个函数才返回
+ Game::destory()函数:函数用来销毁游戏过程产生的各类资源，它应该在程序的最后调用

一个 Easy2D 程序应由 **初始化**、**设计游戏内容**、**开始游戏**、**销毁资源**,如下测试代码:

```c++
#include <easy2d/easy2d.h>
#include <iostream>
using namespace std;
using namespace easy2d;

int main()
{
	if (Game::init()) 
	{
		Game::start();
	}
	Game::destroy();
	return 0;
}
```

<img src="C:\Users\cool莫影\Desktop\easy2D游戏引擎\01.png" alt="image-20210625142159560" style="zoom:50%;" />

## **调整窗口**

+ 隐藏控制台：	Logger::showConsole(false);  

```c++
class Logger
{
public:
	// 启用日志记录
	static void enable();
	// 关闭日志记录
	static void disable();
	// 输出日志消息
	static void messageln(String format, ...);
	// 输出警告
	static void warningln(String format, ...);
	// 输出错误
	static void errorln(String format, ...);
	// 打开/关闭控制台
	static void showConsole(bool show = true);
};
```

+ 窗口颜色:Renderer::setBackgroundColor(Color::LightBlue);

```c
Renderer:渲染
LightBlue: 淡蓝色
```

+ 窗口标题大小
  + Window::setTitle()函数设置窗口标题
  + Window::setSize() 函数设置窗口大小
  + Window::getWidth()函数与 Window::getHeight()函数用来获取窗口宽度和高度 

## **重要元素**

+ 场景与节点

  + 场景:游戏中的一个界面，你的游戏可以有类似主菜单、游戏界面、结束界面等多个场景
    + `SceneManager:` 是控制场景间切换的类,即场景管理器
    + `SceneManager::enter()` 函数进入你创建的场景中
    + `SceneManager::back()` 可以退出当前场景
  + 节点:场景中所有的元素都被称为`Node(节点)`，比如场景中的一个按钮，或者一张图片，它们都是节点的一种
    + Text：文本
    + Sprite：精灵
    + Button：按钮
    + ToggleButton： 开关按钮类
    + Menu:菜单类
    + Shape:形状类

+ 坐标系统

  Easy2D 使用左手坐标空间，坐标系原点在屏幕的左上角，x 轴向右为正，y 轴向下为正。

  <img src="C:\Users\cool莫影\Desktop\easy2D游戏引擎\02.png" alt="image-20210625151036567" style="zoom:50%;" />

` Anchor`(锚点) 是一个重要属性，它相当于节点的 “把手”。有了中心点，你就可以 “抓着” 它移动这个节点，或者旋转它。

`Node::setAnchor` 函数用于设置节点的中心点

## 内存回收机制

Easy2D 支持垃圾内存的自动回收，要使用这个功能，你需要使用 `gcnew` 代替 `new` 来创建对象。

使用 new 运算符创建的对象也可以手动调用 `autorelease` 函数，使其可以自动被回收。

```c++
// 创建一个自动回收的场景
auto scene1 = gcnew Scene;
// 创建一个自动回收的文本
auto text = gcnew Text(L"Hello Easy2D");

// 使用 new 创建对象
auto scene2 = new Scene;
// 调用 autorelease 函数，使 GC 自动对其进行回收
scene2->autorelease();
```

+ 坐标:
+ 锚点:

## 命名风格

- 小驼峰式命名法则，第一个单词小写，后面的单词首字母大写，如`Window::setTitle`
- 所有函数均按照`动词`+`名语`形式命名，如`Logger::showConsole`
- 获取对象的属性值：`get`+`属性名`，如`Node::getWidth`
- 修改对象的属性值：`set`+`属性名`，如`Node::setPos`
- 获取对象的状态(bool值)：`is`+`状态名`，如`Node::isVisiable`

