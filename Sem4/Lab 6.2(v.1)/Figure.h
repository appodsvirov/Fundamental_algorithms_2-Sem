#pragma once
#include "framework.h"
const int SCIRCL = 1001;
const int SRHOMBUS = 1002;
const int STRIANGLE = 1003;
const int SPENTAGON = 1004;

const int BROWN_ON = 1100;
const int BROWN_OFF = 1101;
const int TESTING_ON = 1102;
const int TESTING_OFF = 1103;

const int SPEED0 = 0;
const int SPEED1 = 1;
const int SPEED2 = 3;
const int SPEED3 = 6;

const int BSOLD = 1006;
const int BDASH = 1007;
const int BDOT = 1008;
const int BDASHDOT = 1009;
const int BDASHDOTDOT = 1010;
const int BNULL = 1011;
const int BNSIDEFRAME = 1012;


const int USUALLY = 6;

enum horDirections
{
	left, right
};

enum verDirections
{
	up, down
};

class Figure
{
private:
	int _state;
	COLORREF _color;
	int _fill_type;
	int _border;
	COLORREF _colorBorder;
	int _speed;

	int _x;
	int _y;
	int _width;
	int _height;

	bool _BrownianFigure;
	bool _Testing;
	int _TimerLocal1;
	int _Rand1;
	int _TimerLocal2;
	int _Rand2;
public:
	~Figure() {

	}

	Figure (int _state, COLORREF _color,int _fill_type, int _border, COLORREF _colorBorder, int _speed,
		int _x, int _y, int _width, int _height, bool _BrownianFigure,
		bool _Testing)
		: _state{ _state }, _color{ _color }, _fill_type{_fill_type}, _border{ _border },
		_speed{ _speed } , _x{ _x }, _y{ _y }, _width{ _width }, _height{ _height }, 
		_BrownianFigure{ _BrownianFigure }, _Testing{ _Testing },
		_TimerLocal1{ 0 }, _Rand1{ 0 }, _TimerLocal2{ 0 }, _Rand2{ 0 } {}

	Figure()
		: Figure(SCIRCL, RGB(255, 255, 0), USUALLY, PS_DOT,
			0, SPEED0, 300, 200, 100, 100, FALSE, TRUE) {}

	void NewImage(HDC hdc, HBRUSH brush , HPEN pen)
	{

		pen = CreatePen(_border, 1, _colorBorder);
		if (_fill_type == USUALLY)
			brush = CreateSolidBrush(_color);
		else brush = CreateHatchBrush(_fill_type, _color);
		SelectObject(hdc, brush);
		SelectObject(hdc, pen);
		switch (_state)
		{
		case SCIRCL:
			Ellipse(hdc, _x, _y, _x + _width, _y + _height);
			break;
		case STRIANGLE:
		{
			POINT Arr[3];
			Arr[0].x = _x; Arr[0].y = _y + _height;
			Arr[1].x = _x + _width; Arr[1].y = _y + _height;
			Arr[2].x = _x + 0.5 * _width; Arr[2].y = _y;
			Polygon(hdc, Arr, 3);
		}
		break;
		case SRHOMBUS:
		{
			POINT Arr[4];
			Arr[0].x = _x ; Arr[0].y = _y + 0.5 * _height;
			Arr[1].x = _x + 0.5 * _width; Arr[1].y = _y + _height;
			Arr[2].x = _x + _width; Arr[2].y = _y + 0.5 * _height;
			Arr[3].x = _x + 0.5 * _width; Arr[3].y = _y;
			Polygon(hdc, Arr, 4);
		}
		break;
		case SPENTAGON:
		{
			POINT Arr[5];
			Arr[0].x = _x + 0.2 *_width; Arr[0].y = _y + _height;
			Arr[1].x = _x + 0.8 * _width; Arr[1].y = _y + _height;
			Arr[2].x = _x + _width; Arr[2].y = _y + 0.4 * _height;
			Arr[3].x = _x + 0.5 * _width; Arr[3].y = _y;
			Arr[4].x = _x ; Arr[4].y = _y + 0.4 * _height;
			Polygon(hdc, Arr, 5);
		}
		break;
		default:
			break;
		}
		DeleteObject(brush);
		DeleteObject(pen);
	}

	void SetBrown(int Brown) {
		if (Brown == BROWN_ON)
			_BrownianFigure = TRUE;
		if (Brown == BROWN_OFF)
			_BrownianFigure = FALSE;
	}

	void SetTesting(int Test) {
		if (Test == TESTING_ON)
			_Testing = TRUE;
		if (Test == TESTING_OFF)
			_Testing = FALSE;
	}


	void SetOrientation(int x, int y, int weight, int height) 
	{
		_x = x;
		_y = y;
		_width = weight;
		_height = height;
	}

	void SetState(int state)
	{
		_state = state ;
	}

	const char* GetState() 
	{
		switch (_state)
		{
		case SCIRCL:
			return "Круг";
		case STRIANGLE:
			return "Треугольник";
		case SRHOMBUS:
			return "Ромб";
		case SPENTAGON:
			return "Пятиугольник";
		default:
			break;
		}
	}

	void SetSpeed(int speed) {
		_speed = speed;
	}

	int GetSpeed() 
	{
		return _speed;
	}

	void SetBorder(int border)
	{
		_border = border;
	}

	const char* GetBorder() 
	{
		switch (_border)
		{
		case PS_SOLID:
			return "Сплошная";
		case PS_DASH:
			return "- - - -";
		case PS_DOT:
			return ". . . .";
		case PS_DASHDOT:
			return ". - . -";
		case PS_DASHDOTDOT:
			return "- . . -";
		case PS_NULL:
			return "Нет";
		case PS_INSIDEFRAME:
			return "Обводка";
		default:
			break;
		}
	}

	void SetTypeFill(int Type) {
		_fill_type = Type;
	}

	const char* GetTypeFill() {
		switch (_fill_type)
		{
		case USUALLY:
			return "Обычный";
		case HS_BDIAGONAL:
			return "////////////////////";
		case HS_CROSS:
			return "###########";
		case HS_DIAGCROSS:
			return "xxxxxxxxxxx";
		case HS_FDIAGONAL:
			return "\\ \\ \\ \\ \\ \\ \\ \\ \\ \\ \\ \\ \\ \\ \\ \\";
		case HS_HORIZONTAL:
			return "==========";
		case HS_VERTICAL:
			return "| | | | | | |";

		default:
			break;
		}
	}

	COLORREF GetColor()
	{
		return this->_color;
	}

	void SetColor(COLORREF color)
	{
		_color = color;
	}

	void SetColorBorder(COLORREF color) {
		_colorBorder = color;
	}

	COLORREF GetBColor()
	{
		return this->_colorBorder;
	}

	void BrownTick(int WndWidth, int WndHeight,
		horDirections& hor, verDirections& ver) 
	{
		_TimerLocal1 += 1;

		if (_TimerLocal1 >= _Rand1) {
			_Rand1 = rand() % 100 + 50;
			_TimerLocal1 = 0 ;
			int temp = rand() % 4 ;
			if (temp == 0)
				hor == right ? hor = left : hor = right;
			else if (temp == 1)
				ver == up ? ver = up : ver = down;
			else if (temp == 2) 
			{
				hor == right ? hor = left : hor = right;
				ver == up ? ver = up : ver = down;
			}
		}
		
		if (hor == right)
		{
			_x += (2 + _Rand1 / 100) * _speed;
			if (_x + _width >= WndWidth)
			{
				_x = WndWidth - _width;
				hor = left;
			}
		}
		else if (hor == left)
		{
			_x -= (3 + _Rand1 / 100) * _speed - 1;
			if (_x <= 0)
			{
				_x = 0;
				hor = right;
			}
		}


		////////////////
		if (ver == up)
		{
			_y -= (1 + _Rand1 / 100) *_speed - 1;
			if (_y <= 0)
			{
				_y = 0;
				ver = down;
			}
		}
		else if (ver == down)
		{
			_y += (1 + _Rand1 / 100) * _speed;
			if (_y + _height + _speed + 20 >= WndHeight)
			{
				_y = WndHeight - _height - 20;
				ver = up;
			}
		}
	}

	void Tick(int WndWidth, int WndHeight,
		horDirections &hor, verDirections &ver)
	{
		Test();
		if (_speed == SPEED0) return;
		if (_BrownianFigure) {
			BrownTick(WndWidth, WndHeight, hor, ver);
			return;
		}

		if (hor == right)
		{
			_x += 2 * _speed;
		

			if (_x + _width >= WndWidth)
			{
				_x = WndWidth - _width;
				hor = left;
			}
		}
		else if (hor == left)
		{
			_x -= 2 * _speed;
			if (_x <= 0)
			{
				_x = 0;
				hor = right;
			}
		}
		////////////////
		if (ver == up)
		{
			_y -= _speed;
			if (_y <= 0)
			{
				_y = 0;
				ver = down;
			}
		}
		else if (ver == down)
		{
			_y += _speed;
			if (_y + _height + _speed + 20 >= WndHeight)
			{
				_y = WndHeight - _height - 20;
				ver = up;
			}
		}
		//color = RGB(rand() % 256, rand() % 256, rand() % 256);
	}


	void Test() {
		if (!_Testing) return;
		_TimerLocal2++;
		if (_TimerLocal2 >= _Rand2) {
			_Rand2 = rand() % 100 + 50;
			_TimerLocal2 = 0;
			int temp = rand() % 4;
			switch (temp)
			{
			case 0:
			{
				_fill_type = rand() % (USUALLY + 1) + HS_HORIZONTAL;
				break;
			}
			case 1:
			{
				_color = RGB(rand() % 256, rand() % 256, rand() % 256);
				break;
			}
			case 2:
			{
				_border = rand() % (PS_INSIDEFRAME + 1) + PS_SOLID;
				break;
			}
			case 3: 
			{
				_colorBorder = RGB(rand() % 256, rand() % 256, rand() % 256);
			}
			break;
			default:
				break;
			}

		}
	}
};

