#include <iostream>
#include <windows.h>
#include <commdlg.h>

#define IDD_DIALOG1 101 // 添加分号

// 对话框回调函数
INT_PTR CALLBACK DpiDialogProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static HWND hEdit;
    int dpi;

    switch (msg) {
        case WM_INITDIALOG:
            hEdit = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                                   10, 10, 100, 20, hwnd, NULL, GetModuleHandle(NULL), NULL);
            return TRUE;

        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK) {
                int length = GetWindowTextLength(hEdit) + 1; // 修改这里
                char* buffer = new char[length]; // 修改这里
                GetWindowText(hEdit, buffer, length); // 修改这里
                dpi = atoi(buffer); // 修改这里
                delete[] buffer; // 修改这里
                EndDialog(hwnd, dpi);
            } else if (LOWORD(wParam) == IDCANCEL) {
                EndDialog(hwnd, -1);
            }
            return TRUE;
    }
    return FALSE;
}

int main() {

    // 创建对话框并获取用户输入的DPI值
    INT_PTR result = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), NULL, DpiDialogProc);
    if (result != -1) {
        int dpi = static_cast<int>(result);

        // 修改系统的显示缩放DPI
        DEVMODE devMode;
        ZeroMemory(&devMode, sizeof(devMode));
        devMode.dmSize = sizeof(devMode);
        devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL | DM_DISPLAYFREQUENCY;
        devMode.dmBitsPerPel = dpi * 4; // 假设每个像素占用4字节（32位）
        devMode.dmPelsWidth = GetSystemMetrics(SM_CXSCREEN);
        devMode.dmPelsHeight = GetSystemMetrics(SM_CYSCREEN);
        devMode.dmDisplayFrequency = 60; // 假设刷新率为60Hz

        if (ChangeDisplaySettingsEx(NULL, &devMode, NULL, CDS_UPDATEREGISTRY, NULL) == DISP_CHANGE_SUCCESSFUL) {
            MessageBox(NULL, "DPI设置成功！", "提示", MB_OK);
        } else {
            MessageBox(NULL, "DPI设置失败！", "错误", MB_OK | MB_ICONERROR);
        }
    }

    return 0;
}