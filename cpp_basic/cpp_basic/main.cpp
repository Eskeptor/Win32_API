#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPWSTR lpszClass = L"My First Win32 API Program";

/* WinMain �Լ��� ���������� �ϴ� ��
 * 1. ������ Ŭ������ �����(RegisterClass)
 * 2. ������ ��ü�� �����Ѵ�(CreateWindow) 
 * 3. �����츦 ȭ�鿡 �����ش�(ShowWindow)
 * 4. �Է���ġ�� ���� �Է� ��ȣ�� �޴´�(GetMessage)
 */


/* WinMain �Լ��� �μ�
 * hInstance : ���� ����ǰ� �ִ� ���α׷��� �ν��Ͻ� �ڵ�
 * hPrevInstance : �ٷ� �տ� ����� ���α׷��� �ν��Ͻ� �ڵ�, ��������� NULL���� �ش�.
 * lpCmdLine : ����� ����. ���� ���α׷������� �����Լ����� argv�� �ش�ȴ�.
 * nCmdShow : �����츦 �����ִ� ������ �÷���
 * �ν��Ͻ� �ڵ� : ��üȭ�� Ŭ����
 */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;										// Ŭ���� ���� ����Ʈ ��
	WndClass.cbWndExtra = 0;										// ������ ���� ����Ʈ ��
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// �������� ����
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					// ���α׷����� ����� Ŀ��
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				// ���α׷����� ����� ������
	WndClass.hInstance = hInstance;									// ���α׷��� �ν��Ͻ� �ڵ�
	WndClass.lpfnWndProc = (WNDPROC)WndProc;						// ���ν��� �Լ���
	WndClass.lpszClassName = lpszClass;								// ����ü�� ������� Ŭ������
	WndClass.lpszMenuName = NULL;									// ���α׷����� ����� �޴�
	WndClass.style = CS_HREDRAW | CS_VREDRAW;						// ������ ��Ÿ��

	RegisterClass(&WndClass);
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	// CreateWindow(Ŭ�����������ڿ�, ����������ǥ����, �����콺Ÿ��, ������x��ǥ, ������y��ǥ, ��������, ���������, �θ�������, �޴�, �ν��Ͻ��ڵ�, ������)

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
	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}