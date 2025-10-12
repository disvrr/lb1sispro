#include <windows.h> // підключення бібліотеки з функціями API
#include "resource.h"
// Глобальні змінні:
HINSTANCE hInst; 	//Дескриптор програми	
LPCTSTR szWindowClass = "QWERTY";
LPCTSTR szTitle = "Ivaknenko Diana";

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
	wcex.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;  		//стиль вікна
	wcex.lpfnWndProc = (WNDPROC)WndProc; 		//віконна процедура
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance; 			//дескриптор програми
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		//визначення іконки
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
		WS_CAPTION | WS_BORDER | WS_HSCROLL,			// стиль вікна
		10, 			// положення по Х	
		30,			// положення по Y	
		400, 			// розмір по Х
		300, 			// розмір по Y
		NULL, 					// дескриптор батьківського вікна	
		NULL, 					// дескриптор меню вікна
		hInstance, 				// дескриптор програми
		NULL); 				// параметри створення.

	if (!hWnd) 	//Якщо вікно не творилось, функція повертає FALSE
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow); 		//Показати вікно
	UpdateWindow(hWnd); 				//Оновити вікно
	return TRUE;
}

// FUNCTION: WndProc (HWND, unsigned, WORD, LONG)
// Віконна процедура. Приймає і обробляє всі повідомлення, що приходять в додаток


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt;

	switch (message)
	{
	case WM_CREATE: 				//Повідомлення приходить при створенні вікна
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_CHANGE_CURSOR:
			SetClassLongPtr(hWnd, GCLP_HCURSOR, (LONG_PTR)LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR1)));
		
		break;
		case ID_CHANGE_ICON40004:
			SetClassLongPtr(hWnd, GCLP_HICON, (LONG_PTR)LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)));
		break;
		}
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

