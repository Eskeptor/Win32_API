#include <Windows.h>
#include <tchar.h>
#include "resource.h"
#include <time.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPWSTR lpszClass = TEXT("Resource : Icon");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	WndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
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
	static TCHAR* strTime;
	static RECT thisWindow;
	time_t curTime;
	HDC hdc;
	PAINTSTRUCT ps;

	HMENU popup1;
	HMENU popup2;
	POINT point;

	switch (iMessage)
	{
	case WM_CREATE:
		strTime = L"";
		GetClientRect(hWnd, &thisWindow);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_TIMEPRINT:
			time(&curTime);
			strTime = _wctime(&curTime);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_MPOPUP:
			MessageBox(hWnd, TEXT("¸Þ½ÃÁö ÆË¾÷Ã¢ÀÌ ¶¹½À´Ï´Ù."), TEXT("ÆË¾÷Ã¢"), MB_OK);
			break;
		case ID_CUT:
			MessageBox(hWnd, TEXT("ÆË¾÷Ã¢ÀÌ ¶¹½À´Ï´Ù."), TEXT("ÆË¾÷Ã¢"), MB_OK);
			break;
		default:
			break;
		}
		return 0;
	case WM_CONTEXTMENU:
		point.x = LOWORD(lParam);
		point.y = HIWORD(lParam);
		popup1 = LoadMenu(g_hInst, MAKEINTRESOURCE(IDR_POPUP));
		popup2 = GetSubMenu(popup1, 0);
		TrackPopupMenu(popup2, TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, 0, hWnd, NULL);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, thisWindow.right / 2, thisWindow.bottom / 2, strTime, wcslen(strTime) - 1);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}