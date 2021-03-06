// fileio_gui.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "fileio_gui.h"

#define MAX_LOADSTRING			100
#define WINDOW_WIDTH			1010
#define WINDOW_HEIGHT			480
#define CLASS_NAME				TEXT("File IO")


// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND list;										// 리스트 박스
HWND textEdit;									// 에딧 박스
TCHAR* editText;
std::wstring fileExePath;
std::vector<std::wstring> filePathVector;
int curSelectListIdx = -1;



// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
LRESULT 			ReadData(int);



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FILEIOGUI));

	MSG msg;

	// 기본 메시지 루프입니다.
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASS wcex;

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FILEIOGUI));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_FILEIOGUI);
	wcex.lpszClassName = CLASS_NAME;

	return RegisterClass(&wcex);
}



//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	HWND hWnd = CreateWindow(CLASS_NAME, CLASS_NAME, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, 0, WINDOW_WIDTH, WINDOW_HEIGHT, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}



//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	TCHAR curDirectory[MAX_PATH] = { 0, };
	GetCurrentDirectory(MAX_PATH, curDirectory);
	const TCHAR FILE_DIRECTORY[] = TEXT("\\data\\");
	const TCHAR FILE_EXTENSION[] = TEXT("*.h");
	const TCHAR FILE_EXE_NAME[] = TEXT("fileio.exe");
	std::wstring fileDirectory = std::wstring(FILE_DIRECTORY);
	std::wstring fileExtension = std::wstring(FILE_EXTENSION);
	std::wstring fullDirectory = std::wstring(curDirectory) + fileDirectory;
	std::wstring firstFile = fullDirectory + fileExtension;
	std::wstring wTmp;

	WIN32_FIND_DATA findData;
	
	TCHAR selectItem[MAX_LOADSTRING] = { 0, };

	fileExePath = fullDirectory + FILE_EXE_NAME;

	switch (message)
	{
	case WM_CREATE:
	{
		int i = 0;
		HANDLE hFind = FindFirstFile(firstFile.c_str(), &findData);
		list = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY, 10, 10, 240, 100, hWnd, (HMENU)ID_LIST, hInst, NULL);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			do
			{
				wTmp = fullDirectory + findData.cFileName;
				filePathVector.push_back(wTmp);
				SendMessage(list, LB_ADDSTRING, 0, (LPARAM)findData.cFileName);
			} while (FindNextFile(hFind, &findData));
		}
		CreateWindow(TEXT("button"), TEXT("실행파일 열기"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
			10, 120, 115, 25, hWnd, (HMENU)ID_BUTTON_RUN, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("소스파일 열기"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
			135, 120, 115, 25, hWnd, (HMENU)ID_BUTTON_SOURCE, hInst, NULL);
		textEdit = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_MULTILINE,
			265, 10, 720, 400, hWnd, (HMENU)ID_TEXTEDIT, hInst, NULL);
	}
	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		int listId;
		// 메뉴 선택을 구문 분석합니다.

		switch (wmId)
		{
		case IDM_ABOUT:
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		}
		break;
		case IDM_EXIT:
		{
			DestroyWindow(hWnd);
		}
		break;
		case ID_BUTTON_RUN:
		{
			if (curSelectListIdx != -1)
			{
				STARTUPINFO startInfo = { 0, };
				PROCESS_INFORMATION pi;
				startInfo.cb = sizeof(STARTUPINFO);
				TCHAR command[MAX_PATH] = { 0, };
				wsprintf(command, TEXT("%s -%d"), fileExePath.c_str(), curSelectListIdx);

				CreateProcess(NULL, command, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &startInfo, &pi);
			}
		}
		break;
		case ID_BUTTON_SOURCE:
		{
			if (curSelectListIdx != -1)
			{
				ShellExecute(NULL, TEXT("open"), TEXT("notepad"), filePathVector[curSelectListIdx].c_str(), NULL, SW_SHOW);
			}
		}
		break;
		case ID_LIST:
		{
			listId = HIWORD(wParam);
			switch (listId)
			{
			case LBN_SELCHANGE:
			{
				curSelectListIdx = SendMessage(list, LB_GETCURSEL, 0, 0);
				if (ReadData(curSelectListIdx))
					SetWindowText(textEdit, editText);
				else
					SetWindowText(textEdit, TEXT("파일을 열지 못함"));
			}
			break;
			}
		}
		break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		if (editText != NULL)
			free(editText);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}



// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


LRESULT ReadData(int idx)
{
	HANDLE file = CreateFile(filePathVector[idx].c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD fileSize = GetFileSize(file, NULL);
	DWORD dwRead;
	curSelectListIdx = idx;

	if (editText != NULL)
		free(editText);
	editText = (TCHAR*)calloc(1, fileSize + sizeof(TCHAR));
	ReadFile(file, editText, fileSize, &dwRead, NULL);
	CloseHandle(file);
	return 1;
}