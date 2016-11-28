#include <Windows.h>
#include <tchar.h>
#include "hmenu.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPWSTR lpszClass = TEXT("Child Window");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&WndClass);
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, 0, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static HWND hChkRectangle, hChkEllipse;
	static BOOL bEllipse = FALSE;
	static BOOL bRectangle = FALSE;

	HDC hdc;
	PAINTSTRUCT ps;

	HBRUSH myBrush, oldBrush;
	static short nGraph = 0;
	static short nColor = 0;

	switch (iMessage)
	{
	case WM_CREATE:
		CreateWindow(TEXT("button"), TEXT("버튼1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 20, 100, 25, hWnd, (HMENU)ID_BTN_BUTTON1, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("버튼2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 60, 100, 25, hWnd, (HMENU)ID_BTN_BUTTON2, g_hInst, NULL);

		hChkRectangle = CreateWindow(TEXT("button"), TEXT("사각형"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 20, 120, 80, 25, hWnd, (HMENU)ID_CHK_RECTANGLE, g_hInst, NULL);
		hChkEllipse = CreateWindow(TEXT("button"), TEXT("사각형"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 20, 160, 80, 25, hWnd, (HMENU)ID_CHK_ELLIPSE, g_hInst, NULL);

		CreateWindow(TEXT("button"), TEXT("도형"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 5, 220, 100, 100, hWnd, (HMENU)ID_GRBOX1, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("색상"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 140, 220, 100, 150, hWnd, (HMENU)ID_GRBOX2, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("사각형"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 20, 240, 80, 25, hWnd, (HMENU)ID_RAD1, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("타원"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 20, 280, 80, 25, hWnd, (HMENU)ID_RAD2, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("빨강"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 150, 240, 80, 25, hWnd, (HMENU)ID_RAD3, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("초록"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 150, 280, 80, 25, hWnd, (HMENU)ID_RAD4, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("파랑"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 150, 320, 80, 25, hWnd, (HMENU)ID_RAD5, g_hInst, NULL);
		CheckRadioButton(hWnd, ID_RAD1, ID_RAD2, ID_RAD1);
		CheckRadioButton(hWnd, ID_RAD3, ID_RAD5, ID_RAD3);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_BTN_BUTTON1:
			MessageBox(hWnd, TEXT("버튼1에 이벤트를 발생시켰습니다."), TEXT("button"), MB_OK);
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				MessageBox(hWnd, TEXT("버튼1이 클릭되었습니다."), TEXT("button"), MB_OK);
				break;
			case BN_SETFOCUS:
				MessageBox(hWnd, TEXT("버튼1에 마우스가 올라갔습니다.."), TEXT("button"), MB_OK);
				break;
			default:
				break;
			}
			break;
		case ID_BTN_BUTTON2:
			MessageBox(hWnd, TEXT("버튼2에 이벤트를 발생시켰습니다."), TEXT("button"), MB_OK);
			break;
		case ID_CHK_RECTANGLE:
			if (SendMessage(hChkRectangle, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
			{
				SendMessage(hChkRectangle, BM_SETCHECK, BST_CHECKED, 0);
				bRectangle = true;
			}
			else
			{
				SendMessage(hChkRectangle, BM_SETCHECK, BST_UNCHECKED, 0);
				bRectangle = false;
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_CHK_ELLIPSE:
			if (SendMessage(hChkEllipse, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
			{
				SendMessage(hChkEllipse, BM_SETCHECK, BST_CHECKED, 0);
				bEllipse = true;
			}
			else
			{
				SendMessage(hChkEllipse, BM_SETCHECK, BST_UNCHECKED, 0);
				bEllipse = false;
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_RAD1:
			nGraph = 0;
			break;
		case ID_RAD2:
			nGraph = 1;
			break;
		case ID_RAD3:
			nColor = 0;
			break;
		case ID_RAD4:
			nColor = 1;
			break;
		case ID_RAD5:
			nColor = 2;
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		if (bRectangle == TRUE)
		{
			Rectangle(hdc, 150, 120, 250, 200);
		}
		if (bEllipse == TRUE)
		{
			Ellipse(hdc, 150, 120, 250, 200);
		}

		switch (nColor)
		{
		case 0:
			myBrush = CreateSolidBrush(RGB(255, 0, 0));
			break;
		case 1:
			myBrush = CreateSolidBrush(RGB(0, 255, 0));
			break;
		case 2:
			myBrush = CreateSolidBrush(RGB(0, 0, 255));
			break;
		}

		oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
		switch (nGraph)
		{
		case 0:
			Rectangle(hdc, 10, 400, 200, 500);
			break;
		case 1:
			Ellipse(hdc, 10, 400, 200, 500);
			break;
		}

		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}