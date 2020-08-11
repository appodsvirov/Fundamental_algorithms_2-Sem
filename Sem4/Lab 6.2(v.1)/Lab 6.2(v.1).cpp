// Lab 6.2(v.1).cpp : Определяет точку входа для приложения.
#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"
#include "Lab 6.2(v.1).h"
#include "Figure.cpp"
#include <iostream>
#include <CommCtrl.h>
#define MAX_LOADSTRING 100


HBRUSH Brush;
HPEN hPen;
int timerId;
int x, y, width, height;
int nextImage = 5;
RECT windowRect;
int horSize, verSize;

Figure figure;

horDirections hor;
verDirections ver;


// StatusBar;

HWND hStatusWindow;
HWND StatusBorder, StatusColor, StatusBColor, StatusType, StatusFType;
HWND STextBorder, STextColor, STextBColor, STextType, STextFType;
HWND SColorR, SColorG, SColorB;
HWND SBColorR, SBColorG, SBColorB;
int StatusTimerId;




// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

WCHAR szChildWindowClass[MAX_LOADSTRING];
// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	ChildProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


//Дочернее окно изменения цвета
HINSTANCE ChhInst ;

HBRUSH ChBrush;
HWND MainStatic1, MainStatic2;
HWND Static_R1, Static_R2;
HWND Static_G1, Static_G2;
HWND Static_B1, Static_B2;
HWND Edit_R1, Edit_R2;
HWND Edit_G1, Edit_G2;
HWND Edit_B1, Edit_B2;
HWND Button1, Button2;
const int INPUT_BUFFER_SIZE = 32;
char input_bufferR[INPUT_BUFFER_SIZE];
char input_bufferG[INPUT_BUFFER_SIZE];
char input_bufferB[INPUT_BUFFER_SIZE];

char* temp = new char(10);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB62V1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB62V1));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}




ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB62V1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB62V1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; 

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDM_CGE_COLOR:
		{
			WNDCLASS w;
			memset(&w, 0, sizeof(WNDCLASS));
			w.style = CS_HREDRAW | CS_VREDRAW;
			w.lpfnWndProc = ChildProc;
			w.hInstance = ChhInst;
			w.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			w.lpszClassName = L"ChildWClass";
			w.lpszMenuName = MAKEINTRESOURCEW(IDC_CHILDMENU);
			w.hCursor = LoadCursor(NULL, IDC_CROSS);
			RegisterClass(&w);
			HWND child;
			child = CreateWindowEx(0, L"ChildWClass", (LPCTSTR)NULL,
				WS_OVERLAPPEDWINDOW | WS_BORDER | WS_VISIBLE, 850, 100,
				400, 350, hWnd, NULL, ChhInst, NULL);
			ShowWindow(child, SW_NORMAL);
			UpdateWindow(child);
		}
		break;
		case IDM_TESTING_ON:
			figure.SetTesting(TESTING_ON);
			break;
		case IDM_TESTING_OFF:
			figure.SetTesting(TESTING_OFF);
			break;
		case IDM_BDIAGONAL:
			figure.SetTypeFill(HS_BDIAGONAL);
			break;
		case IDM_CROSS:
			figure.SetTypeFill(HS_CROSS);
			break;
		case IDM_DIAGCROSS:
			figure.SetTypeFill(HS_DIAGCROSS);
			break;
		case IDM_FDIAGONAL:
			figure.SetTypeFill(HS_FDIAGONAL);
			break;
		case IDM_HORIZONTAL:
			figure.SetTypeFill(HS_HORIZONTAL);
			break;
		case IDM_VERTICAL:
			figure.SetTypeFill(HS_VERTICAL);
			break;
		case IDM_USUALLY:
			figure.SetTypeFill(USUALLY);
			break;
		case IDM_BROWN_ON:
			figure.SetBrown(BROWN_ON);
			break;
		case IDM_BROWN_OFF:
			figure.SetBrown(BROWN_OFF);
			break;
		case IDM_SOLD:
			figure.SetBorder(PS_SOLID);
			break;
		case IDM_DASH:
			figure.SetBorder(PS_DASH);
			break;
		case IDM_DOT:
			figure.SetBorder(PS_DOT);
			break;
		case IDM_DASHDOT:
			figure.SetBorder(PS_DASHDOT);
			break;
		case IDM_DASHDOTDOT:
			figure.SetBorder(PS_DASHDOTDOT);
			break;
		case IDM_NULL:
			figure.SetBorder(PS_NULL);
			break;
		case IDM_INSIDEFRAME:
			figure.SetBorder(PS_INSIDEFRAME);
			break;
		case IDM_SPEED0:
			figure.SetSpeed(SPEED0);
			break;
		case IDM_SPEED1:
			figure.SetSpeed(SPEED1);
			break;
		case IDM_SPEED2:
			figure.SetSpeed(SPEED2);
			break;
		case IDM_SPEED3:
			figure.SetSpeed(SPEED3);
			break;
		case IDM_CIRCL:
			figure.SetState(SCIRCL);
			break;
		case IDM_TRIANGLE:
			figure.SetState(STRIANGLE);
			break;
		case IDM_RHOMBUS:
			figure.SetState(SRHOMBUS);
			break;
		case IDM_PENTAGON:
			figure.SetState(SPENTAGON);
			break;

		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_CREATE:
	{
		timerId = SetTimer(hWnd, MOVING_TIMER_ID, 10, NULL);
		StatusTimerId = SetTimer(hWnd, MOVING_STATUS_TIMER_ID, 2000, NULL);

		hor = right;
		ver = down;
		GetClientRect(hWnd, &windowRect);
		width = windowRect.right - windowRect.left;
		height = windowRect.bottom - windowRect.top;

		figure.SetBorder(0);
		figure.SetSpeed(SPEED1);
		figure.SetOrientation(0, 0, 140, 140);
		figure.SetState(STRIANGLE);

		//строка состояния
		hStatusWindow = CreateWindow(STATUSCLASSNAME, L"",
			WS_CHILD | WS_VISIBLE  | SBARS_SIZEGRIP | CCS_BOTTOM,
			0, 0, 0, 0, hWnd, NULL, NULL, NULL);

		STextType = CreateWindow(L"STATIC", L"Фигура:", WS_CHILD | WS_VISIBLE,
			0, 3, 55, 20, hStatusWindow, NULL, NULL, NULL);
		StatusType = CreateWindow(L"STATIC", L"", WS_CHILD | WS_VISIBLE| WS_BORDER,
			60, 3, 95, 20, hStatusWindow, NULL, NULL, NULL); 
		STextColor = CreateWindow(L"STATIC", L"Заливка RGB: ", WS_CHILD | WS_VISIBLE,
			160, 3, 100, 20, hStatusWindow, NULL, NULL, NULL);
		SColorR = CreateWindow(L"STATIC", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
			260, 3, 30, 20, hStatusWindow, NULL, NULL, NULL);
		SColorG = CreateWindow(L"STATIC", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
			290, 3, 30, 20, hStatusWindow, NULL, NULL, NULL);
		SColorB = CreateWindow(L"STATIC", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
			320, 3, 30, 20, hStatusWindow, NULL, NULL, NULL);
		STextFType = CreateWindow(L"STATIC", L"Типы заливки:", WS_CHILD | WS_VISIBLE,
			350, 3, 100, 20, hStatusWindow, NULL, NULL, NULL);
		StatusFType = CreateWindow(L"STATIC", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
			450, 3, 100, 20, hStatusWindow, NULL, NULL, NULL);
		STextBorder = CreateWindow(L"STATIC", L"Граница:", WS_CHILD | WS_VISIBLE,
			550, 3, 60, 20, hStatusWindow, NULL, NULL, NULL);
		StatusBorder = CreateWindow(L"STATIC", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
			620, 3, 70, 20, hStatusWindow, NULL, NULL, NULL);
		STextBColor = CreateWindow(L"STATIC", L"Граница RGB: ", WS_CHILD | WS_VISIBLE,
			690, 3, 100, 20, hStatusWindow, NULL, NULL, NULL);
		SBColorR = CreateWindow(L"STATIC", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
			790, 3, 30, 20, hStatusWindow, NULL, NULL, NULL);
		SBColorG = CreateWindow(L"STATIC", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
			820, 3, 30, 20, hStatusWindow, NULL, NULL, NULL);
		SBColorB = CreateWindow(L"STATIC", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
			850, 3, 30, 20, hStatusWindow, NULL, NULL, NULL);


	}
	break;
	case WM_TIMER:
	{
		if (wParam == StatusTimerId) {
			SetWindowTextA(SColorR, _itoa(GetRValue(figure.GetColor()), temp, 10));
			SetWindowTextA(SColorG, _itoa(GetGValue(figure.GetColor()), temp, 10));
			SetWindowTextA(SColorB, _itoa(GetBValue(figure.GetColor()), temp, 10));
			SetWindowTextA(SBColorR, _itoa(GetRValue(figure.GetBColor()), temp, 10));
			SetWindowTextA(SBColorG, _itoa(GetGValue(figure.GetBColor()), temp, 10));
			SetWindowTextA(SBColorB, _itoa(GetBValue(figure.GetBColor()), temp, 10));
			SetWindowTextA(StatusBorder, figure.GetBorder());
			SetWindowTextA(StatusType, figure.GetState());
			SetWindowTextA(StatusFType, figure.GetTypeFill());
		}
		if (wParam == timerId)
		{
			figure.Tick(width, height, hor, ver);
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		//hPen = CreatePen(PS_DOT, 5, figure.GetColor()); //Создаётся объект
		//Brush = CreateHatchBrush(NULL, figure.GetColor());
		figure.NewImage(hdc, Brush, hPen);
		//ValidateRect(hWnd, NULL);

		//MoveToEx(hdc, 0, 0, NULL);
		//LineTo(hdc, windowRect.right, 0);
		//LineTo(hdc, windowRect.right, windowRect.bottom);
		//LineTo(hdc, width, 0);
		//LineTo(hdc, width, height);
		//LineTo(hdc, 0, height);
		//LineTo(hdc, 0, 0);
		//LineTo(hdc, windowRect.left, 0);

		//SelectObject(hdc, Brush);
		//Ellipse(hdc, 500, 15, 550, 75);
		//4DeleteObject(Brush);

		EndPaint(hWnd, &ps);


	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
	}
}
LRESULT CALLBACK ChildProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lparam)
{
	switch (Message)
	{
	case WM_CREATE:
	{
		MainStatic1 = CreateWindow(L"STATIC", L"\t\tЗаливка фигуры", WS_CHILD | WS_VISIBLE,
			0, 0, 400, 20, hWnd, NULL, NULL, NULL);


		Static_R1 = CreateWindow(L"STATIC", L"Красный:",
			WS_CHILD | WS_VISIBLE,
			10, 30, 100, 20, hWnd, NULL, NULL, NULL);
		Edit_R1 = CreateWindow(L"EDIT", L"255", WS_BORDER | WS_CHILD | WS_VISIBLE,
				110, 30, 100, 20, hWnd, NULL, NULL, NULL);

		Static_G1 = CreateWindow(L"STATIC", L"Зеленый:",
			WS_CHILD | WS_VISIBLE,
			10, 55, 100, 20, hWnd, NULL, NULL, NULL);
		Edit_G1 = CreateWindow(L"EDIT", L"255", WS_BORDER | WS_CHILD | WS_VISIBLE,
			110, 55, 100, 20, hWnd, NULL, NULL, NULL);

		Static_B1 = CreateWindow(L"STATIC", L"Синий: ",
			WS_CHILD | WS_VISIBLE,
			10, 80, 100, 20, hWnd, NULL, NULL, NULL);
		Edit_B1 = CreateWindow(L"EDIT", L"0", WS_BORDER | WS_CHILD | WS_VISIBLE,
			110, 80, 100, 20, hWnd, NULL, NULL, NULL);


		Button1 = CreateWindow(L"BUTTON", L"Применить", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			240, 30, 130, 70, hWnd, (HMENU)IDM_APPLY1, NULL, NULL);
		////////////////////////////////////////////
		MainStatic2 = CreateWindow(L"STATIC", L"\t\tЦвет границы", WS_CHILD | WS_VISIBLE,
			0, 145, 400, 20, hWnd, NULL, NULL, NULL);


		Static_R2 = CreateWindow(L"STATIC", L"Красный:",
			WS_CHILD | WS_VISIBLE,
			10, 175, 100, 20, hWnd, NULL, NULL, NULL);
		Edit_R2 = CreateWindow(L"EDIT", L"255", WS_BORDER | WS_CHILD | WS_VISIBLE,
			110, 175, 100, 20, hWnd, NULL, NULL, NULL);

		Static_G2 = CreateWindow(L"STATIC", L"Зеленый:",
			WS_CHILD | WS_VISIBLE,
			10, 200, 100, 20, hWnd, NULL, NULL, NULL);
		Edit_G2 = CreateWindow(L"EDIT", L"0", WS_BORDER | WS_CHILD | WS_VISIBLE,
			110, 200, 100, 20, hWnd, NULL, NULL, NULL);

		Static_B2 = CreateWindow(L"STATIC", L"Синий: ",
			WS_CHILD | WS_VISIBLE,
			10, 225, 100, 20, hWnd, NULL, NULL, NULL);
		Edit_B2 = CreateWindow(L"EDIT", L"255", WS_BORDER | WS_CHILD | WS_VISIBLE,
			110, 225, 100, 20, hWnd, NULL, NULL, NULL);

		Button2 = CreateWindow(L"BUTTON", L"Применить", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			240, 175, 130, 70, hWnd, (HMENU)IDM_APPLY2, NULL, NULL);
	}
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDM_APPLY1:
		{
			GetWindowTextA(Edit_R1, input_bufferR, INPUT_BUFFER_SIZE);
			GetWindowTextA(Edit_G1, input_bufferG, INPUT_BUFFER_SIZE);
			GetWindowTextA(Edit_B1, input_bufferB, INPUT_BUFFER_SIZE);


			std::string regular = "\\d{1, 3}";
			boost::smatch Result;

			if (!boost::regex_match(std::string(input_bufferR), Result, boost::regex(regular)) ||
				!boost::regex_match(std::string(input_bufferG), Result, boost::regex(regular)) ||
				!boost::regex_match(std::string(input_bufferB), Result, boost::regex(regular)) )
			{
				::MessageBox(hWnd, L"Число должно быть целое, положительное и меньше 256",
					L"ERROOOOR!", MB_OK | MB_ICONWARNING);
				break;
			}
			else if (atoi(input_bufferR) > 255 ||
				atoi(input_bufferG) > 255 || atoi(input_bufferB) > 255) {
				::MessageBox(hWnd, L"Число должно быть целое, положительное и меньше 256",
					L"ERROOOOR!", MB_OK | MB_ICONWARNING);
				break;
			}
			else
				figure.SetColor(RGB(atoi(input_bufferR),
					atoi(input_bufferG), atoi(input_bufferB)));
		}
		break;
		case IDM_APPLY2:
		{
			GetWindowTextA(Edit_R2, input_bufferR, INPUT_BUFFER_SIZE);
			GetWindowTextA(Edit_G2, input_bufferG, INPUT_BUFFER_SIZE);
			GetWindowTextA(Edit_B2, input_bufferB, INPUT_BUFFER_SIZE);

			std::string regular = "\\d{1, 3}";
			boost::smatch Result;

			if (!boost::regex_match(std::string(input_bufferR), Result, boost::regex(regular)) ||
				!boost::regex_match(std::string(input_bufferG), Result, boost::regex(regular)) ||
				!boost::regex_match(std::string(input_bufferB), Result, boost::regex(regular)))
			{
				::MessageBox(hWnd, L"Число должно быть целое, положительное и меньше 256",
					L"ERROOOOR!", MB_OK | MB_ICONWARNING);
				break;
			}
			else if (atoi(input_bufferR) > 255 ||
				atoi(input_bufferG) > 255 || atoi(input_bufferB) > 255) {
				::MessageBox(hWnd, L"Число должно быть целое, положительное и меньше 256",
					L"ERROOOOR!", MB_OK | MB_ICONWARNING);
				break;
			}
			else
				figure.SetColorBorder(RGB(atoi(input_bufferR),
					atoi(input_bufferG), atoi(input_bufferB)));
		}
		break;
		}
	}
	break;
	case WM_PAINT: 
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		

		ChBrush = CreateSolidBrush(RGB(255, 0, 0));
		SelectObject(hdc, ChBrush);
		Ellipse(hdc, 215, 30, 235, 50);
		Ellipse(hdc, 215, 175, 235, 195);
		DeleteObject(ChBrush);


		ChBrush = CreateSolidBrush(RGB(0, 255, 0));
		SelectObject(hdc, ChBrush);
		Ellipse(hdc, 215, 55, 235, 75);
		Ellipse(hdc, 215, 200, 235, 220);
		DeleteObject(ChBrush);

		ChBrush = CreateSolidBrush(RGB(0, 0, 255));
		SelectObject(hdc, ChBrush);
		Ellipse(hdc, 215, 80, 235, 100);
		Ellipse(hdc, 215, 225, 235, 245);
		DeleteObject(ChBrush);

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		return 0;

	default:
		break;
	}
	return DefWindowProc(hWnd, Message, wParam, lparam);
}


// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
