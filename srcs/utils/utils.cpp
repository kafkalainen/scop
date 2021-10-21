#include "../../headers/nerd.h"

bool initGL()
{
    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );

    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        cout << "Error initializing OpenGL!" << gluErrorString(error) << endl;
        return false;
    }
    return true;
}

void update()
{

}

void render()
{
    //Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT );
	glBegin( GL_QUADS );
        glVertex2f( -0.5f, -0.5f );
        glVertex2f(  0.5f, -0.5f );
        glVertex2f(  0.5f,  0.5f );
        glVertex2f( -0.5f,  0.5f );
    glEnd();
	//Update screen
    glutSwapBuffers();
}
