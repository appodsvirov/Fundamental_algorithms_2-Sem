#pragma once
#include "framework.h"
using namespace std;
class Object
{
private:
	LPCWSTR _state;
	int _x;
	int _y;
	int _dx;
	int _dy;
	static vector<Object*> List;
	HWND Wnd;
public:
	Object(HWND hWnd, LPCWSTR _state, int _x, int _y) :_state{ _state }, _x{ _x }, _y{ _y },
		_dx{120}, _dy{20}
	{

		Object::List.push_back(this);
		Wnd = CreateWindow(_state, L"Ìÿó", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_DISABLED,
			_x, _y, _dx, _dy, hWnd, NULL, NULL, NULL);
	}

	static Object* SetObj(POINT Pos)
	{
		for (int i = 0; i < List.size(); i++)
		{
			if (List[i]->_x <= Pos.x && Pos.x <= List[i]->_x + List[i]->_dx &&
				List[i]->_y <= Pos.y && Pos.y <= List[i]->_y + List[i]->_dy)
				return List[i];
		}
		return nullptr;
	}

	void SetOrientation(int x, int y, int Wwidth, int Wheight)
	{
		if (Short(_x, y, _dx, _dy, Wwidth, Wheight, this))
		{
			_y = y;
			SetWindowPos(Wnd, NULL, _x, _y, _dx, _dy, NULL);
		}

		if (Short(x, _y, _dx, _dy, Wwidth, Wheight, this))
		{
			_x = x;
			SetWindowPos(Wnd, NULL, _x, _y, _dx, _dy, NULL);
		}

	}

	void SetSize(bool side, int Wwidth, int Wheight)
	{
		if (side)
		{
			if (_dx < 300 && Short(_x, _y, _dx + 6, _dy + 1, Wwidth, Wheight, this))
				SetWindowPos(Wnd, NULL, _x, _y, _dx += 6, _dy += 1, NULL);
		}
		else
		{
			if (_dx > 60 && Short(_x, _y, _dx - 6, _dy - 1, Wwidth, Wheight, this))
				SetWindowPos(Wnd, NULL, _x, _y, _dx -= 6, _dy -= 1, NULL);
		}
	}
	static bool Short(int x, int y, int wth, int hht, int Wwidth, int Wheight, Object* obj = nullptr)
	{
		int Lleft{ x }, Lright{ x + wth }, Lbot{ y + hht }, Ltop{y};
		for (int i = 0; i < List.size(); i++)
		{	
			if (Lleft < 0 || Ltop < 0 || Lright > Wwidth || Lbot > Wheight) return false;
			if (obj != nullptr && obj == List[i]) continue;
			int Rleft{ (List[i]->_x) }, Rright{ List[i]->_x + List[i]->_dx };
			int Rbot = { List[i]->_y + List[i]->_dy }, Rtop{ List[i]->_y };
			
			if ((Lleft <= Rleft && Rleft <= Lright && (abs(max(Rbot, Lbot) - min(Rtop,Ltop)) <= abs(Lbot - Ltop + Rbot - Rtop)))||
				(Rleft <= Lleft && Lleft <= Rright && (abs(max(Rbot, Lbot) - min(Rtop,Ltop)) <= abs(Rbot - Rtop + Lbot - Ltop))))
				return false;
		}
		return true;
	}
};
