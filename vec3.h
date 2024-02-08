// vec3.h for defining operations on a 3d vector

#ifndef VEC3_H
#define VEC3_H

#define X 'x'
#define Y 'y'
#define Z 'z'

class Vec3 
{
    public:
        Vec3();
        Vec3(const float x, const float y, const float z);

        // Dot product
        float operator*(const Vec3 & op2);

        // Scalar members
        Vec3 & operator*=(const float op2);
        Vec3 & operator/=(const float op2);

        Vec3 operator+(const Vec3 & op2);
        Vec3 & operator+=(const Vec3 & op2);
        Vec3 operator-(const Vec3 & op2);
        Vec3 & operator-=(const Vec3 & op2);

        bool operator==(const Vec3 & op2);
        bool operator!=(const Vec3 & op2); 

        // Scalar friends
        friend Vec3 operator*(const Vec3 & op1, const float op2);
        friend Vec3 operator*(const float op1, const Vec3 & op2);
        friend Vec3 operator/(const Vec3 & op1, const float op2);
        friend Vec3 operator/(const float op1, const Vec3 & op2);

        void set(const char dimension, const float value);
        float get(const char dimension);

        float values[3];
};

#endif

//coordinate_t D = {0, 0, VDISTANCE};
//        UINT32 color = 0;
//        for(int j = -(frame.height/2); j < (frame.height/2); ++j)
//        {
//            for(int i = -(frame.width/2); i < (frame.width/2); ++i)
//            {
//                int x = ScreenCoordX(i);
//                int y = ScreenCoordY(j);
//                D.x = ViewportCoordX(i);
//                D.y = ViewportCoordY(j);
//                color = TraceRay(O, D, 1, 1000000.0);
//                //if(x == 0) printf("(%d, %d)\n", ScreenCoordX(x), ScreenCoordY(y));
//                frame.pixels[(y * frame.width) + x] = color;    // Crashes here
//                //auto r = double(x) / (frame.width - 1);
//                //auto g = double(y) / (frame.height - 1);
//                //auto b = 0;
//                //
//                //auto ir = static_cast<UINT32>(255.999 * r);// << 16;
//                ////printf("red: 0x%08x\n", ir);
//                //auto ig = static_cast<UINT32>(255.999 * g);// << 8;
//                ////printf("green: 0x%08x\n", ig);
//                //auto ib = static_cast<UINT32>(255.999 * b);
//                //
//                //frame.pixels[(y * frame.width) + x] = MapColor(ir, ig, ib);
//            }   //
//        }

 //   Vec3 D = Vec3(0, 0, 0);
 //   UINT32 color = 0;
 //   for(int j = -(frame.height/2); j < (frame.height/2); ++j)
 //   {
 //      for(int i = -(frame.width/2); i < (frame.width/2); ++i)
 //      {
 //          int x = ScreenCoordX(i);    // x equals the corresponding screen coord of canvas coord i
 //
 //      }
 //   }