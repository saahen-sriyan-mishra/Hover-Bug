#include <windows.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>

// Window dimensions
const int WINDOW_WIDTH = 300;
const int WINDOW_HEIGHT = 100;

// Movement variables
int x = 0, y = 0; // Will be initialized to center
int dx = 0, dy = 0;
const int MOVE_SPEED = 3; // Constant speed
std::string displayText = "Hover-Bug";
HWND hwndMain = NULL;

// Movement timing variables
DWORD lastDirectionChange = 0;
const DWORD minDirectionTime = 3000; // 3 seconds
const DWORD maxDirectionTime = 7000; // 7 seconds
DWORD currentDirectionDuration = 0;

// Color animation variables
float colorPhase = 0.0f;
const float colorSpeed = 0.01f;
COLORREF currentColor = RGB(255, 255, 255);

COLORREF GetAnimatedColor(float phase) {
    int r = static_cast<int>((sin(phase) * 127) + 128);
    int g = static_cast<int>((sin(phase + 2.0f * 3.14159f / 3.0f) * 127) + 128);
    int b = static_cast<int>((sin(phase + 4.0f * 3.14159f / 3.0f) * 127) + 128);
    return RGB(r, g, b);
}

void ChangeDirection() {
    // Random direction but maintain constant speed
    float angle = (rand() % 360) * 3.14159f / 180.0f; // Random angle in radians
    dx = static_cast<int>(cos(angle) * MOVE_SPEED);
    dy = static_cast<int>(sin(angle) * MOVE_SPEED);
    
    // Ensure we're moving somewhere
    if (dx == 0 && dy == 0) {
        dx = MOVE_SPEED;
    }
    
    lastDirectionChange = GetTickCount();
    currentDirectionDuration = minDirectionTime + (rand() % (maxDirectionTime - minDirectionTime));
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_TIMER: {
            RECT screenRect;
            GetWindowRect(GetDesktopWindow(), &screenRect);

            // Check if it's time to change direction
            DWORD currentTime = GetTickCount();
            if (currentTime - lastDirectionChange > currentDirectionDuration) {
                ChangeDirection();
            }

            x += dx;
            y += dy;

            // Bounce off edges
            if (x < 0 || x + WINDOW_WIDTH > screenRect.right) {
                dx = -dx;
                x += dx * 2; // Prevent sticking to edge
                ChangeDirection(); // Change direction after bounce
            }
            if (y < 0 || y + WINDOW_HEIGHT > screenRect.bottom) {
                dy = -dy;
                y += dy * 2;
                ChangeDirection();
            }

            SetWindowPos(hwnd, NULL, x, y, WINDOW_WIDTH, WINDOW_HEIGHT, 
                        SWP_NOZORDER | SWP_NOACTIVATE);
            
            // Update color animation
            colorPhase += colorSpeed;
            if (colorPhase > 2 * 3.14159f) {
                colorPhase -= 2 * 3.14159f;
            }
            currentColor = GetAnimatedColor(colorPhase);
            
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

    // Register window class
    const char CLASS_NAME[] = "FloatingWindow";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = NULL;
    RegisterClass(&wc);

    // Calculate center position
    RECT screenRect;
    GetWindowRect(GetDesktopWindow(), &screenRect);
    x = (screenRect.right - WINDOW_WIDTH) / 2;
    y = (screenRect.bottom - WINDOW_HEIGHT) / 2;

    // Create window
    hwndMain = CreateWindowEx(
        WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW,
        CLASS_NAME, 
        NULL, 
        WS_POPUP,
        x, y, WINDOW_WIDTH, WINDOW_HEIGHT, 
        NULL, NULL, hInstance, NULL);

    if (!hwndMain) return 0;

    // Make window non-interactive
    SetWindowLong(hwndMain, GWL_EXSTYLE, 
        GetWindowLong(hwndMain, GWL_EXSTYLE) | WS_EX_TRANSPARENT | WS_EX_LAYERED);

    SetLayeredWindowAttributes(hwndMain, RGB(0, 0, 0), 0, LWA_COLORKEY);
    ShowWindow(hwndMain, SW_SHOWNOACTIVATE);

    // Initialize movement
    ChangeDirection();
    SetTimer(hwndMain, 1, 25, NULL);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}