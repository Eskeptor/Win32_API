#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPWSTR lpszClass = TEXT("Output Example1");

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
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 700, 600, NULL, (HMENU)NULL, hInstance, NULL);

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
	LPWSTR str = TEXT("Just Test");
	LPWSTR long_str = TEXT("동해물과 백두산이 마르고 닳도록, 하나님이 보우하사 우리나라만세. \
남산위에 저 소나무 철갑을 두른듯, 바람서리 불변함은 우리기상일세. \
가을 하늘 공활한데, 높고 구름없이 밝은 달은 우리가슴 일편단심일세. \
이 기상과 이 맘으로 충성을 다하여 괴로우나 즐거우나 나라사랑하세.");
	RECT rect = { 20,40,400,400 };
	POINT polygon[] = { 70,420,20,450,50,520,90,520,120,450 };
	POINT polyline[] = { 190,420,140,450,170,520,210,520,240,450 };

	switch (iMessage)
	{
	case WM_CREATE:
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		TextOut(hdc, 20, 20, str, wcslen(str));	// 일반 텍스트 출력
		DrawText(hdc, long_str, wcslen(long_str), &rect, DT_WORDBREAK | DT_LEFT);	// 사각형안에 텍스트 출력

		SetPixel(hdc, 20, 10, RGB(255, 0, 0));	// 점 출력
		MoveToEx(hdc, 20, 160, NULL);	// 선 출력
		LineTo(hdc, 80, 160);			// 선 출력
		Rectangle(hdc, 20, 180, 120, 280);	// 사각형 출력
		RoundRect(hdc, 140, 180, 240, 280, 20, 20);	// 라운드 사각형 출력
		Ellipse(hdc, 20, 300, 120, 400);	// 원 출력
		Arc(hdc, 140, 300, 240, 400, 190, 300, 240, 350);	// 원 출력(두 선 잇기)
		Chord(hdc, 260, 300, 360, 400, 310, 300, 260, 350);	// 원 출력(현 출력)
		Pie(hdc, 380, 300, 480, 400, 430, 300, 380, 350);	// 원 출력(각 출력)
		Polygon(hdc, polygon, 5);	// 다각형 출력
		Polyline(hdc, polyline, 5);	// 다각선 출력

		EndPaint(hWnd, &ps);

		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}