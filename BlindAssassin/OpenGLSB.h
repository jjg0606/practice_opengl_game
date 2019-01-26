////////////////////////////////////////////////
// Here, we will try to isolate as many platform
// dependencies here as possible so that all sample
// programs contain as few headers and are as self
// contained as possible.

// Windows... Visual C++
#ifdef _WIN32
// Standard Windows includes
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
//#include "glext.h"
//#include "WGLEXT.H"
#endif

// Mac OS X
#ifdef __APPLE__
#include <Carbon/Carbon.h>
#include <GLUT/glut.h>
//#include <OpenGL/glext.h>
#include "glext.h"

//#define APIENTRY
//#define INT_PTR int*
#define Sleep(x)	


#endif