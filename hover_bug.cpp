// Accept input
#include <windows.h>
#include <string>
#include <cstdlib>
#include <ctime>

int x = 100, y = 100;
int dx = 10, dy = 10;
std::string displayText = "Hover-Bug";

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_TIMER: {
            RECT screenRect;
            GetWindowRect(GetDesktopWindow(), &screenRect);

            if (rand() % 5 == 0) {
                dx = (rand() % 15) - 7;
                dy = (rand() % 15) - 7;
            }

            x += dx;
            y += dy;

            if (x < 0 || x + 300 > screenRect.right) dx = -dx;
            if (y < 0 || y + 100 > screenRect.bottom) dy = -dy;

            SetWindowPos(hwnd, NULL, x, y, 300, 100, SWP_NOZORDER | SWP_NOACTIVATE);
            return 0;
        }

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            RECT rect;
            GetClientRect(hwnd, &rect);
            SetBkMode(hdc, TRANSPARENT);
            SetTextColor(hdc, RGB(255, 255, 255));
            DrawText(hdc, displayText.c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            EndPaint(hwnd, &ps);
            return 0;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int) {
    srand(static_cast<unsigned>(time(nullptr)));

    if (lpCmdLine && strlen(lpCmdLine) > 0) {
        displayText = lpCmdLine; // Use user input from main.exe
    }

    const char CLASS_NAME[] = "FloatingWindow";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = NULL;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_LAYERED, CLASS_NAME, NULL, WS_POPUP,
                               x, y, 300, 100, NULL, NULL, hInstance, NULL);

    if (!hwnd) return 0;

    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
    ShowWindow(hwnd, SW_SHOWNOACTIVATE);

    SetTimer(hwnd, 1, 25, NULL);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}