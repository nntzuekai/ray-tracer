//////////////////////////////////////////////////////////////////////////////
//
//  --- Angel.h ---
//
//   The main header file for all examples from Angel 6th Edition
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __ANGEL_H__
#define __ANGEL_H__

#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))


#  include <GL/glew.h>
//#  include <GL/glut.h>
#  include <GL/freeglut.h>
#  include <GL/freeglut_ext.h>

#ifndef M_PI
#  define M_PI  3.14159265358979323846
#endif


namespace Angel {

//  Helper function to load vertex and fragment shader files
GLuint InitShader( const char* vertexShaderFile,
		   const char* fragmentShaderFile );

//  Defined constant for when numbers are too small to be used in the
//    denominator of a division operation.  This is only used if the
//    DEBUG macro is defined.
const GLfloat  DivideByZeroTolerance = GLfloat(1.0e-07);

//  Degrees-to-radians constant 
const GLfloat  DegreesToRadians = M_PI / 180.0;

}  // namespace Angel


#endif // __ANGEL_H__
