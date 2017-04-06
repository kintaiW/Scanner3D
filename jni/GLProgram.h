//
// Created by kintai on 17-4-6.
//

#ifndef OPENCAMERA_GLPROGRAM_H
#define OPENCAMERA_GLPROGRAM_H

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>


class GLProgram {
public:
    GLProgram();
    ~GLProgram();

    /*
     * init GLProgram with vertex shader array data and fragment shader array data
     */
    bool initWithVertexShaderByteArray(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray);

    /*
     * link shader
     */
    bool link();

    /*
     * use this opengl program
     */
    void use();

    /*
     * get location attrib
     */
    GLuint getAttribLocation(const GLchar* attrib);

    inline GLuint getProgramHandle() {return _uProgram;}

private:
    GLuint loadShader(GLenum shaderType, const GLchar* shaderSrc);

    GLuint _uProgram;
    GLuint _uVertShader;
    GLuint _uFragShader;
};



#endif //OPENCAMERA_GLPROGRAM_H
