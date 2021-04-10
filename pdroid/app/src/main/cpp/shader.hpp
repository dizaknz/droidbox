#ifndef _PADDLE_DROID_SHADER_HPP
#define _PADDLE_DROID_SHADER_HPP 

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

class Shader {
    private:
       GLuint m_shader;
       bool m_valid;
    public:
        void Load(const char *shaderSrc, GLenum type);
        void Cleanup();
        GLuint Get() { return m_shader; }
        bool Valid() { return m_valid; }
};

void Shader::Load(const char *shaderSrc, GLenum type) {
    GLint compiled;

    m_shader = glCreateShader(type);
    if(m_shader != 0) {
        glShaderSource(m_shader, 1, &shaderSrc, NULL);
        glCompileShader(m_shader);
        glGetShaderiv(m_shader, GL_COMPILE_STATUS, &compiled);

        if(!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &infoLen);

            if(infoLen > 1) {
                char* infoLog = new char[infoLen];
                glGetShaderInfoLog(m_shader, infoLen, NULL, infoLog);
                LOGW("Error compiling shader:\n%s\n", infoLog);
                delete[] infoLog;
            }
            Cleanup();
        }
        m_valid = true;
    }
    return;
}

void Shader::Cleanup() {
    glDeleteShader(m_shader);
    m_shader = 0;
    m_valid = false;
}

#endif
