#include "Headers.h"


LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ButtonWndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE hInst;
HWND hMainWindow;
LPCSTR MainWindowTitle = "Main Window";
LPCSTR MainWindowClass = "MainWindowClass";

HWND hButtonWindow1;
HWND hButtonWindow2;
HWND hButtonWindow3;
HWND hButtonWindow4;
LPCSTR ButtonWindowClass = "ButtonWindowClass";

#define BID_BUTTON1 2006
#define BID_BUTTON2 2007
#define BID_BUTTON3 2008
#define BID_BUTTON4 2009

int buttonHStart = 5;
int buttonWidth = 100;
int buttonHeight = 20;
int buttonVSpace = 0;
int numButtons = 4;

struct ButtonData {
	bool isActive;
	bool isPressed;
	char text[32];
	void* funcCall;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {



	// Main window
		WNDCLASSEX wcex = { 0 };
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = MainWndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = (HICON)LoadImage(NULL, "largeicon.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED);
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = GetSysColorBrush(COLOR_GRAYTEXT);//  (HBRUSH)(COLOR_GRAYTEXT);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = MainWindowClass;
		wcex.hIconSm = (HICON)LoadImage(NULL, "smallicon.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED);
		RegisterClassEx(&wcex);

		hInst = hInstance;
		hMainWindow = CreateWindowEx(0, MainWindowClass, MainWindowTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 500, 500, NULL, NULL, hInstance, NULL);

	// End Main window

	// Custom Control
		wcex = { 0 };
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_GLOBALCLASS | CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = ButtonWndProc;
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(55, 255, 55));
		wcex.lpszClassName = ButtonWindowClass;
		wcex.cbWndExtra = sizeof(ButtonData*);
		RegisterClassEx(&wcex);

		hButtonWindow1 = CreateWindowEx(0, ButtonWindowClass, "button title", WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hMainWindow, (HMENU)BID_BUTTON1, hInst, NULL);
		hButtonWindow2 = CreateWindowEx(0, ButtonWindowClass, "button title", WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hMainWindow, (HMENU)BID_BUTTON2, hInst, NULL);
		hButtonWindow3 = CreateWindowEx(0, ButtonWindowClass, "button title", WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hMainWindow, (HMENU)BID_BUTTON3, hInst, NULL);
		hButtonWindow4 = CreateWindowEx(0, ButtonWindowClass, "button title", WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hMainWindow, (HMENU)BID_BUTTON4, hInst, NULL);
		ShowWindow(hMainWindow, nCmdShow);
		UpdateWindow(hMainWindow);






	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;


	return 1;

}

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	int buttonCounter = 0;
	switch (message) {
	case WM_CREATE:



		break;
	case WM_SIZE:
		SetWindowPos(hButtonWindow1, HWND_TOP, buttonHStart, buttonCounter, buttonWidth, buttonHeight, SWP_SHOWWINDOW);
		buttonCounter += buttonHeight;
		SetWindowPos(hButtonWindow2, HWND_TOP, buttonHStart, buttonCounter, buttonWidth, buttonHeight, SWP_SHOWWINDOW);
		buttonCounter += buttonHeight;
		SetWindowPos(hButtonWindow3, HWND_TOP, buttonHStart, buttonCounter, buttonWidth, buttonHeight, SWP_SHOWWINDOW);
		buttonCounter += buttonHeight;
		SetWindowPos(hButtonWindow4, HWND_TOP, buttonHStart, buttonCounter, buttonWidth, buttonHeight, SWP_SHOWWINDOW);

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK ButtonWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;
	ButtonData* bData = (ButtonData*)GetWindowLongPtr(hWnd, 0);
	switch (message) {


		case WM_NCCREATE:
			bData = (ButtonData*)malloc(sizeof(ButtonData));
			SetWindowLongPtr(hWnd, 0, (LONG_PTR)bData);
			return 1;
		case WM_NCDESTROY:
			free(bData);
			return 0;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			GetClientRect(hWnd, &rect);
			Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

			SetTextColor(hdc, RGB(0, 0, 0));
			SetBkMode(hdc, TRANSPARENT);
			DrawText(hdc, "Hello World!", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);


			EndPaint(hWnd, &ps);
			break;

	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}