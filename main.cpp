#include <windows.h>
#include <string>

#define ID_EDIT 101
#define ID_BUTTON 102

HWND hEdit;

void LaunchHoverBug(const std::string& text) {
    std::string command = "Hover_Bug.exe " + text;
    system(command.c_str()); // Launch Hover_Bug with text argument
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_COMMAND:
            if (LOWORD(wParam) == ID_BUTTON) {
                char buffer[256];
                GetWindowText(hEdit, buffer, 256);
                LaunchHoverBug(buffer);
            }
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
    const char CLASS_NAME[] = "LauncherWindow";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, "Hover-Bug Launcher", WS_OVERLAPPEDWINDOW,
                               CW_USEDEFAULT, CW_USEDEFAULT, 300, 150,
                               NULL, NULL, hInstance, NULL);

    hEdit = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                           20, 20, 200, 20, hwnd, (HMENU)ID_EDIT, hInstance, NULL);

    CreateWindowEx(0, "BUTTON", "Start", WS_CHILD | WS_VISIBLE,
                   20, 50, 100, 30, hwnd, (HMENU)ID_BUTTON, hInstance, NULL);

    ShowWindow(hwnd, SW_SHOW);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}