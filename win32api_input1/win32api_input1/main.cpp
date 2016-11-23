#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPWSTR lpszClass = TEXT("Output Test(Mouse)");

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
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;

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
	static int xpos = 0, ypos = 0;
	static TCHAR strTemp[MAX_PATH];
	static TCHAR strCapture[MAX_PATH];

	switch (iMessage)
	{
	case WM_CREATE:
		wcscpy(strTemp, L"");
		wcscpy(strCapture, L"캡쳐 비활성화");
		return 0;
	case WM_MOUSEMOVE:
		xpos = LOWORD(lParam);
		ypos = HIWORD(lParam);
		wsprintf(strTemp, L"좌표(%d, %d), 키보드 조합상태 : %d", xpos, ypos, wParam);
		if (GetCapture() == hWnd)
		{
			wsprintf(strCapture, L"캡쳐 활성화");
		}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 20, 20, strTemp, wcslen(strTemp));
		TextOut(hdc, 20, 40, strCapture, wcslen(strCapture));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_LBUTTONDBLCLK:
		MessageBox(hWnd, TEXT("\"더블클릭\" 하였습니다."), TEXT("메시지 박스"), MB_OK);
		return 0;
	case WM_RBUTTONDOWN:
		SetCapture(hWnd);
		//wsprintf(strCapture, L"캡쳐 활성화");
		return 0;
	case WM_RBUTTONUP:
		ReleaseCapture();
		wsprintf(strCapture, L"캡쳐 비활성화");
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}