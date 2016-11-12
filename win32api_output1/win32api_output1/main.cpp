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
	LPWSTR long_str = TEXT("���ع��� ��λ��� ������ �⵵��, �ϳ����� �����ϻ� �츮���󸸼�. \
�������� �� �ҳ��� ö���� �θ���, �ٶ����� �Һ����� �츮����ϼ�. \
���� �ϴ� ��Ȱ�ѵ�, ���� �������� ���� ���� �츮���� ����ܽ��ϼ�. \
�� ���� �� ������ �漺�� ���Ͽ� ���ο쳪 ��ſ쳪 �������ϼ�.");
	RECT rect = { 20,40,400,400 };
	POINT polygon[] = { 70,420,20,450,50,520,90,520,120,450 };
	POINT polyline[] = { 190,420,140,450,170,520,210,520,240,450 };

	switch (iMessage)
	{
	case WM_CREATE:
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		TextOut(hdc, 20, 20, str, wcslen(str));	// �Ϲ� �ؽ�Ʈ ���
		DrawText(hdc, long_str, wcslen(long_str), &rect, DT_WORDBREAK | DT_LEFT);	// �簢���ȿ� �ؽ�Ʈ ���

		SetPixel(hdc, 20, 10, RGB(255, 0, 0));	// �� ���
		MoveToEx(hdc, 20, 160, NULL);	// �� ���
		LineTo(hdc, 80, 160);			// �� ���
		Rectangle(hdc, 20, 180, 120, 280);	// �簢�� ���
		RoundRect(hdc, 140, 180, 240, 280, 20, 20);	// ���� �簢�� ���
		Ellipse(hdc, 20, 300, 120, 400);	// �� ���
		Arc(hdc, 140, 300, 240, 400, 190, 300, 240, 350);	// �� ���(�� �� �ձ�)
		Chord(hdc, 260, 300, 360, 400, 310, 300, 260, 350);	// �� ���(�� ���)
		Pie(hdc, 380, 300, 480, 400, 430, 300, 380, 350);	// �� ���(�� ���)
		Polygon(hdc, polygon, 5);	// �ٰ��� ���
		Polyline(hdc, polyline, 5);	// �ٰ��� ���

		EndPaint(hWnd, &ps);

		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}