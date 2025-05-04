#include <windows.h>
#include <string>
#include <tlhelp32.h>
#include <cstring>

#define ID_EDIT 101
#define ID_START_BUTTON 102
#define ID_STOP_BUTTON 103
#define ID_LABEL 104

HWND hEdit;
HWND hLabel;

DWORD FindHoverBugProcess() {
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (snapshot == INVALID_HANDLE_VALUE) {
        return 0;
    }

    if (Process32First(snapshot, &entry)) {
        do {
            if (_stricmp(entry.szExeFile, "Hover_Bug.exe") == 0) {
                DWORD pid = entry.th32ProcessID;
                CloseHandle(snapshot);
                return pid;
            }
        } while (Process32Next(snapshot, &entry));
    }
    
    CloseHandle(snapshot);
    return 0;
}

void TerminateHoverBug() {
    DWORD pid = FindHoverBugProcess();
    if (pid != 0) {
        HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
        if (hProcess != NULL) {
            TerminateProcess(hProcess, 0);
            CloseHandle(hProcess);
        }
    }
}

void LaunchHoverBug(const std::string& text) {
    TerminateHoverBug();
    
    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    
    std::string commandLine = "Hover_Bug.exe " + text;
    
    CreateProcess(
        NULL,
        const_cast<LPSTR>(commandLine.c_str()),
        NULL,
        NULL,
        FALSE,
        CREATE_NO_WINDOW,
        NULL,
        NULL,
        &si,
        &pi
    );
    
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_COMMAND:
            if (LOWORD(wParam) == ID_START_BUTTON) {
                char buffer[256];
                GetWindowText(hEdit, buffer, 256);
                if (strlen(buffer) == 0) {
                    MessageBox(hwnd, "Please enter some text first!", "Error", MB_ICONERROR);
                } else {
                    LaunchHoverBug(buffer);
                }
            }
            else if (LOWORD(wParam) == ID_STOP_BUTTON) {
                if (FindHoverBugProcess() == 0) {
                    MessageBox(hwnd, "No Hover-Bug object exists to stop!", "Error", MB_ICONERROR);
                } else {
                    TerminateHoverBug();
                }
            }
            return 0;

        case WM_DESTROY:
            TerminateHoverBug(); // Close hover_bug.exe when main.exe closes
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
                               CW_USEDEFAULT, CW_USEDEFAULT, 300, 200,
                               NULL, NULL, hInstance, NULL);

    // Create "Enter text" label
    hLabel = CreateWindowEx(0, "STATIC", "Enter text:", 
                           WS_CHILD | WS_VISIBLE | SS_LEFT,
                           20, 5, 200, 20, hwnd, (HMENU)ID_LABEL, hInstance, NULL);

    hEdit = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                           20, 30, 200, 20, hwnd, (HMENU)ID_EDIT, hInstance, NULL);

    CreateWindowEx(0, "BUTTON", "Start", WS_CHILD | WS_VISIBLE,
                   20, 60, 100, 30, hwnd, (HMENU)ID_START_BUTTON, hInstance, NULL);

    CreateWindowEx(0, "BUTTON", "Stop", WS_CHILD | WS_VISIBLE,
                   140, 60, 100, 30, hwnd, (HMENU)ID_STOP_BUTTON, hInstance, NULL);

    ShowWindow(hwnd, SW_SHOW);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}