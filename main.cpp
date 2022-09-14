#include <windows.h>

bool running = true;

LRESULT CALLBACK windowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT result = 0;

	switch (uMsg) {
		case WM_CLOSE: 
		case WM_DESTROY: {
			running = false;

		} break;

		default:
			result = DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return result;
}

int WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lmCmdLine,
	int nShowCmd
) {
	wchar_t windowClassName[] = L"Ping Pong Game";

	// Create Window class
	WNDCLASS windowClass = {};
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpszClassName = windowClassName;
	windowClass.lpfnWndProc = windowCallback;

	// Register Class
	RegisterClass(&windowClass);

	// Create Window
	HWND window = CreateWindow(
		windowClass.lpszClassName, 
		windowClassName,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1280,
		720,
		0, 
		0,
		hInstance,
		0
	);

	while (running) {
		MSG message;
		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}

	return 0;
}