#include <iostream>
#include <windows.h>
#include <commdlg.h>

#define IDD_DIALOG1 101 // ��ӷֺ�

// �Ի���ص�����
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
                int length = GetWindowTextLength(hEdit) + 1; // �޸�����
                char* buffer = new char[length]; // �޸�����
                GetWindowText(hEdit, buffer, length); // �޸�����
                dpi = atoi(buffer); // �޸�����
                delete[] buffer; // �޸�����
                EndDialog(hwnd, dpi);
            } else if (LOWORD(wParam) == IDCANCEL) {
                EndDialog(hwnd, -1);
            }
            return TRUE;
    }
    return FALSE;
}

int main() {

    // �����Ի��򲢻�ȡ�û������DPIֵ
    INT_PTR result = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), NULL, DpiDialogProc);
    if (result != -1) {
        int dpi = static_cast<int>(result);

        // �޸�ϵͳ����ʾ����DPI
        DEVMODE devMode;
        ZeroMemory(&devMode, sizeof(devMode));
        devMode.dmSize = sizeof(devMode);
        devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL | DM_DISPLAYFREQUENCY;
        devMode.dmBitsPerPel = dpi * 4; // ����ÿ������ռ��4�ֽڣ�32λ��
        devMode.dmPelsWidth = GetSystemMetrics(SM_CXSCREEN);
        devMode.dmPelsHeight = GetSystemMetrics(SM_CYSCREEN);
        devMode.dmDisplayFrequency = 60; // ����ˢ����Ϊ60Hz

        if (ChangeDisplaySettingsEx(NULL, &devMode, NULL, CDS_UPDATEREGISTRY, NULL) == DISP_CHANGE_SUCCESSFUL) {
            MessageBox(NULL, "DPI���óɹ���", "��ʾ", MB_OK);
        } else {
            MessageBox(NULL, "DPI����ʧ�ܣ�", "����", MB_OK | MB_ICONERROR);
        }
    }

    return 0;
}
