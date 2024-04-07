#ifndef EGELAB_H
#define EGELAB_H

#include "graphics.h"
#include <string>
#include <array>

//  ���� Controller �ࡣ����ཫ�����ʼ��ͼ�λ��������ٻ���������ͼ�δ��ڵĳߴ�
class Controller {
private:
	std::string shape;

public:
	Controller() = default;  // Ĭ�Ϲ��캯������ִ���κ��������

	Controller(std::string shape) : shape{ shape } {}  // �������Ĺ��캯������ʼ��shape��Ա����

	virtual ~Controller() = default;  // ������������ȷ�����������������ʱ�ܹ���ȷ�ͷ���Դ

	virtual void draw() = 0;  // ���麯�������ڻ�����״����Ҫ����������ʵ��

	void Initialize() { setinitmode(0, 500, 50); }  // ���� Initialize �������ú���������ʼ������

	void Destroy() { cleardevice(); }  //  ���� Destroy �������ú����������ͼ������

	void Setlength() { initgraph(640, 480); }  //  ���� Setlength �������ú���������ʼ����ͼ����

	std::string getInfo() { return shape; }  // ��ȡ��״��Ϣ�ĺ���

	void setInfo(std::string shape) { this->shape = shape; }  // ������״��Ϣ�ĺ���
};

// ���� Point ������������ʾһ����Ķ�ά���ꡣ
class Point : public Controller {
private:
	int x;
	int y;

public:
	Point(int x, int y) : x{ x }, y{ y } {}

	Point() : Point(0, 0) {}  // Ĭ�Ϲ��캯���������x��y�����ʼ��Ϊ0

	int getX() { return x; }

	int getY() { return y; }

	void setX(int x) { this->x = x; }

	void setY(int y) { this->y = y; }
};

// ���� Color ������������ʾ��ͼ�λ����п���ʹ�õ���ɫ��
class Color : public Point {
private:
	std::string color;

public:
	Color() = default;

	Color(std::string color) : color{color} {}

	// ������ɫΪ��ɫ�ĺ���
	void R() {
		setcolor(RED);  // ����������ɫΪ��ɫ
		setfillcolor(RED);  // ���������ɫΪ��ɫ
	}

	// ������ɫΪ��ɫ�ĺ���
	void G() {
		setcolor(GREEN);
		setfillcolor(GREEN);
	}

	// ������ɫΪ��ɫ�ĺ���
	void B() {
		setcolor(BLUE);
		setfillcolor(BLUE);
	}

	std::string getInfo() { return color; }

	void setInfo(std::string  color) { this->color = color; }
};

//���� Circle ������������ɻ���Բ�εĲ���
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

	//  ���� setCircle ������������ȡ�û������Բ�������Ϣ
	void setCircle() {
		char buf[100];
		inputbox_getline("ikun����", "������Բ��x����", buf, 100);
		this->x = atoi(buf);  //ʹ��atoi()�������ַ���ת��Ϊ���ͱ���
		inputbox_getline("ikun����", "������Բ��y����", buf, 100);
		this->y = atoi(buf);
		inputbox_getline("ikun����", "������뾶", buf, 100);
		this->radius = atoi(buf);
	}

	//  ��д���� Controller �е�draw����
	void draw() override{
		Color::R();  //  ����������ɫΪ��ɫ
		circle(x, y, radius);  // ����һ��Բ��Բ��Ϊ(x, y)���뾶Ϊradius
		getch();
	}
};

//���� Rectangles ������������ɻ��ƾ��εĲ���
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

	bool isFilled() const { return filled; } // ��ȡ�Ƿ����Ĳ���ֵ

	void setFilled(bool filled) { this->filled = filled; } // �����Ƿ����Ĳ���ֵ

	//  ���� setRectangle ������������ȡ�û�����ľ��ε������Ϣ
	void setRectangle() {
		char buf[100];
		inputbox_getline("ikun����", "�����������x����", buf, 100);
		this->left = atoi(buf);
		inputbox_getline("ikun����", "����������ϲ�y����", buf, 100);
		this->top = atoi(buf);
		inputbox_getline("ikun����", "����������Ҳ�x����", buf, 100);
		this->right = atoi(buf);
		inputbox_getline("ikun����", "����������²�y����", buf, 100);
		this->bottom = atoi(buf);
	}

	//  ��д���� Controller �е� draw ����
	void draw() override{
		Color::G();  // ���������������ɫΪ��ɫ
		bar(left, top, right, bottom); //������x���꣬ �ϲ�y���꣬ �Ҳ�x���꣬�²�y����
		getch();
	}
};

//���� Triangle ������������ɻ��������εĲ���
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

	//  ���� setTriangle ������������ȡ�û�����������ε������Ϣ
	void setTriangle() {
		char buf[100];
		for (int i = 0; i < 6; i += 2) {
			inputbox_getline("ikun����", "���������ε�x���꣺", buf, 100);
			//ʹ�� if ����ж��û��Ƿ�������ȷ
			if (atoi(buf) == 0) {
				xyprintf(0, 0, "��������������������꣡\n");
				i -= 2; // ������벻��ȷ�������˴�ѭ��
				continue;
			}
			this->pt[i] = atoi(buf);
			inputbox_getline("ikun����", "���������ε�y���꣺", buf, 100);
			//ʹ�� if ����ж��û��Ƿ�������ȷ
			if (atoi(buf) == 0) {
				xyprintf(0, 0, "��������������������꣡\n");
				i -= 2; // ������벻��ȷ�������˴�ѭ��
				continue;
			}
			this->pt[i + 1] = atoi(buf);
		}
	}

	//  ��д���� Controller �е� draw ����
	void draw() override{
		Color::B();  // ���������������ɫΪ��ɫ
		int* position;
		position = pt.data();  // �� pt ����� data �������ص�ָ�븳ֵ�� position
		fillpoly(3, position);
		getch();
	}

	~Triangle() override {}
};


//  ���� Drawpicture ������������ɻ�ͼ����
void Drawpicture() {
	char buf[100];
	inputbox_getline("ikun����", "��ӭ������ikun���壬����ݲ˵�ѡ��������еĲ�����\n1.��Բ\n2.������\n3.��������", buf, 100); //����һ���������ʾ�û����в���ѡ��
	int choice = atoi(buf);  // �����ͱ��� choice ���洢�û���ѡ��

	//  ����û�ѡ��Ĳ���
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

	//  ������������
	else {
		setcolor(RED);
		xyprintf(0, 0, "Error input!");
	}
}

//���� Setgetline �������������������ɻ�ͼ��Ļ�������
void Setgetline(Controller* gra) {
	char buf[100];
	inputbox_getline("ikun����", "��ӭ������ikun���壬����ݲ˵�ѡ��������еĲ�����\n1.�����Ļ\n2.����\n3.�˳�", buf, 100); //����һ���������ʾ�û����в���ѡ��
	int choice = atoi(buf);

	// ����û�ѡ��Ĳ���
	if (choice == 1) { gra->Destroy(); }
	else if (choice == 2) { Drawpicture(); }
	else if (choice == 3) { exit(0); }
	// ������������
	else {
		setcolor(RED);
		xyprintf(0, 0, "Error input!");
	}
}
#endif // !EGELAB_H