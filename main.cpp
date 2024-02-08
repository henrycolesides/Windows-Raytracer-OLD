#ifndef UNICODE
#define UNICODE
#endif

#include <cmath>
#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <windows.h>

#include "vec3.h"
#include "color.h"
#include "shapes.h"

int WIDTH = 480;
int HEIGHT = 480;

const float VWIDTH = 1.0;
const float VHEIGHT = 1.0;
const float VDISTANCE = 1.0;
const float VZ = 1.0;

struct
{
    int width;
    int height;
    UINT32 * pixels;
} frame = {0};

inline int ScreenCoordX(int cx) {return (frame.width / 2) + cx;}
inline int ScreenCoordY(int cy) {return (frame.height / 2) + cy;}

inline float ViewportCoordX(int cx) {return ((float)cx) * (VWIDTH/(float)frame.width);}
inline float ViewportCoordY(int cy) {return ((float)cy) * (VHEIGHT/(float)frame.height);}

// Ray equation:
// Point P = O + t(V - O)
// P = O + tD (direction vector)
// VZ == VDISTANCE (Can be substituted for now)

UINT32 TraceRay(Vec3 & O, Vec3 & D, float t_min, float t_max);

static BOOL quit = false;
static BITMAPINFO frame_bitmap_info;
static HBITMAP frame_bitmap = 0;
static HDC frame_device_context = 0;

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

    //printf("Dot test: %f\n", Dot(coordinate_t{10, 20, 30}, {40, 50, 60}));
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

    SetWindowPos(hwnd, HWND_TOP, 0, 0, WIDTH, HEIGHT, SWP_NOOWNERZORDER);
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

        // Raytracing begins here!

        Vec3 O = Vec3(0.0, 0.0, 0.0);
        Vec3 D = Vec3(0.0, 0.0, VDISTANCE);
        uint32_t color = INT_MAX;
        for(int j = -(frame.height/2); j < (frame.height/2); ++j)
        {
            for(int i = -(frame.width/2); i < (frame.width/2); ++i)
            {
                int x = ScreenCoordX(i);
                int y = ScreenCoordY(j);

                try
                {
                    D.set(X, ViewportCoordX(i));
                    D.set(Y, ViewportCoordY(j));                
                    color = TraceRay(O, D, 1, __FLT_MAX__);
                    frame.pixels[(y * frame.width) + x] = color; 
                }
                catch(bool success)
                {
                    if(!success) 
                    {
                        std::cerr << "Error: attempt to assign invalid dimension\n";
                    }
                }
                
                //if(x == 0) printf("(%d, %d)\n", ScreenCoordX(x), ScreenCoordY(y));
                //auto r = double(x) / (frame.width - 1);
                //auto g = double(y) / (frame.height - 1);
                //auto b = 0;
                //
                //auto ir = static_cast<UINT32>(255.999 * r);// << 16;
                ////printf("red: 0x%08x\n", ir);
                //auto ig = static_cast<UINT32>(255.999 * g);// << 8;
                ////printf("green: 0x%08x\n", ig);
                //auto ib = static_cast<UINT32>(255.999 * b);
                //
                //frame.pixels[(y * frame.width) + x] = MapColor(ir, ig, ib);
            }   //
        }
       //frame.pixels[(300 * frame.width) + 100] = 0;
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
                0, //paint.rcPaint.left,
                0, //paint.rcPaint.top,
                paint.rcPaint.right - paint.rcPaint.left,
                paint.rcPaint.bottom - paint.rcPaint.top,
                frame_device_context,
                0, //paint.rcPaint.left,
                0, //paint.rcPaint.top,
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
            WIDTH = LOWORD(lParam);
            HEIGHT = HIWORD(lParam);
        }
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
            break;
    }
    return 0;
}

// Ray equation:
// Point P = O + t(V - O)
// P = O + tD (direction vector)
// VZ == VDISTANCE (Can be substituted for now)

// Sphere equation: (P-C) * (dot) (P-C) = r^2
// Where: C is center of sphere
//        R is radius of spehre
//        P is point we are checking

uint32_t TraceRay(Vec3 & O, Vec3 & D, float t_min, float t_max)
{
    float closest_t = __FLT_MAX__;

    Sphere * closest_sphere = nullptr;
    Sphere spheres[3] = {Sphere(Vec3(0.0, -1.0, 3.0), 1.0, Color(255, 0, 0)),
                        Sphere(Vec3(2.0, 0.0, 4.0), 1.0, Color(0, 0, 255)),
                        Sphere(Vec3(-2.0, 0, 4.0), 1.0, Color(0, 255, 0))};
    for(int i = 0; i < 3; ++i)
    { 
        Vec3 ts = spheres[i].intersect_ray(O, D);

        if(ts.get(X) >= t_min && ts.get(X) < t_max && ts.get(X) < closest_t)
        {
            closest_t = ts.get(X);
            closest_sphere = &spheres[i];
        }

        if(ts.get(Y) >= t_min && ts.get(Y) < t_max && ts.get(Y) < closest_t)
        {
            closest_t = ts.get(Y);
            closest_sphere = &spheres[i];
        }
    }
    if(!closest_sphere) return INT_MAX;
    else return closest_sphere->map_color();
}