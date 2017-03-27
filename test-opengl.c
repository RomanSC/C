/* test-opengl.c | Wed, Mar 20, 2017 | Roman S. Collins
*/

#define GL_GLEXT_PROTOTYPES
#define GL_GLXEXT_PROTOTYPES

// Standard libs
#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h> // OpenGL
#include <GL/glu.h> // Utilities
#include <GL/glx.h>
//#include <GL/glew.h> // Maths
//#include <GL/glfw.h> // Windowing, input, and sound

// include SDL to assist in setting context
/* #include <SDL2/SDL.h> */

#include <X11/Xlib.h>

// Obsolete so provided explicitly
// http://wili.cc/blog/ogl3-glx.html
#include "GL/glxext.h"
#include "GL/glext.h"

int main( void ) {
    char window_title[] = "test-opengl.c";

    Display * d_dpy;
    Window d_win;
    GLXContext d_ctx;

    const char * display = ":0";

    int width = 800;
    int height = 600;

    if (!(d_dpy = XOpenDisplay(display))) {
        throw std::string("Could not open display.");
    }

    int attr[] = {
        GLX_RGBA,
        GLX_RED_SIZE, 1,
        GLX_GREEN_SIZE, 1,
        GLX_BLUE_SIZE, 1,
        GLX_DOUBLEBUFFER,
        GLX_DEPTH_SIZE, 1,
        None
    };

    int scrnum = DefaultScreen(d_dpy);
    Window root = RootWindow(d_dpy, scrnum);

    int elemc;
    GLXFBConfig *fbcfg = glXChooseFBConfig(d_dpy, scrnum, NULL, &elemc);
    if (!fbcfg)
        throw std::string("Couldn't get FB configs\n");
    else
        printf("Got %d FB configs\n", elemc);

    XVisualInfo *visinfo = glXChooseVisual(d_dpy, scrnum, attr);

    if (!visinfo)
        throw std::string("Couldn't get a visual\n");

    // Window parameters
    XSetWindowAttributes winattr;
    winattr.background_pixel = 0;
    winattr.border_pixel = 0;
    winattr.colormap = XCreateColormap(d_dpy, root, visinfo->visual, AllocNone);
    winattr.event_mask = StructureNotifyMask | ExposureMask | KeyPressMask;
    unsigned long mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;

    printf("Window depth %d, w %d h %d\n", visinfo->depth, width, height);
    d_win = XCreateWindow(d_dpy, root, 0, 0, width, height, 0,
            visinfo->depth, InputOutput, visinfo->visual, mask, &winattr);

    // OpenGL 3.2
    int gl3attr[] = {
        GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
        GLX_CONTEXT_MINOR_VERSION_ARB, 2,
        GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
        None
    };

    d_ctx = glXCreateContextAttribsARB(d_dpy, fbcfg[0], NULL, true, gl3attr);

    XFree(visinfo);

    XMapWindow(d_dpy, d_win);
    glXMakeCurrent(d_dpy, d_win, d_ctx);

    printf("OpenGL:\n\tvendor %s\n\trenderer %s\n\tversion %s\n\tshader language %s\n\n",
            glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION),
            glGetString(GL_SHADING_LANGUAGE_VERSION));

    int extCount;
    glGetIntegerv(GL_NUM_EXTENSIONS, &extCount);
    for (int i = 0; i < extCount; ++i)
        printf("Extension %d/%d: %s\n", i+1, extCount, glGetStringi(GL_EXTENSIONS, i));

    glViewport(0, 0, width, height);

    return 0;
}
