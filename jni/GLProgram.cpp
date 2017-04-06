//
// Created by kintai on 17-4-6.
//

#include "GLProgram.h"
#include "FutureLog.h"

GLProgram::GLProgram()
{
}

GLProgram::~GLProgram()
{
}

bool GLProgram::initWithVertexShaderByteArray(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray)
{
    _uVertShader = loadShader(GL_VERTEX_SHADER, vShaderByteArray);
    if (!_uVertShader) {
        return false;
    }

    _uFragShader = loadShader(GL_FRAGMENT_SHADER, fShaderByteArray);
    if (!_uFragShader) {
        return false;
    }

    _uProgram = glCreateProgram();
    if (!_uProgram) {
        return false;
    }

    glAttachShader(_uProgram, _uVertShader);
    checkGlError("glAttachShader");
    glAttachShader(_uProgram, _uFragShader);
    checkGlError("glAttachShader");

    return true;
}

bool GLProgram::link()
{
    glLinkProgram(_uProgram);

    GLint linkStatus = GL_FALSE;
    glGetProgramiv(_uProgram, GL_LINK_STATUS, &linkStatus);
    if (linkStatus != GL_TRUE) {
        GLint bufLength = 0;
        glGetProgramiv(_uProgram, GL_INFO_LOG_LENGTH, &bufLength);
        if (bufLength) {
            char* buf = (char*) malloc(bufLength);
            if (buf) {
                glGetProgramInfoLog(_uProgram, bufLength, NULL, buf);
                LOGE("Could not link _uProgram:\n%s\n", buf);
                free(buf);
            }
        }
        glDeleteProgram(_uProgram);
        _uProgram = 0;

        return false;
    }
    return true;
}

void GLProgram::use()
{
    glUseProgram(_uProgram);
    checkGlError("glUseProgram");
}

GLuint GLProgram::loadShader(GLenum shaderType, const char* shaderSrc)
{
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        glShaderSource(shader, 1, &shaderSrc, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled); // check compile information
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char* infoLog = (char*) malloc(infoLen);
                if (infoLog) {
                    glGetShaderInfoLog(shader, infoLen, NULL, infoLog); // seek infor log
                    LOGE("Could not compile shader %d:\n%s\n",
                         shaderType, infoLog);
                    free(infoLog);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

GLuint GLProgram::getAttribLocation(const GLchar* attrib)
{
    GLuint retAtt = glGetAttribLocation(_uProgram, attrib);
    checkGlError("glGetAttribLocation");
    LOGI("glGetAttribLocation(\"%s\") = %d\n", attrib, retAtt);
    return retAtt;
}
