// Lab 6.5(v.1).cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Lab 6.5(v.1).h"
#include "Object.h"
#define MAX_LOADSTRING 100

RECT windowRect;

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

HINSTANCE hRB;
HWND CButton, RButton1, RButton2, RButton3, RButton4, RButton5;
int Wheight, Wwidth;
bool RClick{}, LClick{}, Flag_Aplly{};
const wchar_t* TypeBs[]{ L"BUTTON", L"EDIT", L"STATIC", L"COMBOBOX", L"SCROLLBAR" };
int numBs{ -1 };
POINT Pos;
Object* SelectedObj{nullptr};
// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
vector<Object*> Object::List;
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB65V1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB65V1));

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



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB65V1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB65V1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

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

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
	{
		GetClientRect(hWnd, &windowRect);
		Wwidth = windowRect.right - windowRect.left;
		Wheight = windowRect.bottom - windowRect.top;
		//Object *obj = new Object(hWnd, L"BUTTON", 50, 50);

		RButton1 = CreateWindowEx(NULL, L"BUTTON", L"Button", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			Wwidth - 130, 30, 120, 50, hWnd, (HMENU)IDM_RADIO1, hRB, NULL);
		RButton2 = CreateWindowEx(NULL, L"BUTTON", L"Edit", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			Wwidth - 130, 80, 120, 50, hWnd, (HMENU)IDM_RADIO2, hRB, NULL);
		RButton3 = CreateWindowEx(NULL, L"BUTTON", L"Label", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			Wwidth - 130, 130, 120, 50, hWnd, (HMENU)IDM_RADIO3, hRB, NULL);
		RButton4 = CreateWindowEx(NULL, L"BUTTON", L"Combobox", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			Wwidth - 130, 180, 120, 50, hWnd, (HMENU)IDM_RADIO4, hRB, NULL);
		RButton5 = CreateWindowEx(NULL, L"BUTTON", L"Spinbutton", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			Wwidth - 130, 230, 120, 50, hWnd, (HMENU)IDM_RADIO5, hRB, NULL);
		CButton = CreateWindowEx(NULL, L"BUTTON", L"Cоздать", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			Wwidth - 130, 300, 120, 70, hWnd, (HMENU)IDM_BUTTON, NULL, NULL);

	}
	break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
			case IDM_BUTTON:
			{
				if (numBs == -1) MessageBox(hWnd, L"Вы ничего не выбрали :(", L"Выбор кнопки", NULL);
				else
				{
					Flag_Aplly = 1;
					MessageBox(hWnd, L"Выберите место для размещения кнопки", L"Выбор положения кнопки", NULL);
				}
			}
				break;
			case IDM_RADIO1:
				numBs = 0;
				break;
			case IDM_RADIO2:
				numBs = 1;
				break;
			case IDM_RADIO3:
				numBs = 2;
				break;
			case IDM_RADIO4:
				numBs = 3;
				break;
			case IDM_RADIO5:
				numBs = 4;
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
	case WM_MOUSEWHEEL:
	{
		SelectedObj = Object::SetObj(Pos);
		if (SelectedObj != nullptr)
		{
			if ((short)HIWORD(wParam) < 0)
				SelectedObj->SetSize(false, Wwidth - 130, Wheight);
			else 	SelectedObj->SetSize(true, Wwidth - 130, Wheight) ;
		}
		SelectedObj = nullptr;
	}
	break;
	case WM_MOUSEMOVE:
	{
		GetCursorPos(&Pos);
		ScreenToClient(hWnd, &Pos);
		if (SelectedObj != nullptr)
		{
			SelectedObj->SetOrientation(Pos.x, Pos.y, Wwidth - 130, Wheight);
		}
	}
	break;
	case WM_LBUTTONDOWN:
	{
		SelectedObj = Object::SetObj(Pos);

	}
	break;
	case WM_LBUTTONUP:
	{
		SelectedObj = nullptr;
		if (!Flag_Aplly) break;
		if (Object::Short(Pos.x, Pos.y, 100, 20, Wwidth - 130, Wheight))
			Object* tmp = new Object(hWnd, TypeBs[numBs], Pos.x, Pos.y);
		else MessageBox(hWnd, L"Кнопка выходит за допустимые границы или задевает другие кнопки", NULL, NULL);
		Flag_Aplly = 0;
	}
	break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			//Rectangle(hdc, 300, 300, 400, 400);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
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
