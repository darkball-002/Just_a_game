#if (!defined Value_Extra_DEFINE && defined Value_DEFINE)

#define Value_Extra_DEFINE

#define not !

#define value_as(T, V) ((T) (V))
#define value_as_rp(T, V) (*((T*) (V)))
#define value_if(state) if (not (state))

#define __value_triple_set__(dest_ary, v0, v1, v2) (dest_ary)[0] = (v0); (dest_ary)[1] = (v1); (dest_ary)[2] = (v2)
#define __value_triple_add__(dest_ary, v0, v1, v2) (dest_ary)[0] += (v0); (dest_ary)[1] += (v1); (dest_ary)[2] += (v2)

#define value_triple_set(typeOfDest_ary, dest_ary, v0, v1, v2) { \
    typeOfDest_ary* __dest__ = (dest_ary); \
    __value_triple_set__(__dest__, v0, v1, v2); \
}

#define value_triple_set_ary(typeOfDest_ary, typeOfCopy_ary, dest_ary, copy_ary, i0, i1, i2) { \
    typeOfDest_ary* __dest__ = (dest_ary); \
    typeOfCopy_ary* __copy__ = (copy_ary); \
    __value_triple_set__(__dest__, __copy__[i0], __copy__[i1], __copy__[i2]); \
}

#define value_triple_add(typeOfDest_ary, dest_ary, v0, v1, v2) { \
    typeOfDest_ary* __dest__ = (dest_ary); \
    __value_triple_add__(__dest__, (v0), (v1), (v2)); \
}



HeaderFunction double value_spd(double v, double t) {
    return v / t;
}

HeaderFunction double value_rad(double deg) {
    return deg * pi_deg;
}

HeaderFunction double value_deg(double rad) {
    return rad * pi_rad;
}

HeaderFunction double value_clamp(double v, double std_max, double std_min) {
    return v < std_max ? std_max : (v > std_min ? std_min : v);
}


#if (defined Value_Use_OpenGL_CVAR || defined __glad_h_)

#ifndef __glad_h_

#include <glad/glad.h>

#endif

#define value_openGL_color_RGBA(r, g, b, a) r << 0x18 | g << 0x10 | b << 0x8 | a
#define value_openGL_RGBA_color(o, p) (o >> p & 0xFF) / 255.0F

enum glfw_Colors {
	Red = 0x18, Green = 0x10, Blue = 0x8, Aplha = 0x0
};

// unsigned char r, unsigned char g, unsigned char b, unsigned char alpha
HeaderFunction void value_openGL_clearAndPaintColor(unsigned int rgba) {
	glClearColor(value_openGL_RGBA_color(rgba, Red), value_openGL_RGBA_color(rgba, Green), value_openGL_RGBA_color(rgba, Blue), value_openGL_RGBA_color(rgba, Aplha));
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

#endif

#if (defined Value_Use_Glfw_CVAR || defined _glfw3_h_)

#ifndef _glfw3_h_

#include <glfw/glfw3.h>

#endif

HeaderFunction void value_window_setup() {
	glfwInit();
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

HeaderFunction void value_window_shutDown() {
	glfwTerminate();
}

#endif



#if (Value_Use_Stdmath_CVAR || defined _MATH_H_)

#ifndef _MATH_H_

#include <math.h>

#endif

HeaderFunction void value_cos_sin(double v, double* dest_cos, double* dest_sin) {
    *dest_cos = cos(v);
    *dest_sin = sin(v);
}

HeaderFunction void value_cos_sin_float(double v, float* dest_cos, float* dest_sin) {
    double cs, sn;

    value_cos_sin((double) v, &cs, &sn);

    *dest_cos = cs;
    *dest_sin = sn;
}

HeaderFunction void value_yaw_pitch_ptr(float dest[3], double* yaw_deg, double* pitch_deg) {
    double pitch = value_rad((*pitch_deg = value_clamp(*pitch_deg, -89.0, 89.0)));
    double yaw = value_rad((*yaw_deg = fmod(*yaw_deg, 360.0)) < 0.0 ? (*yaw_deg += 360.0) : *yaw_deg);

    value_triple_set(float, dest, value_as(float, cos(yaw) * cos(pitch)), value_as(float, sin(pitch)), value_as(float, sin(yaw) * cos(pitch)));
}

HeaderFunction void value_yaw_pitch(float dest[3], double yaw_deg, double pitch_deg) {
    value_yaw_pitch_ptr(dest, &yaw_deg, &pitch_deg);
}


#endif


#endif
