// Lab 6.3(v.1).cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Lab 6.3(v.1).h"
#include "Ball.cpp"



#define MAX_LOADSTRING 100


// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

Ball obj1;
Ball objs[COUNT_BALLS];
int timerId;
HBRUSH Brush;
horDirections hor, hors[COUNT_BALLS];
verDirections ver, vers[COUNT_BALLS];

//std::ofstream logF;
HANDLE hFile;
// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// Рабочая область, конпки
HWND WorkSpace, ButtonExit, ButtonOn;
bool state{};

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
    LoadStringW(hInstance, IDC_LAB63V1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB63V1));
	srand(time(0));
    MSG msg;
	//srand(time(0));
	//logF.open("Log.txt");
	CreateFile(L"Log.txt", GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, NULL, hFile);
	wchar_t* y = new wchar_t[8]{L"123"};
	LPCVOID tmp = (LPCVOID)y;
	WriteFile(hFile, tmp, 8, NULL, NULL);
    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

	CloseHandle(hFile);
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB63V1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB63V1);
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
		timerId = SetTimer(hWnd, TIMER_ID, 10, NULL);
		hor = right;
		ver = down;

		for (int i = 0; i < COUNT_BALLS; i++) {
			hors[i] = right;
			vers[i] = down;
		}

		ButtonOn = CreateWindow(L"BUTTON", L"Запустить", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			WORKSPACE_X + WORKSPACE_DX + 25, WORKSPACE_Y, 150, 100,
			hWnd, (HMENU)(IDM_APPLY_ON), NULL, NULL);
		ButtonExit = CreateWindow(L"BUTTON", L"Выйти", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			WORKSPACE_X + WORKSPACE_DX + 25, WORKSPACE_Y + 125, 150, 100,
			hWnd, (HMENU)(IDM_APPLY_EXIT), NULL, NULL);

		}
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
			case IDM_APPLY_ON:
				if (state) {
					SetWindowText(ButtonOn, L"Запустить");
					state = 0;
				}
				else {
					SetWindowText(ButtonOn, L"Остановить");
					state = 1; 
				}
				obj1.setR();
				break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case IDM_APPLY_EXIT:
				DestroyWindow(hWnd);
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_TIMER:
		{
		if (wParam == timerId)
		{
			obj1.Tick(hor, ver);
			LPCVOID temp = L"217\r\n", *t = &temp;
			WriteFile(hFile, t, 10, NULL, NULL);
			for (int i = 0; i < COUNT_BALLS; i++) objs[i].Tick(hors[i], vers[i]);
			Crash(objs, hors, vers, hFile);
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;

		}
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

			Brush = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(hdc, Brush);
			Rectangle(hdc, WORKSPACE_X, WORKSPACE_Y,
				WORKSPACE_X + WORKSPACE_DX, WORKSPACE_Y + WORKSPACE_DY);
			Rectangle(hdc, 250, 250, 290, 290);
			DeleteObject(Brush);

			//obj1.NewImage(hdc, Brush);
			for (int i = 0; i < COUNT_BALLS; i++) objs[i].NewImage(hdc, Brush);

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
