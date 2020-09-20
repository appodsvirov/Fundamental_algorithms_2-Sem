#include "framework.h"
#include "Lab 6.1(v.2).h"


using namespace boost::posix_time;
using namespace boost::gregorian;



// Global Variables:
const int INPUT_BUFFER_SIZE = 32;

HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
char input_buffer[INPUT_BUFFER_SIZE];

int update_timer;
int interval, curr_interval;
int Day, Month, Years, Hour, Minute, Second, Millisecond;

date G_Date_and_Time;
ptime G_Timer;

HWND Static_DaT, Static_T, Clock ;
HWND Edit_DAT, Edit_T, B_Apply;


ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_LAB61V2, szWindowClass, MAX_LOADSTRING);

	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB61V2));

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB61V2));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB61V2);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;  
	HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
		return FALSE;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		
		// 1) надпись над первым редактируемым полем - вводом даты и времени 
		Static_DaT = CreateWindow(L"STATIC", L"Дата и время dd.mm.yyyy h:m:s:ms",
			WS_CHILD | WS_VISIBLE,
			STATIC_DAT_X, STATIC_DAT_Y, STATIC_DAT_W, STATIC_T_H, hWnd, NULL, NULL, NULL);

		//2) редактируемое поле - ввод даты и времени
		Edit_DAT = CreateWindow(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
			EDIT_DAT_X, EDIT_DAT_Y, EDIT_DAT_W, EDIT_DAT_H, hWnd, NULL, NULL, NULL);

		// 3) надпись над вторым редактируемым полем - вводом таймера 
		Static_T = CreateWindow(L"STATIC", L"Интервал (ms):",
			WS_CHILD | WS_VISIBLE,
			STATIC_T_X, STATIC_T_Y, STATIC_T_W, STATIC_T_H, hWnd, NULL, NULL, NULL);

		// 4) редактируемое поле - ввод таймера
		Edit_T = CreateWindow(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
			EDIT_T_X, EDIT_T_Y, EDIT_T_W, EDIT_T_H, hWnd, NULL, NULL, NULL);

		// 5) конпка Принять
		B_Apply = CreateWindow(
			L"BUTTON",
			L"Принять",
			WS_DLGFRAME | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			BUTTON_X, BUTTON_Y, BUTTON_W, BUTTON_H, hWnd, (HMENU)(IDM_APPLY), NULL, NULL);

		// 6) Часы
		Clock  = CreateWindow(L"STATIC", L"",
			WS_CHILD | WS_VISIBLE,
			CLOCK_X, CLOCK_Y, CLOCK_W, CLOCK_H,
			hWnd, NULL, NULL, NULL);

		//  Положение окна
		SetWindowPos(hWnd, NULL, WINDOW_X, WINDOW_Y, WINDOW_W, WINDOW_H, SWP_NOREPOSITION);

	case WM_COMMAND:
	{
		switch (wParam)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);

			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);

			break;
		case IDM_SETDATETIME://"Установить дату и время"
		{
			SYSTEMTIME curTime;
			GetLocalTime(&curTime);
			int milli = curTime.wMilliseconds;

			ptime now = second_clock::local_time();

			int Day, Month, Years;

			std::wstringstream wss;
			date curr_dt = now.date();
			time_duration curr_t = now.time_of_day();

			Day = curr_dt.day();
			Month = curr_dt.month();
			Years = curr_dt.year();

			std::string time = to_simple_string(curr_t);

			wss << (Day < 10 ? "0" : "") << Day << "." << (Month < 10 ? "0" : "") << Month << "." << Years << " " << time.c_str() << ":" << std::to_string(milli).c_str();

			SetWindowText(Edit_DAT, wss.str().c_str());
		}

		break;

		case IDM_DEFAULT_TIMER:// "Установить таймер в 1 секунду"
		{
			SetWindowText(Edit_T, L"1000");
			break;
		}

		case IDM_APPLY:
		{
			// Провекрка корректности 1 поля
			GetWindowTextA(Edit_DAT, input_buffer, INPUT_BUFFER_SIZE);
			std::string str = input_buffer;
			std::wstringstream wss;

			std::string regular = "\\d{1, 2}[.](\\d{1, 2})[.](\\d{4})(\\s+)(\\d{1, 2}):(\\d{1, 2}):(\\d{1, 2}):(\\d{1, 3})";
			boost::smatch Result;

			if (!boost::regex_match(std::string(input_buffer), Result, boost::regex(regular)))
			{
				::MessageBox(hWnd, L"Некорректные дата и время.", L"ERROOOOR!", MB_OK | MB_ICONWARNING);
				break;
			}

			std::vector<std::string> parts, date_components, time_components;

			try
			{
				boost::split(parts, str, boost::is_any_of(" "));

				boost::split(date_components, parts[0], boost::is_any_of("."));

				Day = std::stoi(date_components[0]);
				Month = std::stoi(date_components[1]);
				Years = std::stoi(date_components[2]);

				boost::split(time_components, parts[1], boost::is_any_of(":"));

				Hour = std::stoi(time_components[0]);
				Minute = std::stoi(time_components[1]);
				Second = std::stoi(time_components[2]);
				Millisecond = std::stoi(time_components[3]);

			}
			catch (const std::invalid_argument& e)
			{
				::MessageBox(hWnd, L"Некорректные дата и время.", L"ERROOOOR!", MB_OK | MB_ICONWARNING);

				break;
			}

			try
			{
				date init_d(Years, Month, Day);
				ptime t(init_d, hours(Hour) + minutes(Minute) + seconds(Second) + millisec(Millisecond));

				G_Date_and_Time = init_d;
				G_Timer = t;
			}
			catch (const std::exception& e)
			{
				wss << e.what();
				::MessageBox(hWnd, wss.str().c_str(), L"ERROOOOR!", MB_OK | MB_ICONWARNING);

				break;
			}

			wss.clear();

			//------------------------------
			// Проверка корркектности 2 поля
			GetWindowTextA(Edit_T, input_buffer, INPUT_BUFFER_SIZE);

			str = input_buffer;

			regular = "\\d+";
			if (!boost::regex_match(std::string(input_buffer), Result, boost::regex(regular)))
			{
				::MessageBox(hWnd, L"Таймер - это натуральное число", L"ERROOOOR!", MB_OK | MB_ICONWARNING);
				break;
			}

			try
			{
				interval = std::stoi(str);

				if (interval <= 0)
				{
					throw std::out_of_range("Таймер - это натуральное число");
				}
			}
			catch (const std::invalid_argument& e)
			{
				::MessageBox(hWnd, L"Таймер - это натуральное число", L"ERROOOOR!", MB_OK | MB_ICONWARNING);

				break;
			}
			catch (const std::out_of_range& e)
			{
				wss << e.what();
				::MessageBox(hWnd, wss.str().c_str(), L"ERROOOOR!", MB_OK | MB_ICONWARNING);

				break;
			}

			update_timer = SetTimer(hWnd, IDM_UPDATE_TIMER, interval, NULL);
		}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_TIMER:
		if (wParam == update_timer)
		{
			std::wstringstream wss;

			G_Timer += millisec(interval);
			date curr_dt = G_Timer.date();
			time_duration curr_t = G_Timer.time_of_day();

			Day = curr_dt.day();
			Month = curr_dt.month();
			Years = curr_dt.year();

			std::string time = to_simple_string(curr_t);
			wss << (Day < 10 ? "0" : "") << Day << "." << (Month < 10 ? "0" : "") << Month << "." << Years << " " << time.c_str();

			SetWindowText(Clock , wss.str().c_str());
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


