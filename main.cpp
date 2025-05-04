/* #include <windows.h>

// Window procedure: non-interactive, just default behavior
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            RECT rect;
            GetClientRect(hwnd, &rect);
            SetBkMode(hdc, TRANSPARENT);
            SetTextColor(hdc, RGB(255, 255, 255));
            DrawText(hdc, "Hello, World", -1, &rect,
                     DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            EndPaint(hwnd, &ps);
            return 0;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
    const char CLASS_NAME[] = "AlwaysOnTopWindow";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));  // Optional: black background

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_LAYERED, // Always on top, no taskbar, transparent
        CLASS_NAME,
        NULL, // No title
        WS_POPUP, // No border, no title bar
        100, 100, 300, 100,
        NULL, NULL, hInstance, NULL
    );

    if (!hwnd) return 0;

    SetLayeredWindowAttributes(hwnd, 0, 255, LWA_ALPHA); // 255 = fully opaque

    ShowWindow(hwnd, SW_SHOWNOACTIVATE); // Show without focus

    // Main loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
*/



#include <windows.h>

// Window procedure: non-interactive, just default behavior
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_KEYDOWN: {
            // Check if the pressed key is 'Esc' (key code: 27)
            if (wParam == VK_ESCAPE) {
                PostQuitMessage(0);  // Exit the message loop and close the window
            }
            return 0;
        }

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            RECT rect;
            GetClientRect(hwnd, &rect);
            SetBkMode(hdc, TRANSPARENT);
            SetTextColor(hdc, RGB(255, 255, 255));
            DrawText(hdc, "Hello, World", -1, &rect,
                     DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            EndPaint(hwnd, &ps);
            return 0;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
    const char CLASS_NAME[] = "AlwaysOnTopWindow";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));  // Optional: black background

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_LAYERED, // Always on top, no taskbar, transparent
        CLASS_NAME,
        NULL, // No title
        WS_POPUP, // No border, no title bar
        100, 100, 300, 100,
        NULL, NULL, hInstance, NULL
    );

    if (!hwnd) return 0;

    SetLayeredWindowAttributes(hwnd, 0, 255, LWA_ALPHA); // 255 = fully opaque

    ShowWindow(hwnd, SW_SHOWNOACTIVATE); // Show without focus

    // Main loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
