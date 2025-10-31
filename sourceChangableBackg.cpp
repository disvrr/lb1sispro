#include <windows.h> // підключення бібліотеки з функціями API
#include "resource.h"
#include <shellapi.h>

// Глобальні змінні:
HINSTANCE hInst; 	//Дескриптор програми	
LPCTSTR szWindowClass = "QWERTY";
LPCTSTR szTitle = "Ivaknenko Diana";
NOTIFYICONDATA tray;
HWND g_hMainWnd;

// Попередній опис функцій

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
// Основна програма 
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
	int nCmdShow)
{
	MSG msg;

	// Реєстрація класу вікна 
	MyRegisterClass(hInstance);

	// Створення вікна програми
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	// Цикл обробки повідомлень
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_DROPSHADOW;//стиль вікна
	wcex.lpfnWndProc = (WNDPROC)WndProc; 		//віконна процедура
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance; 			//дескриптор програми
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION); 		//визначення іконки
	wcex.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW); 	//визначення курсору
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //установка фону
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);				//визначення меню
	wcex.lpszClassName = szWindowClass; 		//ім’я класу
	wcex.hIconSm = NULL;
	return RegisterClassEx(&wcex); 			//реєстрація класу вікна
}

// FUNCTION: InitInstance (HANDLE, int)
// Створює вікно програми і зберігає дескриптор програми в змінній hInst

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hInst = hInstance; //зберігає дескриптор додатка в змінній hInst
	hWnd = CreateWindow(szWindowClass, 	// ім’я класу вікна
		szTitle, 				// назва програми
		WS_SYSMENU | WS_MINIMIZEBOX | WS_CAPTION | WS_BORDER | WS_HSCROLL | WS_THICKFRAME, // стиль вікна
		10, 			// положення по Х	
		30,			// положення по Y	
		400, 			// розмір по Х
		300, 			// розмір по Y
		NULL, 					// дескриптор батьківського вікна	
		NULL, 					// дескриптор меню вікна
		hInstance, 				// дескриптор програми
		NULL); 				// параметри створення.
	g_hMainWnd = hWnd;

	if (!hWnd) 	//Якщо вікно не творилось, функція повертає FALSE
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow); 		//Показати вікно
	UpdateWindow(hWnd); 				//Оновити вікно
	return TRUE;
}

INT_PTR CALLBACK DialogProc2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case WM_INITDIALOG:  //ініціалізація функціоналу керування діалоговим вікном
			return TRUE;
		case IDOK:
			EndDialog(hDlg, IDOK);
			SendMessage(g_hMainWnd, WM_CLOSE, 0, 0);
			break;
		case IDCANCEL2:
			EndDialog(hDlg, IDCANCEL2);
			break;
		}
		break;
	case WM_CLOSE: 
		EndDialog(hDlg, 0);
		return TRUE;
	}
	return FALSE;
}

// FUNCTION: WndProc (HWND, unsigned, WORD, LONG)
// Віконна процедура. Приймає і обробляє всі повідомлення, що приходять в додаток

INT_PTR CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case WM_INITDIALOG:  //ініціалізація функціоналу керування діалоговим вікном
			return TRUE;
		case IDOK:
			EndDialog(hDlg, IDOK);
			break;
		case IDCLOSE:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hDlg, DialogProc2);
			break;
		case IDDETAILS:
			SetDlgItemText(hDlg, IDC_STATIC2, "КІУКІ-24-1");
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		return TRUE;
	}
	return FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt;

	switch (message)
	{
	case WM_CREATE: 		
	{
		tray.cbSize = sizeof(NOTIFYICONDATA);
		tray.hWnd = hWnd;
		tray.uID = 1;
		tray.uFlags = NIF_ICON;
		tray.uCallbackMessage = NULL;
		tray.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_APPLICATION));

		Shell_NotifyIcon(NIM_ADD, &tray);
		break;
	}
	case WM_COMMAND:
	{
		HICON hIcon = NULL;

		switch (LOWORD(wParam))
		{
		case ID_CHANGE_ICON1:
			hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));
			break;
		case ID_CHANGE_ICON2:
			hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON2));
			break;
		case ID_CHANGE_ICON3:
			hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON3));
			break;
		case ID_ABOUT_PROGRAM:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, DialogProc);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}

		if (hIcon)
		{
			SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
			SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);

			tray.hIcon = hIcon;
			Shell_NotifyIcon(NIM_MODIFY, &tray);
		}
	}
	break;
	case WM_SIZE:
		// Користувач змінив розмір вікна
		InvalidateRect(hWnd, NULL, TRUE); // Оновлюємо все вікно
		return 0;
	case WM_LBUTTONDBLCLK:
		//Подвійне натискання лівої кнопки миші 
		MessageBox(hWnd, "TEXT", "CAPTION", MB_OK);
		break;
	case WM_PAINT: 				//Перемалювати вікно
		hdc = BeginPaint(hWnd, &ps); 	//Почати графічний вивід	
		GetClientRect(hWnd, &rt); 		//Область вікна для малювання
		DrawText(hdc, "Привіт, світ!", -1, &rt, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hWnd, &ps); 		//Закінчити графічний вивід	
		break;

	case WM_DESTROY: 				//Завершення роботи
		PostQuitMessage(0);
		break;
	default:
		//Обробка повідомлень, які не оброблені користувачем
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

