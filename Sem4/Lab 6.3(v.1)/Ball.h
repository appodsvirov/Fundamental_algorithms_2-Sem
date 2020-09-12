#pragma once
#include "framework.h"



#define COUNT_BALLS 4
#define ACCURACY 2
#define WORKSPACE_X 50
#define WORKSPACE_Y 50
#define WORKSPACE_DX 700
#define WORKSPACE_DY 300
#define MAX_RADIUS 40
#define MIN_RADIUS 10
#define MAX_WEIGHT 10
#define MAX_SPEED 8
#define TICK_TIMER 30

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
	bool flagstop;

public:
	Ball(int _x, int _y, int _radius, int _weight, double _speedX, double _speedY)
		:_x{ _x }, _y{ _y },
		_radius{_radius}, _weight{_weight},
		_speedX{ _speedX }, _speedY{ _speedY }, flagstop{}{}
	Ball() :Ball(rand() % (WORKSPACE_DX - MIN_RADIUS) + MIN_RADIUS + 1,
		rand() % (WORKSPACE_DY - MIN_RADIUS) + MIN_RADIUS + 1,
		rand() % (MAX_RADIUS - MIN_RADIUS) + MIN_RADIUS + 1,
		rand() % MAX_WEIGHT + 1, 
		rand() % MAX_SPEED + 1,
		rand() % MAX_SPEED + 1) {}

	void Tick(horDirections& hor, verDirections& ver) {
		if (flagstop) return;
		if (_speedX < 0) {
			_speedX *= -1;
			hor == left ? hor = right : hor = left;
		}
		if (_speedY < 0) {
			_speedX *= -1;
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



		brush = CreateSolidBrush(RGB(255, 255, 0));
		SelectObject(hdc, brush);
		Ellipse(hdc, _x, _y, _x + 2 * _radius, _y + 2 * _radius);
		DeleteObject(brush);


	}
	void setR() {
		_radius = rand() % (MAX_RADIUS - MIN_RADIUS) + MIN_RADIUS + 1;
	}

	void setStop() {
		flagstop ? flagstop = 0 : flagstop = 1;
	}

	bool setСoordinate(int x, int y) {
		bool fx{}, fy{};
		if (x >= WORKSPACE_X && x + 2 * _radius <= WORKSPACE_X + WORKSPACE_DX) {
			_x = x;
			fx = true;
		}
		if (y >= WORKSPACE_Y && y + 2 * _radius <= WORKSPACE_Y + WORKSPACE_DY) {
			_y = y;
			fy = true;
		}
		return fx || fy;
	}

	bool Short(int x, int y) 
	{
		if (x >= _x && x <= _x + 2 * _radius && y >= _y && y <= _y + 2 * _radius)
			return TRUE;
		return FALSE;
	}

	void SetСhanges(HWND hWnd,HWND ESpX, HWND ESpY, HWND EWeight, HWND ERadius)
	{
		const int INPUT_BUFFER = 32;
		char temp[INPUT_BUFFER];
		std::regex rgx2("\\d{2}");
		std::regex rgx("\\d");

		GetWindowTextA(ESpX, temp, INPUT_BUFFER);
		if (!std::regex_match(temp, rgx))
			::MessageBox(hWnd, L"Скорость - целое , положительное число, меньше 10",
				L"ERROOOOR!", MB_OK | MB_ICONWARNING);
		else _speedX = atoi(temp);
		GetWindowTextA(ESpY, temp, INPUT_BUFFER);
		if (!std::regex_match(temp, rgx))
			::MessageBox(hWnd, L"Скорость - целое , положительное число, меньше 10",
				L"ERROOOOR!", MB_OK | MB_ICONWARNING);
		else _speedY = atoi(temp);
		GetWindowTextA(EWeight, temp, INPUT_BUFFER);
		if (!std::regex_match(temp, rgx))
			::MessageBox(hWnd, L"Масса - натуральное число, меньше 10",
				L"ERROOOOR!", MB_OK | MB_ICONWARNING);
		else _weight = atoi(temp);
		GetWindowTextA(ERadius, temp, INPUT_BUFFER);
		_radius = atoi(temp);
		if (_radius == 0) ::MessageBox(hWnd, L"Масса - натуральное число",
		L"ERROOOOR!", MB_OK | MB_ICONWARNING);
		if (!std::regex_match(temp, rgx2))
			::MessageBox(hWnd, L"Радиус - натуральное число",
				L"ERROOOOR!", MB_OK | MB_ICONWARNING);
		else if (_radius < 10 || _radius > 40)
			::MessageBox(hWnd, L"Радиус - целое число, больше 9 и меньше 41",
			L"ERROOOOR!", MB_OK | MB_ICONWARNING);
	}

	friend void Load(Ball* balls, HANDLE& hFile)
	{
		char buf[500]{};
		char temp[5]{};
		hFile = CreateFile(L"DataFile.txt", GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, NULL, NULL);
		for (int i = 0; i < COUNT_BALLS; i++) 
		{
			_itoa_s(balls[i]._x, temp, 10);
			strcat(buf, temp);
			strcat(buf, " ");

			_itoa_s(balls[i]._y, temp, 10);
			strcat(buf, temp);
			strcat(buf, " ");

			_itoa_s(balls[i]._radius, temp, 10);
			strcat(buf, temp);
			strcat(buf, " ");

			_itoa_s(balls[i]._weight, temp, 10);
			strcat(buf, temp);
			strcat(buf, " ");

			_itoa_s(balls[i]._speedX, temp, 10);
			strcat(buf, temp);
			strcat(buf, " ");

			_itoa_s(balls[i]._speedY, temp, 10);
			strcat(buf, temp);
			strcat(buf, "\n");
		}
		WriteFile(hFile, buf, sizeof(buf), NULL, NULL);
		CloseHandle(hFile);
	}
	friend void Save(Ball* balls, HANDLE& hFile)
	{
		char buf[500]{};
		int temp;
		hFile = CreateFile(L"DataFile.txt", GENERIC_READ, 0, NULL, OPEN_ALWAYS, NULL, NULL);
		ReadFile(hFile, buf, sizeof(buf), NULL, NULL);
		std::istringstream	in(buf);
		for (int i = 0; i < COUNT_BALLS; i++) {
			in >> balls[i]._x >> balls[i]._y >> balls[i]._radius >>
				balls[i]._weight >> balls[i]._speedX >> balls[i]._speedY;
		}
		CloseHandle(hFile);
	}
	friend double Distance(Ball Iobj, Ball Jobj) {
		return (double)sqrt(
			pow(Iobj._x - Jobj._x + Iobj._radius - Jobj._radius, 2) +
			pow(Iobj._y - Jobj._y + Iobj._radius - Jobj._radius, 2));
	}

	friend void Crash(HWND hWnd,Ball* balls, horDirections *hors, verDirections *vers, HANDLE &hFile) {
		for (int i = 0; i < COUNT_BALLS - 1; i++) {
			for (int j = i + 1; j < COUNT_BALLS	; j++) {
				double ISpeedX = balls[i]._speedX, ISpeedY = balls[i]._speedY;
				double JSpeedX = balls[j]._speedX, JSpeedY = balls[j]._speedY;
				int IWt = balls[i]._weight, IRd = balls[i]._radius;
				int JWt = balls[j]._weight, JRd = balls[j]._radius;
				int IX = balls[i]._x, IY = balls[i]._y, &LkIX = balls[i]._x, &LkIY = balls[i]._y;
				int JX = balls[j]._x, JY = balls[j]._y, &LkJX = balls[j]._x, & LkJY = balls[j]._y;
				bool flagFalse = 1;

				if (hors[i] == left) ISpeedX *= -1;
				if (hors[j] == left) JSpeedX *= -1;
				if (vers[i] == up) ISpeedY *= -1;
				if (vers[j] == up) JSpeedY *= -1;

				double MdlWeight = (balls[i]._weight + balls[j]._weight) / 2;
				if (Distance(balls[i], balls[j]) <= balls[i]._radius + balls[j]._radius)
				{

					if (abs (IY + IRd - JY - JRd) <= 5 && ISpeedY == 0 && JSpeedY == 0)
					{
						if (IWt == JWt)
						{
							double tmp = balls[i]._speedX;
							balls[i]._speedX = balls[j]._speedX;
							balls[j]._speedX = tmp;
							if (hors[i] == right && hors[j] == left) {
								hors[i] = left; hors[j] = right;
							}
							else if (hors[i] == left && hors[j] == right) {
								hors[i] = right; hors[j] = left;
							}

						}
						else {
							balls[i]._speedX = ((IWt - JWt) * ISpeedX + 2 * JWt * JSpeedX) /
								(IWt + JWt);
							balls[j]._speedX = ((JWt - IWt) * JSpeedX + 2 * IWt * ISpeedX) /
								(IWt + JWt);
						}

						//if (LkIX - WORKSPACE_X <= ACCURACY && LkJX - LkIX - 2 * IRd <= ACCURACY||
						//	WORKSPACE_X + WORKSPACE_DX - LkIX - IRd <= ACCURACY ||
						//	LkIX - LkJX - 2 * JRd <= ACCURACY)
						//{
						//	balls[j]._speedX *= -1;
						//}
						//else if (LkJX - WORKSPACE_X <= ACCURACY && LkIX - LkJX - 2 * JRd <= ACCURACY ||
						//	WORKSPACE_X + WORKSPACE_DX - LkJX - JRd <= ACCURACY ||
						//	LkJX - LkIX - 2 * IRd <= ACCURACY)
						//{
						//	balls[i]._speedX *= -1;
						//}

						if (LkIX + IRd < LkJX + JRd) {
							if (balls[i].setСoordinate(LkJX - 2*IRd, LkIY));
							else if (balls[j].setСoordinate(LkIX + 2*IRd, LkJY));
						}
						else if (LkIX + IRd >= LkJX + JRd) {
							if (balls[i].setСoordinate(LkJX + 2 * JRd, LkIY));
							else if (balls[j].setСoordinate(LkIX - 2*JRd, LkJY));
						}

					}

					//111111111111111111111111111111111111111111111111
					else if (abs(IX + IRd - JX - JRd) <= 5 && ISpeedX == 0 && JSpeedX == 0)
					{
						if (IWt == JWt)
						{
							double tmp = balls[i]._speedY;
							balls[i]._speedY = balls[j]._speedY;
							balls[j]._speedY = tmp;
							ISpeedY = balls[i]._speedY;
							JSpeedY = balls[j]._speedY;
							if (vers[i] == down && vers[j] == up) {
								vers[i] = up; vers[j] = down;
							}
							else if (vers[i] == up && vers[j] == down) {
								vers[i] = down; vers[j] = up;
							}


						}
						else {
							balls[i]._speedY = ((IWt - JWt) * ISpeedY + 2 * JWt * JSpeedY) /
								(IWt + JWt);
							balls[j]._speedY = ((JWt - IWt) * JSpeedY + 2 * IWt * ISpeedY) /
								(IWt + JWt);
						}


						if (LkIY + IRd < LkJY + JRd) {
							if (balls[i].setСoordinate(LkIX, LkJY - 2 * IRd));
							else if (balls[j].setСoordinate(LkIX, LkIY + 2 * IRd));
						}
						else if (LkIY + IRd >= LkJY + JRd) {
							if (balls[i].setСoordinate(LkIX, LkJY + 2 * JRd));
							else if (balls[j].setСoordinate(LkJX, LkIY - 2 * JRd));
						}
					}
					//222222222222222222222222222222222222222222222222

					else if (IX <= JX && IY <= JY && Distance(balls[i], balls[j]) < IRd + JRd)
					{
						balls[i]._speedX = ((IWt - JWt) * abs(ISpeedX) + 2 * JWt * abs(JSpeedX)) /
							(IWt + JWt);
						balls[j]._speedX = ((JWt - IWt) * abs(JSpeedX) + 2 * IWt * abs(ISpeedX)) /
							(IWt + JWt);
						balls[i]._speedY = ((IWt - JWt) * abs(ISpeedY) + 2 * JWt * abs(JSpeedY)) /
							(IWt + JWt);
						balls[j]._speedY = ((JWt - IWt) * abs(JSpeedY) + 2 * IWt * abs(ISpeedY)) /
							(IWt + JWt);
						if (abs(IX - JX + IRd - JRd) < abs(IY - JY + IRd - JRd))
						{
							hors[i] == left?  hors[i] = right : hors[i] = left;
							hors[j] == left ? hors[j] = right : hors[j] = left;
						}
						else if (abs(IX - JX + IRd - JRd) > abs(IY - JY + IRd - JRd))
						{
							vers[i] == up ? vers[i] = down : vers[i] = up;
							vers[j] == up ? vers[j] = down : vers[j] = up;
						}
						else
						{
							vers[i] == up ? vers[i] = down : vers[i] = up;
							vers[j] == up ? vers[j] = down : vers[j] = up;
						}
						while (Distance(balls[i], balls[j]) < IRd + JRd + 2 * ACCURACY)
						{
							if (balls[i].setСoordinate(LkIX - 2, LkIY - 2));
							else if (balls[j].setСoordinate(LkJX + 2, LkJY + 2));
							else break;
							//if (Distance(balls[i], balls[j]) < IRd + JRd) InvalidateRect(hWnd, NULL, TRUE);
						}
					}
					else if (IX > JX && IY > JY && Distance(balls[i], balls[j]) < IRd + JRd) {

						balls[i]._speedX = ((IWt - JWt) * abs(ISpeedX) + 2 * JWt * abs(JSpeedX)) /
							(IWt + JWt);
						balls[j]._speedX = ((JWt - IWt) * abs(JSpeedX) + 2 * IWt * abs(ISpeedX)) /
							(IWt + JWt);
						balls[i]._speedY = ((IWt - JWt) * abs(ISpeedY) + 2 * JWt * abs(JSpeedY)) /
							(IWt + JWt);
						balls[j]._speedY = ((JWt - IWt) * abs(JSpeedY) + 2 * IWt * abs(ISpeedY)) /
							(IWt + JWt);
						if (abs(IX - JX + IRd - JRd) < abs(IY - JY + IRd - JRd))
						{
							hors[i] == left ? hors[i] = right : hors[i] = left;
							hors[j] == left ? hors[j] = right : hors[j] = left;
						}
						else if (abs(IX - JX + IRd - JRd) > abs(IY - JY + IRd - JRd))
						{
							vers[i] == up ? vers[i] = down : vers[i] = up;
							vers[j] == up ? vers[j] = down : vers[j] = up;
						}
						else
						{
							vers[i] == up ? vers[i] = down : vers[i] = up;
							vers[j] == up ? vers[j] = down : vers[j] = up;
						}
						while (Distance(balls[i], balls[j]) < IRd + JRd + 2 * ACCURACY)
						{
							
							if (balls[i].setСoordinate(LkIX + 2, LkIY + 2));
							else if (balls[j].setСoordinate(LkJX - 2, LkJY - 2));
							else break;
							if (Distance(balls[i], balls[j]) < IRd + JRd) InvalidateRect(hWnd, NULL, TRUE);
						}
					}


					else if (IX >= JX && IY <= JY && Distance(balls[i], balls[j]) < IRd + JRd) {

						balls[i]._speedX = ((IWt - JWt) * abs(ISpeedX) + 2 * JWt * abs(JSpeedX)) /
							(IWt + JWt);
						balls[j]._speedX = ((JWt - IWt) * abs(JSpeedX) + 2 * IWt * abs(ISpeedX)) /
							(IWt + JWt);
						balls[i]._speedY = ((IWt - JWt) * abs(ISpeedY) + 2 * JWt * abs(JSpeedY)) /
							(IWt + JWt);
						balls[j]._speedY = ((JWt - IWt) * abs(JSpeedY) + 2 * IWt * abs(ISpeedY)) /
							(IWt + JWt);
						if (abs(IX - JX + IRd - JRd) < abs(IY - JY + IRd - JRd))
						{
							hors[i] == left ? hors[i] = right : hors[i] = left;
							hors[j] == left ? hors[j] = right : hors[j] = left;
						}
						else if (abs(IX - JX + IRd - JRd) > abs(IY - JY + IRd - JRd))
						{
							vers[i] == up ? vers[i] = down : vers[i] = up;
							vers[j] == up ? vers[j] = down : vers[j] = up;
						}
						else
						{
							vers[i] == up ? vers[i] = down : vers[i] = up;
							vers[j] == up ? vers[j] = down : vers[j] = up;
						}
						while (Distance(balls[i], balls[j]) < IRd + JRd + 2 * ACCURACY)
						{
							if (balls[i].setСoordinate(LkIX + 2, LkIY - 2));
							else if (balls[j].setСoordinate(LkJX - 2, LkJY + 2));
							else break;
							if (Distance(balls[i], balls[j]) < IRd + JRd) InvalidateRect(hWnd, NULL, TRUE);
						}
					}


					else if (IX < JX && IY > JY && Distance(balls[i], balls[j]) < IRd + JRd) {

						balls[i]._speedX = ((IWt - JWt) * abs(ISpeedX) + 2 * JWt * abs(JSpeedX)) /
							(IWt + JWt);
						balls[j]._speedX = ((JWt - IWt) * abs(JSpeedX) + 2 * IWt * abs(ISpeedX)) /
							(IWt + JWt);
						balls[i]._speedY = ((IWt - JWt) * abs(ISpeedY) + 2 * JWt * abs(JSpeedY)) /
							(IWt + JWt);
						balls[j]._speedY = ((JWt - IWt) * abs(JSpeedY) + 2 * IWt * abs(ISpeedY)) /
							(IWt + JWt);
						if (abs(IX - JX + IRd - JRd) < abs(IY - JY + IRd - JRd))
						{
							hors[i] == left ? hors[i] = right : hors[i] = left;
							hors[j] == left ? hors[j] = right : hors[j] = left;
						}
						else if (abs(IX - JX + IRd - JRd) > abs(IY - JY + IRd - JRd))
						{
							vers[i] == up ? vers[i] = down : vers[i] = up;
							vers[j] == up ? vers[j] = down : vers[j] = up;
						}
						else
						{
							hors[i] == left ? hors[i] = right : hors[i] = left;
							hors[j] == left ? hors[j] = right : hors[j] = left;
							vers[i] == up ? vers[i] = down : vers[i] = up;
							vers[j] == up ? vers[j] = down : vers[j] = up;
						}
						while (Distance(balls[i], balls[j]) < IRd + JRd + 2 * ACCURACY)
						{
							if (balls[i].setСoordinate(LkIX - 2, LkIY + 2));
							else if (balls[j].setСoordinate(LkJX + 2, LkJY - 2));
							else break;
							if (Distance(balls[i], balls[j]) < IRd + JRd) InvalidateRect(hWnd, NULL, TRUE);
						}
					}

					char buf[270]{ "\nСтолкновение шаров №" };
					char temp[5] = {};
					_itoa_s(i, temp, 10);
					strcat(buf, temp);
					strcat(buf, " и №");
					_itoa_s(j, temp, 10);
					strcat(buf, temp);
					strcat(buf, "\n\tПервый шар:\n\t\t x = ");
					_itoa_s(balls[i]._x + balls[i]._radius, temp, 10);
					strcat(buf, temp);
					strcat(buf, "\n");
					strcat(buf, "\t\t y = ");
					_itoa_s(balls[i]._y + balls[i]._radius, temp, 10);
					strcat(buf, temp);
					strcat(buf, "\n\t\t Speed0(Ox) = ");
					_itoa_s(0, temp, 10);
					strcat(buf, temp);
					strcat(buf, "\t\t Speed0(Oy) = ");
					_itoa_s(0, temp, 10);
					strcat(buf, temp);
					strcat(buf, "\n\t\t Speed1(Ox) = ");
					_itoa_s(balls[i]._speedX, temp, 10);
					strcat(buf, temp);
					strcat(buf, "\t\t Speed1(Oy) = ");
					_itoa_s(balls[i]._speedY, temp, 10);
					strcat(buf, temp);
					strcat(buf, "\n\t\t Масса = ");
					_itoa_s(balls[i]._weight, temp, 10);
					strcat(buf, temp);

					strcat(buf, "\n\tВторой шар:\n\t\t x = ");
					_itoa_s(balls[j]._x + balls[j]._radius, temp, 10);
					strcat(buf, temp);
					strcat(buf, "\t\t y = ");
					_itoa_s(balls[j]._y + balls[j]._radius, temp, 10);
					strcat(buf, temp);
					strcat(buf, "\n\t\t Speed0(Ox) = ");
					_itoa_s(0, temp, 10);
					strcat(buf, temp);
					strcat(buf, "\t\t Speed0(Oy) = ");
					_itoa_s(0, temp, 10);
					strcat(buf, temp);
					strcat(buf, "\n\t\t Speed1(Ox) = ");
					_itoa_s(balls[j]._speedX, temp, 10);
					strcat(buf, temp);
					strcat(buf, "\t\t Speed1(Oy) = ");
					_itoa_s(balls[j]._speedY, temp, 10);
					strcat(buf, temp);
					strcat(buf, "\n\t\t Масса = ");
					_itoa_s(balls[j]._weight, temp, 10);
					strcat(buf, temp);
					strcat(buf, "\n");
					WriteFile(hFile, buf, sizeof(buf), NULL, NULL);
					//logF << "Столкновение шаров №" << i << " и №" << j<< std::endl;
				}


			}
		}
	}
};

