#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <stdio.h>

// Code for bitblit painting:
struct
{
    int width;
    int height;
    UINT32 * pixels;
} frame = {0};

static BOOL quit = false;
static BITMAPINFO frame_bitmap_info;
static HBITMAP frame_bitmap = 0;
static HDC frame_device_context = 0;

#if RAND_MAX == 32767
#define Rand32() ((rand() << 16) + (rand() << 1) + (rand() & 1))
#else
#define Rand32() rand()
#endif

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lparam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    const wchar_t WND_CLASS_NAME[] = L"Sample Window Class";
    WNDCLASS wnd_class = {};
   
    wnd_class.lpfnWndProc = WindowProc;
    wnd_class.hInstance = hInstance;
    wnd_class.lpszClassName = WND_CLASS_NAME; 

    RegisterClass(&wnd_class);

    frame_bitmap_info.bmiHeader.biSize = sizeof(frame_bitmap_info.bmiHeader);
    frame_bitmap_info.bmiHeader.biPlanes = 1;
    frame_bitmap_info.bmiHeader.biBitCount = 32;
    frame_bitmap_info.bmiHeader.biCompression = BI_RGB;
    frame_device_context = CreateCompatibleDC(0);

    HWND hwnd = CreateWindowEx(
        0,
        WND_CLASS_NAME,
        L"Learn to Program Windows",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL);

    if(hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    while(!quit)
    {
        
        MSG msg = {};
        while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            //TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        //static unsigned int p = 0;
        //frame.pixels[(p++)%(frame.width*frame.height)] = Rand32();
        //frame.pixels[Rand32()%(frame.width*frame.height)] = 0;

        //for(int j = 0; j < frame.height; ++j)
        //{
        //    for(int i = 0; i < frame.width; ++ i)
        //    {
        //        auto r = double(i) / (frame.width - 1);
        //        auto g = double(j) / (frame.height - 1);
        //        auto b = 0;
        //
        //        auto ir = static_cast<int>(255.999 * r);
        //        auto ig = static_cast<int>(255.999 * g);
        //        auto ib = static_cast<int>(255.999 * b);
        //    }
        //}

        for(int j = 0; j < frame.height; ++j)
        {
            for(int i = 0; i < frame.width; ++i)
            {
                auto r = double(i) / (frame.width - 1);
                auto g = double(j) / (frame.height - 1);
                auto b = 0;

                auto ir = static_cast<UINT32>(255.999 * r) << 16;
                //printf("red: 0x%08x\n", ir);
                auto ig = static_cast<UINT32>(255.999 * g) << 8;
                //printf("green: 0x%08x\n", ig);
                auto ib = static_cast<UINT32>(255.999 * b);
                //printf("blue: 0x%08x\n", ib);
                auto color = ir | ig | ib;
                //printf("Color: 0x%08x\n", color);
                frame.pixels[(j * frame.width) + i] = color;
            }
        }
        frame.pixels[(100 * frame.width) + 100] = 0;
        InvalidateRect(hwnd, NULL, FALSE);
        UpdateWindow(hwnd);
    }
    return 0;
}



LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_QUIT:
        case WM_DESTROY:
            quit = true;
            break;
        case WM_PAINT:
        {
            static PAINTSTRUCT paint;
            static HDC device_context;
            device_context = BeginPaint(hwnd, &paint);
            BitBlt(device_context,
                paint.rcPaint.left,
                paint.rcPaint.top,
                paint.rcPaint.right - paint.rcPaint.left,
                paint.rcPaint.bottom - paint.rcPaint.top,
                frame_device_context,
                paint.rcPaint.left,
                paint.rcPaint.top,
                SRCCOPY);
            EndPaint(hwnd, &paint);
        }
            break;
        case WM_SIZE:
        {
            frame_bitmap_info.bmiHeader.biWidth = LOWORD(lParam);
            frame_bitmap_info.bmiHeader.biHeight = HIWORD(lParam);

            if(frame_bitmap) DeleteObject(frame_bitmap);
            frame_bitmap = CreateDIBSection(NULL,
                                        &frame_bitmap_info,
                                        DIB_RGB_COLORS,
                                        (void**)&frame.pixels,
                                        0, 0);
            SelectObject(frame_device_context, frame_bitmap);
            frame.width = LOWORD(lParam);
            frame.height = HIWORD(lParam);
        }
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
            break;
    }
    return 0;
}