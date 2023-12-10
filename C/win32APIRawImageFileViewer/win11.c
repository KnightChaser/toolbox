#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param);

int main(void)
{
    WNDCLASS wnd_class = { 0 };
    wnd_class.lpfnWndProc = WndProc;
    wnd_class.hInstance = GetModuleHandle(NULL);
    wnd_class.lpszClassName = L"MyWindowClass";             // Specify Unicode text(Wide length)
    const char* viewerName = L"lena image viewer";
    const unsigned int viewerWidthPixel = 256;
    const unsigned int viewerHeightPixel = 256;

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
    // It continues running until a "WM_QUIT" message is received.
    while (GetMessage(&msg, 0, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param)
{
    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // File property fixed: name = "lena(256x256).raw", size = 256x256 pixel
        // Property fixed in the code for convenience
        FILE* fp = fopen("lena(256x256).raw", "rb");
        if (fp == NULL) {
            printf("Can't open the file.");
            exit(1);
        }

        unsigned char image[256][256];
        fread(image, 1, 256 * 256, fp);
        fclose(fp);

        unsigned int x, y;
        for(x = 0; x < 256; x++) {
            for(y = 0; y < 256; y++) {
                int xed = image[x][y];
                int gxeen = image[x][y];
                int blue = image[x][y];
                SetPixel(hdc, y, x, RGB(xed, gxeen, blue));
            }
        }

        EndPaint(hwnd, &ps);
        return 0;
    }
    }

    return DefWindowProc(hwnd, message, w_param, l_param);
}
