#ifndef EGELAB_H
#define EGELAB_H

#include "graphics.h"
#include <string>
#include <array>

//  定义 Controller 类。这个类将负责初始化图形环境、销毁环境、设置图形窗口的尺寸
class Controller {
private:
	std::string shape;

public:
	Controller() = default;  // 默认构造函数，不执行任何特殊操作

	Controller(std::string shape) : shape{ shape } {}  // 带参数的构造函数，初始化shape成员变量

	virtual ~Controller() = default;  // 虚析构函数，确保在派生类对象销毁时能够正确释放资源

	virtual void draw() = 0;  // 纯虚函数，用于绘制形状，需要在派生类中实现

	void Initialize() { setinitmode(0, 500, 50); }  // 设置 Initialize 函数，该函数用来初始化参数

	void Destroy() { cleardevice(); }  //  设置 Destroy 函数，该函数用来清除图像内容

	void Setlength() { initgraph(640, 480); }  //  设置 Setlength 函数，该函数用来初始化绘图环境

	std::string getInfo() { return shape; }  // 获取形状信息的函数

	void setInfo(std::string shape) { this->shape = shape; }  // 设置形状信息的函数
};

// 定义 Point 函数。这个类表示一个点的二维坐标。
class Point : public Controller {
private:
	int x;
	int y;

public:
	Point(int x, int y) : x{ x }, y{ y } {}

	Point() : Point(0, 0) {}  // 默认构造函数，将点的x和y坐标初始化为0

	int getX() { return x; }

	int getY() { return y; }

	void setX(int x) { this->x = x; }

	void setY(int y) { this->y = y; }
};

// 定义 Color 函数。这个类表示在图形环境中可以使用的颜色。
class Color : public Point {
private:
	std::string color;

public:
	Color() = default;

	Color(std::string color) : color{color} {}

	// 设置颜色为红色的函数
	void R() {
		setcolor(RED);  // 设置线条颜色为红色
		setfillcolor(RED);  // 设置填充颜色为红色
	}

	// 设置颜色为绿色的函数
	void G() {
		setcolor(GREEN);
		setfillcolor(GREEN);
	}

	// 设置颜色为蓝色的函数
	void B() {
		setcolor(BLUE);
		setfillcolor(BLUE);
	}

	std::string getInfo() { return color; }

	void setInfo(std::string  color) { this->color = color; }
};

//定义 Circle 函数，用来完成绘制圆形的操作
class Circle : public Color {
private:
	int x;
	int y;
	int radius;

public:
	Circle(int x, int y, int radius) : x{ x }, y{ y }, radius{ radius } {}

	Circle() : Circle(0, 0, 0) {}

	int getX() { return x; }

	int getY() { return y; }

	int getRadius() { return radius; }

	//  设置 setCircle 函数，用来获取用户输入的圆的相关信息
	void setCircle() {
		char buf[100];
		inputbox_getline("ikun画板", "请输入圆心x坐标", buf, 100);
		this->x = atoi(buf);  //使用atoi()函数将字符串转变为整型变量
		inputbox_getline("ikun画板", "请输入圆心y坐标", buf, 100);
		this->y = atoi(buf);
		inputbox_getline("ikun画板", "请输入半径", buf, 100);
		this->radius = atoi(buf);
	}

	//  重写父类 Controller 中的draw函数
	void draw() override{
		Color::R();  //  设置线条颜色为红色
		circle(x, y, radius);  // 绘制一个圆，圆心为(x, y)，半径为radius
		getch();
	}
};

//设置 Rectangles 函数，用来完成绘制矩形的操作
class Rectangles : public Color {
private:
	int left;
	int top;
	int right;
	int bottom;
	bool filled;

public:
	Rectangles(int left, int top, int right, int bottom, bool filled = true) : left{ left }, top{ top }, right{ right }, bottom{ bottom }, filled{ filled } {}

	Rectangles() : Rectangles(0, 0, 0, 0) {}

	int getLeft() { return left; }

	int gettop() { return top; }

	int getRight() { return right; }

	int getBottom() { return bottom; }

	bool isFilled() const { return filled; } // 获取是否填充的布尔值

	void setFilled(bool filled) { this->filled = filled; } // 设置是否填充的布尔值

	//  设置 setRectangle 函数，用来获取用户输入的矩形的相关信息
	void setRectangle() {
		char buf[100];
		inputbox_getline("ikun画板", "请输入矩形左部x坐标", buf, 100);
		this->left = atoi(buf);
		inputbox_getline("ikun画板", "请输入矩形上部y坐标", buf, 100);
		this->top = atoi(buf);
		inputbox_getline("ikun画板", "请输入矩形右部x坐标", buf, 100);
		this->right = atoi(buf);
		inputbox_getline("ikun画板", "请输入矩形下部y坐标", buf, 100);
		this->bottom = atoi(buf);
	}

	//  重写父类 Controller 中的 draw 函数
	void draw() override{
		Color::G();  // 设置线条和填充颜色为绿色
		bar(left, top, right, bottom); //矩形左部x坐标， 上部y坐标， 右部x坐标，下部y坐标
		getch();
	}
};

//设置 Triangle 函数，用来完成绘制三角形的操作
class Triangle : public Color {
private:
	std::array<int, 6> pt;
	bool filled;

public:
	Triangle(std::array<int, 6> pt, bool filled = true) : pt(pt) , filled(filled){}

	Triangle() : Triangle(std::array<int, 6>{0, 0, 0, 0, 0, 0}) {}

	std::array<int, 6> getPt() { return pt; }

	bool isFilled() const { return filled; }

	void setFilled(bool filled) { this->filled = filled; }

	//  设置 setTriangle 函数，用来获取用户输入的三角形的相关信息
	void setTriangle() {
		char buf[100];
		for (int i = 0; i < 6; i += 2) {
			inputbox_getline("ikun画板", "请输入多边形的x坐标：", buf, 100);
			//使用 if 语句判断用户是否输入正确
			if (atoi(buf) == 0) {
				xyprintf(0, 0, "输入错误！请重新输入坐标！\n");
				i -= 2; // 如果输入不正确，跳过此次循环
				continue;
			}
			this->pt[i] = atoi(buf);
			inputbox_getline("ikun画板", "请输入多边形的y坐标：", buf, 100);
			//使用 if 语句判断用户是否输入正确
			if (atoi(buf) == 0) {
				xyprintf(0, 0, "输入错误！请重新输入坐标！\n");
				i -= 2; // 如果输入不正确，跳过此次循环
				continue;
			}
			this->pt[i + 1] = atoi(buf);
		}
	}

	//  重写父类 Controller 中的 draw 函数
	void draw() override{
		Color::B();  // 设置线条和填充颜色为蓝色
		int* position;
		position = pt.data();  // 将 pt 对象的 data 方法返回的指针赋值给 position
		fillpoly(3, position);
		getch();
	}

	~Triangle() override {}
};


//  设置 Drawpicture 函数，用来完成绘图功能
void Drawpicture() {
	char buf[100];
	inputbox_getline("ikun画板", "欢迎您进入ikun画板，请根据菜单选择您想进行的操作：\n1.画圆\n2.画矩形\n3.画三角形", buf, 100); //弹出一个输入框，提示用户进行操作选择
	int choice = atoi(buf);  // 用整型变量 choice 来存储用户的选择

	//  完成用户选择的操作
	if (choice == 1) {
		Circle circle;
		circle.setCircle();
		circle.draw();
	}

	else if (choice == 2) {
		Rectangles rectangle;
		rectangle.setRectangle();
		rectangle.draw();
	}

	else if (choice == 3) {
		Triangle triangle;
		triangle.setTriangle();
		triangle.draw();
	}

	//  输入错误会提醒
	else {
		setcolor(RED);
		xyprintf(0, 0, "Error input!");
	}
}

//设置 Setgetline 函数。这个函数用来完成绘图板的基础功能
void Setgetline(Controller* gra) {
	char buf[100];
	inputbox_getline("ikun画板", "欢迎您进入ikun画板，请根据菜单选择您想进行的操作：\n1.清除屏幕\n2.作画\n3.退出", buf, 100); //弹出一个输入框，提示用户进行操作选择
	int choice = atoi(buf);

	// 完成用户选择的操作
	if (choice == 1) { gra->Destroy(); }
	else if (choice == 2) { Drawpicture(); }
	else if (choice == 3) { exit(0); }
	// 输入错误会提醒
	else {
		setcolor(RED);
		xyprintf(0, 0, "Error input!");
	}
}
#endif // !EGELAB_H