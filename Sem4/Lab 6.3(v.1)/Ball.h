#pragma once
#include "framework.h"



#define COUNT_BALLS 5

#define WORKSPACE_X 50
#define WORKSPACE_Y 50
#define WORKSPACE_DX 700
#define WORKSPACE_DY 300
#define MAX_RADIUS 40
#define MIN_RADIUS 5
#define MAX_WEIGHT 10
#define MAX_SPEED 5

enum horDirections
{
	left, right
};

enum verDirections
{
	up, down
};

class Ball
{
private:
	int _x;
	int _y;
	int _radius;
	int _weight;
	double _speedX;
	double _speedY;
public:
	Ball(int _x, int _y, int _radius, int _weight, double _speedX, double _speedY)
		:_x{ _x }, _y{ _y },
		_radius{_radius}, _weight{_weight},
		_speedX{_speedX},_speedY{_speedY}{}
	Ball() :Ball(rand() % (WORKSPACE_DX - MIN_RADIUS) + MIN_RADIUS + 1,
		rand() % (WORKSPACE_DY - MIN_RADIUS) + MIN_RADIUS + 1,
		rand() % (MAX_RADIUS - MIN_RADIUS) + MIN_RADIUS + 1,
		rand() % MAX_WEIGHT + 1,
		rand() % MAX_SPEED + 1,
		rand() % MAX_SPEED + 1) {}

	void Tick(horDirections& hor, verDirections& ver) {
		if (_speedX < 0) {
			_speedX *= -1;
			hor == left ? hor = right : hor = left;
			ver == up ? ver = down : ver = up;
		}


		if (hor == right)
		{
			_x += _speedX;


			if (_x + 2 * _radius >=  WORKSPACE_X + WORKSPACE_DX)
			{
				_x = WORKSPACE_X + WORKSPACE_DX - 2* _radius ;
				hor = left;
			}
		}
		else if (hor == left)
		{
			_x -= _speedX;
			if (_x <= WORKSPACE_X)
			{
				_x = WORKSPACE_X;
				hor = right;
			}
		}
		////////////////
		if (ver == up)
		{
			_y -= _speedY;
			if (_y <= WORKSPACE_Y)
			{
				_y = WORKSPACE_Y;
				ver = down;
			}
		}
		else if (ver == down)
		{
			_y += _speedY;
			if (_y + 2 * _radius + _speedY >= WORKSPACE_Y + WORKSPACE_DY)
			{
				_y = WORKSPACE_Y + WORKSPACE_DY - 2 * _radius;
				ver = up;
			}
		}
	}

	void NewImage(HDC hdc, HBRUSH brush)
	{



		brush = CreateSolidBrush(RGB(100, 150, 255));
		SelectObject(hdc, brush);
		Ellipse(hdc, _x, _y, _x + 2 * _radius, _y + 2 * _radius);
		DeleteObject(brush);


	}
	void setR() {
		_radius = rand() % (MAX_RADIUS - MIN_RADIUS) + MIN_RADIUS + 1;
	}

	friend void Crash(Ball* balls, horDirections *hors, verDirections *vers, HANDLE hFile) {
		for (int i = 0; i < COUNT_BALLS - 1; i++) {
			for (int j = i + 1; j < COUNT_BALLS	; j++) {
				if ((double)sqrt(
					pow(balls[i]._x - balls[j]._x + balls[i]._radius - balls[j]._radius, 2) +
					pow(balls[i]._y - balls[j]._y + balls[i]._radius - balls[j]._radius, 2)) <=
					balls[i]._radius + balls[j]._radius)
				{
					vers[i] == up ? vers[i] = down : vers[i] = up;
					hors[i] == left ? hors[i] = right : hors[i] = left;

					vers[j] == up ? vers[j] = down : vers[j] = up;
					hors[j] == left ? hors[j] = right : hors[j] = left;
					//if ((balls[i]._speedX == 0 && balls[j]._speedX == 0) ||
					//	(balls[i]._speedY == 0 && balls[j]._speedY == 0))
					//{
					//	if (balls[i]._weight > balls[j]._weight && balls[j]._weight == 0)
					//	{
					//		double tmpSpeedX = balls[i]._speedX, tmpSpeedY = balls[i]._speedY;
					//		balls[i]._speedX = () / ()
					//	}
					//}
					
					WriteFile(hFile, L"123", 8, NULL, NULL);
					//logF << "Столкновение шаров №" << i << " и №" << j<< std::endl;
				}


			}
		}
	}
};

