#include <windows.h> // ���������� �������� � ��������� API
#include "resource.h"
// �������� ����:
HINSTANCE hInst; 	//���������� ��������	
LPCTSTR szWindowClass = "QWERTY";
LPCTSTR szTitle = "Ivaknenko Diana";

// ��������� ���� �������

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
// ������� �������� 
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
	int nCmdShow)
{
	MSG msg;

	// ��������� ����� ���� 
	MyRegisterClass(hInstance);

	// ��������� ���� ��������
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	// ���� ������� ����������
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
	wcex.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;  		//����� ����
	wcex.lpfnWndProc = (WNDPROC)WndProc; 		//������ ���������
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance; 			//���������� ��������
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		//���������� ������
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW); 	//���������� �������
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //��������� ����
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);				//���������� ����
	wcex.lpszClassName = szWindowClass; 		//��� �����
	wcex.hIconSm = NULL;
	return RegisterClassEx(&wcex); 			//��������� ����� ����
}

// FUNCTION: InitInstance (HANDLE, int)
// ������� ���� �������� � ������ ���������� �������� � ����� hInst

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hInst = hInstance; //������ ���������� ������� � ����� hInst
	hWnd = CreateWindow(szWindowClass, 	// ��� ����� ����
		szTitle, 				// ����� ��������
		WS_CAPTION | WS_BORDER | WS_HSCROLL,			// ����� ����
		10, 			// ��������� �� �	
		30,			// ��������� �� Y	
		400, 			// ����� �� �
		300, 			// ����� �� Y
		NULL, 					// ���������� ������������ ����	
		NULL, 					// ���������� ���� ����
		hInstance, 				// ���������� ��������
		NULL); 				// ��������� ���������.

	if (!hWnd) 	//���� ���� �� ���������, ������� ������� FALSE
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow); 		//�������� ����
	UpdateWindow(hWnd); 				//������� ����
	return TRUE;
}

// FUNCTION: WndProc (HWND, unsigned, WORD, LONG)
// ³����� ���������. ������ � �������� �� �����������, �� ��������� � �������


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt;

	switch (message)
	{
	case WM_CREATE: 				//����������� ��������� ��� �������� ����
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
		//������� ���������� ��� ������ ���� 
		MessageBox(hWnd, "TEXT", "CAPTION", MB_OK);
		break;
	case WM_PAINT: 				//������������ ����
		hdc = BeginPaint(hWnd, &ps); 	//������ ��������� ����	
		GetClientRect(hWnd, &rt); 		//������� ���� ��� ���������
		DrawText(hdc, "�����, ���!", -1, &rt, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hWnd, &ps); 		//�������� ��������� ����	
		break;

	case WM_DESTROY: 				//���������� ������
		PostQuitMessage(0);
		break;
	default:
		//������� ����������, �� �� �������� ������������
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

