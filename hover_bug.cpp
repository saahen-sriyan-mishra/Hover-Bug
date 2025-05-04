#include <windows.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>

int x = 100, y = 100;
int dx = 2, dy = 2;
std::string displayText = "Hover-Bug";
HWND hwndMain = NULL;

// Color animation variables
int currentColorIndex = 0;
float colorPhase = 0.0f;
const float colorSpeed = 0.01f;
COLORREF currentColor = RGB(255, 255, 255);

// Function to generate smoothly transitioning colors
COLORREF GetAnimatedColor(float phase) {
    // This creates a smooth color transition through the color spectrum
    int r = static_cast<int>((sin(phase) * 127) + 128);
    int g = static_cast<int>((sin(phase + 2.0f * 3.14159f / 3.0f) * 127) + 128);
    int b = static_cast<int>((sin(phase + 4.0f * 3.14159f / 3.0f) * 127) + 128);
    
    return RGB(r, g, b);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_TIMER: {
            RECT screenRect;
            GetWindowRect(GetDesktopWindow(), &screenRect);

            if (rand() % 100 == 0) { // Reduced frequency of direction changes
                dx = (rand() % 5) - 2; // Reduced maximum speed
                dy = (rand() % 5) - 2;
            }

            x += dx;
            y += dy;

            if (x < 0 || x + 300 > screenRect.right) dx = -dx;
            if (y < 0 || y + 100 > screenRect.bottom) dy = -dy;

            SetWindowPos(hwnd, NULL, x, y, 300, 100, SWP_NOZORDER | SWP_NOACTIVATE);
            
            // Update color animation
            colorPhase += colorSpeed;
            if (colorPhase > 2 * 3.14159f) {
                colorPhase -= 2 * 3.14159f;
            }
            currentColor = GetAnimatedColor(colorPhase);
            
            // Force a repaint to show the new color
            InvalidateRect(hwnd, NULL, TRUE);
            return 0;
        }

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            RECT rect;
            GetClientRect(hwnd, &rect);
            SetBkMode(hdc, TRANSPARENT);
            SetTextColor(hdc, currentColor);
            DrawText(hdc, displayText.c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            EndPaint(hwnd, &ps);
            return 0;
        }
        
        case WM_COPYDATA: {
            PCOPYDATASTRUCT pCopyData = (PCOPYDATASTRUCT)lParam;
            if (pCopyData->dwData == 1) {
                displayText = std::string((char*)pCopyData->lpData, pCopyData->cbData);
                InvalidateRect(hwnd, NULL, TRUE);
            }
            return TRUE;
        }
        
        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int) {
    srand(static_cast<unsigned>(time(nullptr)));

    // Check for existing instance
    hwndMain = FindWindow("FloatingWindow", NULL);
    if (hwndMain) {
        if (lpCmdLine && strlen(lpCmdLine) > 0) {
            COPYDATASTRUCT cds;
            cds.dwData = 1;
            cds.cbData = strlen(lpCmdLine) + 1;
            cds.lpData = (void*)lpCmdLine;
            SendMessage(hwndMain, WM_COPYDATA, (WPARAM)NULL, (LPARAM)&cds);
        }
        return 0;
    }

    if (lpCmdLine && strlen(lpCmdLine) > 0) {
        displayText = lpCmdLine;
    }

    const char CLASS_NAME[] = "FloatingWindow";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = NULL;

    RegisterClass(&wc);

    // Create window with additional style to hide from taskbar
    hwndMain = CreateWindowEx(
        WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW,  // Added WS_EX_TOOLWINDOW
        CLASS_NAME, 
        NULL, 
        WS_POPUP,
        x, y, 300, 100, 
        NULL, NULL, hInstance, NULL);

    if (!hwndMain) return 0;

    // Make window non-interactive
    SetWindowLong(hwndMain, GWL_EXSTYLE, 
        GetWindowLong(hwndMain, GWL_EXSTYLE) | WS_EX_TRANSPARENT | WS_EX_LAYERED);

    SetLayeredWindowAttributes(hwndMain, RGB(0, 0, 0), 0, LWA_COLORKEY);
    ShowWindow(hwndMain, SW_SHOWNOACTIVATE);

    SetTimer(hwndMain, 1, 25, NULL);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}