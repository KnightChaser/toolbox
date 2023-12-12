#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param);

static const wchar_t* viewerName = L"lena image viewer"; // Use wchar_t for Unicode strings
static const unsigned int viewerWidthPixel = 256;
static const unsigned int viewerHeightPixel = 256;
static const char* filepath = "lena(256x256).raw";
static const unsigned int imageWidthPixel = 256;
static const unsigned int imageHeightPixel = 256;

int main(void) {
    WNDCLASS wnd_class = { 0 };
    wnd_class.lpfnWndProc = WndProc;
    wnd_class.hInstance = GetModuleHandle(NULL);
    wnd_class.lpszClassName = L"MyWindowClass"; // Use L prefix for Unicode string

    if (!RegisterClass(&wnd_class))
        return -1;

    HWND hwnd = CreateWindowEx(WS_EX_LEFT,                  // dwExStyle
                                wnd_class.lpszClassName,    // lpClassName
                                viewerName,                 // lpWindowName
                                WS_OVERLAPPEDWINDOW,        // dwStyle
                                CW_USEDEFAULT,              // X
                                CW_USEDEFAULT,              // Y
                                viewerWidthPixel,           // nWidth
                                viewerHeightPixel,          // nHeight
                                0,                          // hWndParent
                                0,                          // hMenu
                                GetModuleHandle(NULL),      // hInstance
                                0);                         // lpParam

    if (!hwnd)
        return -1;

    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, 0, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param) {

    switch (message) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            FILE* fp = fopen(filepath, "rb");
            if (fp == NULL) {
                printf("Can't open the file.");
                exit(1);
            }

            unsigned char* image = (unsigned char*)malloc(imageHeightPixel * imageWidthPixel);
            if (image == NULL) {
                fclose(fp);
                return -1;
            }

            fread(image, 1, imageHeightPixel * imageWidthPixel, fp);
            fclose(fp);

            unsigned int x, y;
            for (x = 0; x < imageWidthPixel; x++) {
                for (y = 0; y < imageHeightPixel; y++) {
                    int pixelValue = image[x * imageWidthPixel + y];
                    SetPixel(hdc, y, x, RGB(pixelValue, pixelValue, pixelValue));
                }
            }

            free(image);

            EndPaint(hwnd, &ps);
            return 0;
        }
    }

    return DefWindowProc(hwnd, message, w_param, l_param);
}
