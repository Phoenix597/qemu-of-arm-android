#include <stdio.h>
#include <stdlib.h>
#include "EGLDispatch.h"
#include "osDynLibrary.h"

EGLDispatch s_egl;

bool init_egl_dispatch()
{
    osUtils::dynLibrary *lib = osUtils::dynLibrary::open("/vendor/lib64/egl/libEGL_mtk.so");
    if (!lib) return NULL;

    s_egl.eglGetError = (eglGetError_t) lib->findSymbol("eglGetError");
    s_egl.eglGetDisplay = (eglGetDisplay_t) lib->findSymbol("eglGetDisplay");
    s_egl.eglInitialize = (eglInitialize_t) lib->findSymbol("eglInitialize");
    s_egl.eglTerminate = (eglTerminate_t) lib->findSymbol("eglTerminate");
    s_egl.eglQueryString = (eglQueryString_t) lib->findSymbol("eglQueryString");
    s_egl.eglGetConfigs = (eglGetConfigs_t) lib->findSymbol("eglGetConfigs");
    s_egl.eglChooseConfig = (eglChooseConfig_t) lib->findSymbol("eglChooseConfig");
    s_egl.eglGetConfigAttrib = (eglGetConfigAttrib_t) lib->findSymbol("eglGetConfigAttrib");
    s_egl.eglCreateWindowSurface = (eglCreateWindowSurface_t) lib->findSymbol("eglCreateWindowSurface");
    s_egl.eglCreatePbufferSurface = (eglCreatePbufferSurface_t) lib->findSymbol("eglCreatePbufferSurface");
    s_egl.eglCreatePixmapSurface = (eglCreatePixmapSurface_t) lib->findSymbol("eglCreatePixmapSurface");
    s_egl.eglDestroySurface = (eglDestroySurface_t) lib->findSymbol("eglDestroySurface");
    s_egl.eglQuerySurface = (eglQuerySurface_t) lib->findSymbol("eglQuerySurface");
    s_egl.eglBindAPI = (eglBindAPI_t) lib->findSymbol("eglBindAPI");
    s_egl.eglQueryAPI = (eglQueryAPI_t) lib->findSymbol("eglQueryAPI");
    s_egl.eglWaitClient = (eglWaitClient_t) lib->findSymbol("eglWaitClient");
    s_egl.eglReleaseThread = (eglReleaseThread_t) lib->findSymbol("eglReleaseThread");
    s_egl.eglCreatePbufferFromClientBuffer = (eglCreatePbufferFromClientBuffer_t) lib->findSymbol("eglCreatePbufferFromClientBuffer");
    s_egl.eglSurfaceAttrib = (eglSurfaceAttrib_t) lib->findSymbol("eglSurfaceAttrib");
    s_egl.eglBindTexImage = (eglBindTexImage_t) lib->findSymbol("eglBindTexImage");
    s_egl.eglReleaseTexImage = (eglReleaseTexImage_t) lib->findSymbol("eglReleaseTexImage");
    s_egl.eglSwapInterval = (eglSwapInterval_t) lib->findSymbol("eglSwapInterval");
    s_egl.eglCreateContext = (eglCreateContext_t) lib->findSymbol("eglCreateContext");
    s_egl.eglDestroyContext = (eglDestroyContext_t) lib->findSymbol("eglDestroyContext");
    s_egl.eglMakeCurrent = (eglMakeCurrent_t) lib->findSymbol("eglMakeCurrent");
    s_egl.eglGetCurrentContext = (eglGetCurrentContext_t) lib->findSymbol("eglGetCurrentContext");
    s_egl.eglGetCurrentSurface = (eglGetCurrentSurface_t) lib->findSymbol("eglGetCurrentSurface");
    s_egl.eglGetCurrentDisplay = (eglGetCurrentDisplay_t) lib->findSymbol("eglGetCurrentDisplay");
    s_egl.eglQueryContext = (eglQueryContext_t) lib->findSymbol("eglQueryContext");
    s_egl.eglWaitGL = (eglWaitGL_t) lib->findSymbol("eglWaitGL");
    s_egl.eglWaitNative = (eglWaitNative_t) lib->findSymbol("eglWaitNative");
    s_egl.eglSwapBuffers = (eglSwapBuffers_t) lib->findSymbol("eglSwapBuffers");
    s_egl.eglCopyBuffers = (eglCopyBuffers_t) lib->findSymbol("eglCopyBuffers");
    s_egl.eglGetProcAddress = (eglGetProcAddress_t) lib->findSymbol("eglGetProcAddress");

#define INIT_EGL_EXT_FUNC(name) \
    if (s_egl.eglGetProcAddress) s_egl.name = (name ## _t) s_egl.eglGetProcAddress(#name); \
    if (!s_egl.name || !s_egl.eglGetProcAddress) s_egl.name = (name ## _t) lib->findSymbol(#name)

    INIT_EGL_EXT_FUNC(eglLockSurfaceKHR);
    INIT_EGL_EXT_FUNC(eglUnlockSurfaceKHR);
    INIT_EGL_EXT_FUNC(eglCreateImageKHR);
    INIT_EGL_EXT_FUNC(eglDestroyImageKHR);
    INIT_EGL_EXT_FUNC(eglCreateSyncKHR);
    INIT_EGL_EXT_FUNC(eglDestroySyncKHR);
    INIT_EGL_EXT_FUNC(eglClientWaitSyncKHR);
    INIT_EGL_EXT_FUNC(eglSignalSyncKHR);
    INIT_EGL_EXT_FUNC(eglGetSyncAttribKHR);
    INIT_EGL_EXT_FUNC(eglSetSwapRectangleANDROID);

    return true;
}
