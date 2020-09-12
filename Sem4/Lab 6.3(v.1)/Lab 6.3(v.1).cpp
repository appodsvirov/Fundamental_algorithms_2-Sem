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
HANDLE hFile, DataFile;
// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// Рабочая область, конпки
HWND ButtonExit, ButtonOn, ButtonLoad, ButtonSaving;
HWND TextMain, Id;
HWND StaticSpX, EditSpX, StaticSpY, EditSpY;
HWND StaticWeight, EditWeight;
HWND StaticRadius, EditRadius;
HWND ButtonApply, ButtonCancel;
bool state = 1;
int setobj1 = COUNT_BALLS, setobj2 = COUNT_BALLS;

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
	srand(time(NULL));
	//logF.open("Log.txt");
	hFile = CreateFile(L"Log.txt", GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, NULL, NULL);
	//wchar_t* y = new wchar_t[8]{L"12а"};
	//char buf[30]{ "123abc" };
	//LPCVOID tmp = (LPCVOID)y;
	WriteFile(hFile, "Лог столкновений:", 18, NULL, NULL);
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
		timerId = SetTimer(hWnd, TIMER_ID, TICK_TIMER, NULL);
		hor = right;
		ver = down;

		for (int i = 0; i < COUNT_BALLS; i++) {
			hors[i] = right;
			vers[i] = down;
		}

		ButtonOn = CreateWindow(L"BUTTON", L"Остановить", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			WORKSPACE_X + WORKSPACE_DX + 25, WORKSPACE_Y, 150, 75,
			hWnd, (HMENU)(IDM_APPLY_ON), NULL, NULL);
		ButtonExit = CreateWindow(L"BUTTON", L"Выйти", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			WORKSPACE_X + WORKSPACE_DX + 25, WORKSPACE_Y + 100, 150, 75,
			hWnd, (HMENU)(IDM_APPLY_EXIT), NULL, NULL);
		ButtonLoad = CreateWindow(L"BUTTON", L"Сохранение", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			WORKSPACE_X, WORKSPACE_Y + WORKSPACE_DY + 5, 100, 25,
			hWnd, (HMENU)(IDM_LOADING), NULL, NULL);
		ButtonSaving = CreateWindow(L"BUTTON", L"Загрузка", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			WORKSPACE_X + 105, WORKSPACE_Y + WORKSPACE_DY + 5, 75, 25,
			hWnd, (HMENU)(IDM_SAVING), NULL, NULL);
		

		TextMain = CreateWindow(L"STATIC", L"Редактор шара №", WS_CHILD | WS_BORDER ,
			WORKSPACE_X + WORKSPACE_DX + 5, WORKSPACE_Y + 200, 125, 20,
			hWnd, NULL, NULL, NULL);
		Id = CreateWindow(L"STATIC", L"", WS_CHILD,
			WORKSPACE_X + WORKSPACE_DX + 131, WORKSPACE_Y + 200, 25, 20,
			hWnd, NULL, NULL, NULL);
		StaticSpX = CreateWindow(L"STATIC", L"Скорость Оx:", WS_CHILD ,
			WORKSPACE_X + WORKSPACE_DX + 25, WORKSPACE_Y + 230, 100, 20,
			hWnd, NULL, NULL, NULL);
		EditSpX = CreateWindow(L"EDIT", L"0", WS_CHILD | WS_BORDER,
			WORKSPACE_X + WORKSPACE_DX + 125, WORKSPACE_Y + 230, 45, 20,
			hWnd, NULL, NULL, NULL);
		StaticSpY = CreateWindow(L"STATIC", L"Скорость Оy:", WS_CHILD,
			WORKSPACE_X + WORKSPACE_DX + 25, WORKSPACE_Y + 250, 100, 20,
			hWnd, NULL, NULL, NULL);
		EditSpY = CreateWindow(L"EDIT", L"0", WS_CHILD | WS_BORDER,
			WORKSPACE_X + WORKSPACE_DX + 125, WORKSPACE_Y + 250, 45, 20,
			hWnd, NULL, NULL, NULL);
		StaticWeight = CreateWindow(L"STATIC", L"Масса:", WS_CHILD ,
			WORKSPACE_X + WORKSPACE_DX + 25, WORKSPACE_Y + 270, 100, 20,
			hWnd, NULL, NULL, NULL);
		EditWeight = CreateWindow(L"EDIT", L"5", WS_CHILD | WS_BORDER,
			WORKSPACE_X + WORKSPACE_DX + 125, WORKSPACE_Y + 270, 45, 20,
			hWnd, NULL, NULL, NULL);
		StaticRadius = CreateWindow(L"STATIC", L"Радиус:", WS_CHILD ,
			WORKSPACE_X + WORKSPACE_DX + 25, WORKSPACE_Y + 290, 100, 20,
			hWnd, NULL, NULL, NULL);
		EditRadius = CreateWindow(L"EDIT", L"30", WS_CHILD | WS_BORDER,
			WORKSPACE_X + WORKSPACE_DX + 125, WORKSPACE_Y + 290, 45, 20,
			hWnd, NULL, NULL, NULL);
		ButtonApply = CreateWindow(L"BUTTON", L"Применить", WS_CHILD | BS_DEFPUSHBUTTON,
			WORKSPACE_X + WORKSPACE_DX + 25, WORKSPACE_Y + 320, 150, 40,
			hWnd, (HMENU)(IDM_APPLY), NULL, NULL);
		ButtonCancel = CreateWindow(L"BUTTON", L"X", WS_CHILD | BS_DEFPUSHBUTTON,
			WORKSPACE_X + WORKSPACE_DX + 165, WORKSPACE_Y + 200, 20, 20,
			hWnd, (HMENU)(IDM_CANCEL), NULL, NULL);
		}
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
			case IDM_LOADING:
				{
				Load(objs, DataFile);
				}
				break;
			case IDM_SAVING:
			{
				Save(objs, DataFile);
			}
			break;
			case IDM_APPLY_ON:
				if (state) {
					SetWindowText(ButtonOn, L"Запустить");
					state = 0;
				}
				else
				{
					SetWindowText(ButtonOn, L"Остановить");
					state = 1; 
				}
				SetWindowLong(TextMain, GWL_STYLE, WS_CHILD);
				SetWindowLong(Id, GWL_STYLE, WS_CHILD);
				SetWindowLong(StaticSpX, GWL_STYLE, WS_CHILD);
				SetWindowLong(EditSpX, GWL_STYLE, WS_CHILD);
				SetWindowLong(StaticSpY, GWL_STYLE, WS_CHILD);
				SetWindowLong(EditSpY, GWL_STYLE, WS_CHILD);
				SetWindowLong(StaticWeight, GWL_STYLE, WS_CHILD);
				SetWindowLong(EditWeight, GWL_STYLE, WS_CHILD);
				SetWindowLong(StaticRadius, GWL_STYLE, WS_CHILD);
				SetWindowLong(EditRadius, GWL_STYLE, WS_CHILD);
				SetWindowLong(ButtonApply, GWL_STYLE, WS_CHILD);
				SetWindowLong(ButtonCancel, GWL_STYLE, WS_CHILD);
				setobj2 = COUNT_BALLS;
				for (int i = 0; i < COUNT_BALLS; i++) objs[i].setStop();
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
			case IDM_APPLY:
				{
				SetWindowLong(TextMain, GWL_STYLE, WS_CHILD);
				SetWindowLong(Id, GWL_STYLE, WS_CHILD);
				SetWindowLong(StaticSpX, GWL_STYLE, WS_CHILD);
				SetWindowLong(EditSpX, GWL_STYLE, WS_CHILD);
				SetWindowLong(StaticSpY, GWL_STYLE, WS_CHILD);
				SetWindowLong(EditSpY, GWL_STYLE, WS_CHILD);
				SetWindowLong(StaticWeight, GWL_STYLE, WS_CHILD);
				SetWindowLong(EditWeight, GWL_STYLE, WS_CHILD);
				SetWindowLong(StaticRadius, GWL_STYLE, WS_CHILD);
				SetWindowLong(EditRadius, GWL_STYLE, WS_CHILD);
				SetWindowLong(ButtonApply, GWL_STYLE, WS_CHILD);
				SetWindowLong(ButtonCancel, GWL_STYLE, WS_CHILD);
				objs[setobj2].SetСhanges(hWnd, EditSpX, EditSpY, EditWeight, EditRadius);
				setobj2 = COUNT_BALLS;
				}
				break;
			case IDM_CANCEL:
			{
				SetWindowLong(TextMain, GWL_STYLE, WS_CHILD);
				SetWindowLong(Id, GWL_STYLE, WS_CHILD);
				SetWindowLong(StaticSpX, GWL_STYLE, WS_CHILD);
				SetWindowLong(EditSpX, GWL_STYLE, WS_CHILD);
				SetWindowLong(StaticSpY, GWL_STYLE, WS_CHILD);
				SetWindowLong(EditSpY, GWL_STYLE, WS_CHILD);
				SetWindowLong(StaticWeight, GWL_STYLE, WS_CHILD);
				SetWindowLong(EditWeight, GWL_STYLE, WS_CHILD);
				SetWindowLong(StaticRadius, GWL_STYLE, WS_CHILD);
				SetWindowLong(EditRadius, GWL_STYLE, WS_CHILD);
				SetWindowLong(ButtonApply, GWL_STYLE, WS_CHILD);
				SetWindowLong(ButtonCancel, GWL_STYLE, WS_CHILD);
				setobj2 = COUNT_BALLS;
			}
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
			for (int i = 0; i < COUNT_BALLS; i++) objs[i].Tick(hors[i], vers[i]);
			Crash(hWnd, objs, hors, vers, hFile);
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;

		}
	case WM_RBUTTONDOWN:
		{
		if (state) break;
		for (int i = 0; i < COUNT_BALLS; i++)
			if (objs[i].Short(LOWORD(lParam), HIWORD(lParam)))
			{
				setobj2 = i;
				SetWindowLong(TextMain, GWL_STYLE, WS_CHILD | WS_VISIBLE | WS_BORDER);
				SetWindowLong(Id, GWL_STYLE, WS_CHILD | WS_VISIBLE | WS_BORDER);
				SetWindowLong(StaticSpX, GWL_STYLE, WS_CHILD | WS_VISIBLE);
				SetWindowLong(EditSpX, GWL_STYLE, WS_CHILD | WS_VISIBLE | WS_BORDER);
				SetWindowLong(StaticSpY, GWL_STYLE, WS_CHILD | WS_VISIBLE);
				SetWindowLong(EditSpY, GWL_STYLE, WS_CHILD | WS_VISIBLE | WS_BORDER);
				SetWindowLong(StaticWeight, GWL_STYLE, WS_CHILD | WS_VISIBLE);
				SetWindowLong(EditWeight, GWL_STYLE, WS_CHILD | WS_VISIBLE | WS_BORDER);
				SetWindowLong(StaticRadius, GWL_STYLE, WS_CHILD | WS_VISIBLE);
				SetWindowLong(EditRadius, GWL_STYLE, WS_CHILD | WS_VISIBLE | WS_BORDER);
				SetWindowLong(ButtonApply, GWL_STYLE, WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON);
				SetWindowLong(ButtonCancel, GWL_STYLE, WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON);

				break;
			}

		}
		break;
	case WM_RBUTTONUP:
		{
		if (state == 1 || setobj2 == COUNT_BALLS) break;
		char tmp[4];
		_itoa_s(setobj2, tmp, 10);
		SetWindowTextA(Id, tmp);
		//setobj2 = COUNT_BALLS;
		}
		break;
	case WM_LBUTTONDOWN:
		{
		for (int i = 0; i < COUNT_BALLS; i++)
			if (objs[i].Short(LOWORD(lParam), HIWORD(lParam))) {
				setobj1 = i;
				break;
			}
		}
		break;
	case WM_MOUSEMOVE:
		{
		if (state == 1 || setobj1 == COUNT_BALLS) break;
		objs[setobj1].setСoordinate(LOWORD(lParam), HIWORD(lParam));
		InvalidateRect(hWnd, NULL, TRUE);
		break;
		}
	case WM_LBUTTONUP:
		{
		setobj1 = COUNT_BALLS;
		}
		break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

			Brush = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(hdc, Brush);
			Rectangle(hdc, WORKSPACE_X, WORKSPACE_Y,
				WORKSPACE_X + WORKSPACE_DX, WORKSPACE_Y + WORKSPACE_DY);
			//Rectangle(hdc, 250, 250, 290, 290);
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
