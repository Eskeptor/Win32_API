#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPWSTR lpszClass = TEXT("Keyboard Input");

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
	static TCHAR WM_KEYDOWN_strLine[MAX_PATH];
	static TCHAR WM_CHAR_str[MAX_PATH];
	static int len = 0;
	SIZE size;

	switch (iMessage)
	{
	case WM_CREATE:
		wcscpy(WM_KEYDOWN_strLine, L"");
		wcscpy(WM_CHAR_str, L"");
		len = 0;
		return 0;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_HOME:
			wsprintf(WM_KEYDOWN_strLine, L"%s 키를 눌렀습니다.", L"Home");
			InvalidateRect(hWnd, NULL, TRUE);
			return 0;
		case VK_UP:
			wsprintf(WM_KEYDOWN_strLine, L"%s 키를 눌렀습니다.", L"Up");
			InvalidateRect(hWnd, NULL, TRUE);
			return 0;
		case VK_DOWN:
			wsprintf(WM_KEYDOWN_strLine, L"%s 키를 눌렀습니다.", L"Down");
			InvalidateRect(hWnd, NULL, TRUE);
			return 0;
		case VK_BACK:
			wsprintf(WM_KEYDOWN_strLine, L"%s 키를 눌렀습니다.", L"Backspace");
			return 0;
		}
		return 0;
	case WM_CHAR:
		if (wParam == VK_BACK) {
			if (len == 0)
				break;
			WM_CHAR_str[--len] = (char)wParam;
		}
		else {
			WM_CHAR_str[len++] = (char)wParam;
		}
		hdc = GetDC(hWnd);
		GetTextExtentPoint(hdc, WM_CHAR_str, len, &size);
		SetCaretPos(size.cx + 20, 40);
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 20, 20, WM_KEYDOWN_strLine, wcslen(WM_KEYDOWN_strLine));
		TextOut(hdc, 20, 40, WM_CHAR_str, len);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_SETFOCUS:
		hdc = GetDC(hWnd);
		CreateCaret(hWnd, NULL, 2, 14);
		ShowCaret(hWnd);
		SetCaretPos(20, 40);
		return 0;
	case WM_KILLFOCUS:
		HideCaret(hWnd);
		DestroyCaret();
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}