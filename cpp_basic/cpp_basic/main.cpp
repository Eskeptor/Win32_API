#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPWSTR lpszClass = L"My First Win32 API Program";

/* WinMain 함수가 순차적으로 하는 일
 * 1. 윈도우 클래스를 만든다(RegisterClass)
 * 2. 윈도우 객체를 생성한다(CreateWindow) 
 * 3. 윈도우를 화면에 보여준다(ShowWindow)
 * 4. 입력장치로 부터 입력 신호를 받는다(GetMessage)
 */


/* WinMain 함수의 인수
 * hInstance : 현재 실행되고 있는 프로그램의 인스턴스 핸들
 * hPrevInstance : 바로 앞에 실행된 프로그램의 인스턴스 핸들, 통상적으로 NULL값을 준다.
 * lpCmdLine : 명령행 인자. 도스 프로그램에서의 메인함수에서 argv에 해당된다.
 * nCmdShow : 윈도우를 보여주는 형태의 플래그
 * 인스턴스 핸들 : 실체화된 클래스
 */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;										// 클래스 여분 바이트 수
	WndClass.cbWndExtra = 0;										// 윈도우 여분 바이트 수
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// 윈도우의 배경색
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					// 프로그램에서 사용할 커서
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				// 프로그램에서 사용할 아이콘
	WndClass.hInstance = hInstance;									// 프로그램의 인스턴스 핸들
	WndClass.lpfnWndProc = (WNDPROC)WndProc;						// 프로시저 함수명
	WndClass.lpszClassName = lpszClass;								// 구조체로 만들어질 클래스명
	WndClass.lpszMenuName = NULL;									// 프로그램에서 사용할 메뉴
	WndClass.style = CS_HREDRAW | CS_VREDRAW;						// 윈도우 스타일

	RegisterClass(&WndClass);
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	// CreateWindow(클래스지정문자열, 윈도우제목표시줄, 윈도우스타일, 윈도우x좌표, 윈도우y좌표, 윈도우폭, 윈도우높이, 부모윈도우, 메뉴, 인스턴스핸들, 포인터)

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