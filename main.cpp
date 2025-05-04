//Basic

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





// NO Interaction 
// On powershell
// Do
// taskkill /IM main.exe /F



/*
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
*/









// NO Background

/*
#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_KEYDOWN:
            if (wParam == VK_ESCAPE) { // Pressing ESC will close the window
                DestroyWindow(hwnd);
            }
            return 0;

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            RECT rect;
            GetClientRect(hwnd, &rect);
            SetBkMode(hdc, TRANSPARENT); // Make background transparent
            SetTextColor(hdc, RGB(255, 255, 255)); // White text
            DrawText(hdc, "Hello, World", -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            EndPaint(hwnd, &ps);
            return 0;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
    const char CLASS_NAME[] = "TransparentTextWindow";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = NULL; // No background color

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        WS_EX_TOPMOST | WS_EX_LAYERED, // Always on top, layered for transparency
        CLASS_NAME,
        NULL,
        WS_POPUP, // No border, no title bar
        100, 100, 300, 100,
        NULL, NULL, hInstance, NULL
    );

    if (!hwnd) return 0;

    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY); // Make black fully transparent

    ShowWindow(hwnd, SW_SHOWNOACTIVATE);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

*/


// Floating 
// Hard to close
// On powershell
// Do
// taskkill /IM main.exe /F


/*
#include <windows.h>
#include <cstdlib>  // For rand()
#include <ctime>    // For seeding randomness

// Global Variables
int x = 100, y = 100; // Initial window position
int dx = 5, dy = 5;   // Step size

// Window procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_KEYDOWN:
            if (wParam == VK_ESCAPE) DestroyWindow(hwnd);
            return 0;

        case WM_TIMER: {
            RECT screenRect;
            GetClientRect(GetDesktopWindow(), &screenRect);

            // Randomly change direction sometimes
            if (rand() % 10 == 0) {
                dx = (rand() % 7) - 3; // -3 to +3 step variation
                dy = (rand() % 7) - 3;
            }

            // Move window
            x += dx;
            y += dy;

            // Keep it within screen bounds
            if (x < 0 || x + 300 > screenRect.right) dx = -dx;
            if (y < 0 || y + 100 > screenRect.bottom) dy = -dy;

            // Set new position
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
            DrawText(hdc, "Hello, World", -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            EndPaint(hwnd, &ps);
            return 0;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
    srand(static_cast<unsigned>(time(nullptr))); // Seed randomness

    const char CLASS_NAME[] = "FloatingWindow";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = NULL;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        WS_EX_TOPMOST | WS_EX_LAYERED, CLASS_NAME, NULL, WS_POPUP,
        x, y, 300, 100, NULL, NULL, hInstance, NULL
    );

    if (!hwnd) return 0;

    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
    ShowWindow(hwnd, SW_SHOWNOACTIVATE);

    // Start movement loop (updates every 50ms)
    SetTimer(hwnd, 1, 50, NULL);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

*/

// More Vigorous on entire screen
#include <windows.h>
#include <cstdlib>  // For rand()
#include <ctime>    // For seeding randomness

// Global Variables
int x = 100, y = 100; // Initial position
int dx = 10, dy = 10; // Increased speed

// Window procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_KEYDOWN:
            if (wParam == VK_ESCAPE) DestroyWindow(hwnd);
            return 0;

        case WM_TIMER: {
            RECT screenRect;
            GetWindowRect(GetDesktopWindow(), &screenRect); // Get full screen dimensions

            // Change direction randomly
            if (rand() % 5 == 0) {
                dx = (rand() % 15) - 7; // More erratic movement (-7 to +7 variation)
                dy = (rand() % 15) - 7;
            }

            // Move window
            x += dx;
            y += dy;

            // Keep it within screen bounds
            if (x < 0 || x + 300 > screenRect.right) dx = -dx;
            if (y < 0 || y + 100 > screenRect.bottom) dy = -dy;

            // Update position
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
            DrawText(hdc, "Hello, World", -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            EndPaint(hwnd, &ps);
            return 0;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
    srand(static_cast<unsigned>(time(nullptr))); // Seed randomness

    const char CLASS_NAME[] = "FloatingWindow";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = NULL;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        WS_EX_TOPMOST | WS_EX_LAYERED, CLASS_NAME, NULL, WS_POPUP,
        x, y, 300, 100, NULL, NULL, hInstance, NULL
    );

    if (!hwnd) return 0;

    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
    ShowWindow(hwnd, SW_SHOWNOACTIVATE);

    // Faster movement updates (every 25ms instead of 50ms)
    SetTimer(hwnd, 1, 25, NULL);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

