#ifndef UNICODE
#define UNICODE
#endif

#include <cmath>
#include <windows.h>
#include <stdio.h>

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

struct coordinate_s
{
    float x;
    float y;
    float z;
} typedef coordinate_t;

struct color_s
{
    UINT32 r;
    UINT32 g;
    UINT32 b;
} typedef color_t;

struct sphere_s
{
    coordinate_t c;
    color_t color;
    float r;
} typedef sphere_t;

static coordinate_t O = {0.0, 0.0, 0.0};
static coordinate_t cam = {0.0, 0.0, 0.0};

inline int ScreenCoordX(int cx) {return (frame.width / 2) + cx;}
inline int ScreenCoordY(int cy) {return (frame.height / 2) + cy;}
inline UINT32 MapColor(UINT32 r, UINT32 g, UINT32 b) {return (r << 16) | (g << 8) | (b);}

inline float ViewportCoordX(int cx) {return ((float)cx) * (VWIDTH/(float)frame.width);}
inline float ViewportCoordY(int cy) {return ((float)cy) * (VHEIGHT/(float)frame.height);}

inline float Dot(coordinate_t op1, coordinate_t op2) {return (op1.x * op2.x) + (op1.y * op2.y) + (op1.z * op2.z);}

// Ray equation:
// Point P = O + t(V - O)
// P = O + tD (direction vector)
// VZ == VDISTANCE (Can be substituted for now)

UINT32 TraceRay(coordinate_t O, coordinate_t D, float t_min, float t_max);
coordinate_t IntersectRaySphere( coordinate_t O, coordinate_t D, sphere_t sphere);
coordinate_t GetRayPoint(UINT32, coordinate_t);
//inline coordinate_t GetRayPoint(UINT32 t, coordinate_t V) {return }
// Code for bitblit painting:

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

    SetWindowPos(hwnd, HWND_TOP, 800, 300, WIDTH, HEIGHT, SWP_NOOWNERZORDER);
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

        //for(int j = 1; j < frame.height; ++j)
        //{
        //    for(int i = 0; i < frame.width; ++i)
        //    {
        //        auto r = double(i) / (frame.width - 1);
        //        auto g = double(j) / (frame.height - 1);
        //        auto b = 0;
        //
        //        auto ir = static_cast<UINT32>(255.999 * r);// << 16;
        //        //printf("red: 0x%08x\n", ir);
        //        auto ig = static_cast<UINT32>(255.999 * g);// << 8;
        //        //printf("green: 0x%08x\n", ig);
        //        auto ib = static_cast<UINT32>(255.999 * b);
        //        //printf("blue: 0x%08x\n", ib);
        //        //auto color = ir | ig | ib;
        //        //printf("Color: 0x%08x\n", color);
        //        //frame.pixels[(j * frame.width) + i] = color;
        //        frame.pixels[(j * frame.width) + i] = MapColor(ir, ig, ib);
        //    }
        //}
        //printf("Screen: (%d, %d)\n", frame.width, frame.height);
        //printf("Canvas: (%d, %d)\n", frame.width/2, frame.height/2);
        coordinate_t D = {0, 0, VDISTANCE};
        UINT32 color = 0;
        for(int j = -(frame.height/2); j < (frame.height/2); ++j)
        {
            for(int i = -(frame.width/2); i < (frame.width/2); ++i)
            {
                int x = ScreenCoordX(i);
                int y = ScreenCoordY(j);
                D.x = ViewportCoordX(i);
                D.y = ViewportCoordY(j);
                color = TraceRay(O, D, 1, 1000000.0);
                //if(x == 0) printf("(%d, %d)\n", ScreenCoordX(x), ScreenCoordY(y));
                frame.pixels[(y * frame.width) + x] = color;    // Crashes here
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
coordinate_t GetRayPoint(UINT32 t, coordinate_t V)
{
    coordinate_t P = {0, 0, 0};
    P.x = O.x + (t * (V.x - O.x));
    P.y = O.y + (t * (V.y - O.y));
    P.x = O.z + (t * (V.z - O.z));
    return P;
}

// Sphere equation: (P-C) * (dot) (P-C) = r^2
// Where: C is center of sphere
//        R is radius of spehre
//        P is point we are checking

UINT32 TraceRay(coordinate_t O, coordinate_t D, float t_min, float t_max)
{
    float closest_t = 1000000.0;
   // sphere_t closest_sphere = {{NULL, NULL, NULL}, {NULL, NULL, NULL}, NULL};
    sphere_t * closest_sphere = NULL;
    sphere_t the_sphere = {{0.0, -1.0, 3.0}, {255, 0, 0}, 1.0};
    coordinate_t ts = IntersectRaySphere(O, D, the_sphere);
    if(ts.x >= t_min && ts.x < t_max && ts.x < closest_t)
    {
 //       printf("Sphere found!\n");
        closest_t = ts.x;
        closest_sphere = &the_sphere;
    }

    if(ts.y >= t_min && ts.y < t_max && ts.y < closest_t)
    {
//        printf("Sphere found!\n");
        closest_t = ts.y;
        closest_sphere = &the_sphere;
    }

    if(!closest_sphere)
    {
        return 0;
    }
    else
    {
        return MapColor(closest_sphere->color.r, closest_sphere->color.g, closest_sphere->color.b);
    }
}

coordinate_t IntersectRaySphere( coordinate_t O, coordinate_t D, sphere_t sphere)
{
    float r = sphere.r;
    coordinate_t CO = {O.x - sphere.c.x, O.y - sphere.c.y, O.z - sphere.c.z};

    float a = Dot(D, D);
    float b = 2 * Dot(CO, D);
    float c = Dot(CO, CO) - (sphere.r * sphere.r);

    float discriminant = (b * b) - (4 * a * c);
    if(discriminant < 0.0)
    {
        return {1000000.0, 1000000.0, 0.0};
    }

    float t1 = (-b + std::sqrt(discriminant)) / (2 * a);
    float t2 = (-b - std::sqrt(discriminant)) / (2 * a);
    return {t1, t2, 0.0};
}