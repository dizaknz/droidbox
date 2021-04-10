#ifndef _PADDLE_DROID_DISPLAY_HPP
#define _PADDLE_DROID_DISPLAY_HPP

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <android_native_app_glue.h>

#include "log.hpp"
#include "shader.hpp"

static const int32_t VERTEX_SIZE = sizeof(GLfloat) * 7;
static const int32_t POSITION_PARAMETER_INDEX = 0;
static const int32_t POSITION_NUM_ELEMENTS = 3;
static const int32_t COLOR_PARAMETER_INDEX = 1;
static const int32_t COLOR_NUM_ELEMENTS = 4;

class Display {
    private:
        EGLDisplay m_display;
        EGLSurface m_surface;
        EGLContext m_context;
        Shader m_vertexShader;
        Shader m_fragmentShader;
        int32_t m_programObject;
        float m_width;
        float m_height;
        bool m_active;

    public:
        int Init(android_app *);
        void Close();
        float ViewPortX(float x);
        float ViewPortY(float y);
        float X(float rawX);
        float Y(float rawY);
};

int Display::Init(android_app *app) {
    const EGLint attribs[] = {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_BLUE_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_RED_SIZE, 8,
        EGL_NONE
    };

    EGLint w, h, format;
    EGLint numConfigs;
    EGLConfig config;
    GLint linked;

    m_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(m_display, NULL, NULL);
    eglChooseConfig(m_display, attribs, &config, 1, &numConfigs);
    eglGetConfigAttrib(m_display, config, EGL_NATIVE_VISUAL_ID, &format);

    ANativeWindow_setBuffersGeometry(app->window, 0, 0, format);
    m_surface = eglCreateWindowSurface(m_display, config, app->window, NULL);

    EGLint contextAttribs[] = {
        EGL_CONTEXT_CLIENT_VERSION,
        2,
        EGL_NONE
    };
    m_context = eglCreateContext(m_display, config, NULL, contextAttribs);

    if (eglMakeCurrent(m_display, m_surface, m_surface, m_context) == EGL_FALSE) {
        LOGE("Unable to eglMakeCurrent");
        return -1;
    }

    eglQuerySurface(m_display, m_surface, EGL_WIDTH, &w);
    eglQuerySurface(m_display, m_surface, EGL_HEIGHT, &h);

    m_width = w;
    m_height = h;

    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    char vShaderStr[] =
        "attribute vec4 a_vPosition;   \n"
        "attribute vec4 a_vColor;      \n"
        "varying vec4 v_vColor;        \n"
        "void main()                   \n"
        "{                             \n"
        "   gl_Position = a_vPosition; \n"
        "    v_vColor = a_vColor;      \n"
        "}                             \n";

    char fShaderStr[] =
        "precision mediump float;      \n"
        "varying vec4 v_vColor;        \n"
        "void main()                   \n"
        "{                             \n"
        "  gl_FragColor = v_vColor;    \n"
        "}                             \n";

    // load the vertex/fragment shaders
    m_vertexShader.Load(vShaderStr, GL_VERTEX_SHADER);
    m_fragmentShader.Load(fShaderStr, GL_FRAGMENT_SHADER);
    if(!m_vertexShader.Valid() || !m_fragmentShader.Valid()) {
        LOGE("Failed to load shaders");
        return -1;
    }

    // program object
    m_programObject = glCreateProgram();
    if(m_programObject == 0) {
        LOGE("Failed to create progra");
        return -1;
    }

    // attach shaders to program and bind
    glAttachShader(m_programObject, m_vertexShader.Get());
    glAttachShader(m_programObject, m_fragmentShader.Get());
    glBindAttribLocation(m_programObject, POSITION_PARAMETER_INDEX, "a_vPosition");
    glBindAttribLocation(m_programObject, COLOR_PARAMETER_INDEX, "a_vColor");

    // link and validate
    glLinkProgram(m_programObject);
    glGetProgramiv(m_programObject, GL_LINK_STATUS, &linked);
    if(!linked) {
        GLint infoLen = 0;
        glGetProgramiv(m_programObject, GL_INFO_LOG_LENGTH, &infoLen);

        if(infoLen > 1) {
            char* infoLog = new char[infoLen];
            glGetProgramInfoLog(m_programObject, infoLen, NULL, infoLog);
            LOGE("Error linking program:\n%s\n", infoLog);

            delete[] infoLog;
        }
        glDeleteProgram(m_programObject);

        return -1;
    }
    m_active = true;
    return 0;
}

void Display::Close() {
	if (m_display != EGL_NO_DISPLAY) {
		eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		if (m_context != EGL_NO_CONTEXT) {
			eglDestroyContext(m_display, m_context);
		}
		if (m_surface != EGL_NO_SURFACE) {
			eglDestroySurface(m_display, m_surface);
		}
		eglTerminate(m_display);
	}
	m_display = EGL_NO_DISPLAY;
	m_context = EGL_NO_CONTEXT;
	m_surface = EGL_NO_SURFACE;
    m_vertexShader.Cleanup();
    m_fragmentShader.Cleanup();
}

float Display::ViewPortX(float x) {
    float min = -1.0;
    float max = 1.0;

    return -1 * (((max - min) * (1 - x)) + min);
}

float Display::ViewPortY(float y) {
    float min = -1.0;
    float max = 1.0;

    return ((max - min) * (1 - y)) + min;
}

float Display::X(float rawX) {
    return rawX / m_width;
}

float Display::Y(float rawY) {
    return rawY / m_height;
}

#endif
