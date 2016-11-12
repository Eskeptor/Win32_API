#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPWSTR lpszClass = TEXT("Mouse Click");

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
	HDC hdc;
	PAINTSTRUCT ps;
	LONG dwStyle;

	// 윈도우 스타일 변경
	LPWSTR strTitle = TEXT("윈도우 스타일 변경");


	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		dwStyle = GetWindowLong(hWnd, GWL_STYLE);
		dwStyle = dwStyle | WS_VSCROLL | WS_HSCROLL;
		SetWindowLong(hWnd, GWL_STYLE, dwStyle);
		SendMessage(hWnd, WM_NCPAINT, 1, 0);
		MoveWindow(hWnd, 300, 300, 500, 500, TRUE);
		// WM_NCPAINT : 윈도우의 외곽영역을 그리는 메시지
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 19, 19, strTitle, wcslen(strTitle));
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}