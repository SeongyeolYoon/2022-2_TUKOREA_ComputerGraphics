#include <iostream>
#include <string>
#include <random>
#include <cstdlib>
#include <Windows.h>

std::mt19937_64 mersenne{ std::random_device{}() };
std::uniform_int_distribution<int> uiXPos{ 0,800 };
std::uniform_int_distribution<int> uiYPos{ 0,600 };

class Rect;
bool isMe{ false };

bool isCollide(const Rect&,const Rect&);

class Rect {
private:
	int left;
	int bottom;
	int right;
	int top;
public:
	Rect(const int& _left = 0, const int& _bottom = 0, const int& _right = 0, const int& _top = 0)
	{
		if (_left > _right) {
			left = _right;
			right = _left;
		}
		else {
			left = _left;
			right = _right;
		}
		if (_bottom > _top) {
			bottom = _top;
			top = _bottom;
		}
		else {
			bottom = _bottom;
			top = _top;
		}
	}

	void update()
	{
		if (GetAsyncKeyState('W')) {
			if (isMe) {
				top += 10;
				bottom += 10;
				if (top > 600) {
					std::cout << "out of range" << std::endl;
					top -= 10;
					bottom -= 10;
				}
			}
			else {
				top += 20;
				bottom += 20;
				if (top > 600) {
					std::cout << "out of range" << std::endl;
					top -= 20;
					bottom -= 20;
				}
			}
		}
		else if (GetAsyncKeyState('A')) {
			if (isMe) {
				left -= 10;
				right -= 10;
				if (left < 0) {
					std::cout << "out of range" << std::endl;
					left += 10;
					right += 10;
				}
			}
			else {
				left -= 20;
				right -= 20;
				if (left < 0) {
					std::cout << "out of range" << std::endl;
					left += 20;
					right += 20;
				}
			}
		}
		else if (GetAsyncKeyState('S')) {
			if (isMe) {
				top -= 10;
				bottom -= 10;
				if (bottom < 0) {
					std::cout << "out of range" << std::endl;
					top += 10;
					bottom += 10;
				}
			}
			else {
				top -= 20;
				bottom -= 20;
				if (bottom < 0) {
					std::cout << "out of range" << std::endl;
					top += 20;
					bottom += 20;
				}
			}
		}
		else if (GetAsyncKeyState('D')) {
			if (isMe) {
				left += 10;
				right += 10;
				if (right > 800) {
					std::cout << "out of range" << std::endl;
					left -= 10;
					right -= 10;
				}
			}
			else {
				left += 20;
				right += 20;

				if (right > 800) {
					std::cout << "out of range" << std::endl;
					left -= 20;
					right -= 20;
				}
			}
		}
		system("pause");
	}

	void render(const std::string& str)
	{
		std::cout << str << ": (" << left << "," << bottom << ") " << "(" << right << "," << top << ")" << std::endl;
	}

	const int& getLeft() const
	{
		return left;
	}

	const int& getBottom() const	
	{
		return bottom;
	}

	const int& getTop() const
	{
		return top;
	}

	const int& getRight() const
	{
		return right;
	}
};

int main()
{
	Rect defaultRect{ uiXPos(mersenne) / 10 * 10, uiYPos(mersenne) / 10 * 10, uiXPos(mersenne) / 10 * 10, uiYPos(mersenne) / 10 * 10 };
	Rect myRect{ uiXPos(mersenne) / 10 * 10, uiYPos(mersenne) / 10 * 10, uiXPos(mersenne) / 10 * 10, uiYPos(mersenne) / 10 * 10 };

	while (true) {
		isMe = !isMe;
		if (isMe)
			myRect.update();
		else
			defaultRect.update();
		system("cls");
		defaultRect.render("Default");
		myRect.render("MyRect");

		if (isCollide(defaultRect, myRect)) {
			std::cout << "Default && MyRect is collide!!" << std::endl;
			system("pause");
		}
	}
}

bool isCollide(const Rect& defaultRect, const Rect& myRect)
{
	// AABB
	if ((defaultRect.getLeft() < myRect.getRight()) && (defaultRect.getRight() > myRect.getLeft()) 
		&& (defaultRect.getTop() > myRect.getBottom()) && (defaultRect.getBottom() < myRect.getTop()))
		return true;
	return false;
}