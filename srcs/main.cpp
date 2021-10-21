#include "../headers/nerd.h"

void runMainLoop( int val )
{
	//Frame logic
	update();
	render();

	//Run frame one more time
	glutTimerFunc( 1000 / SCREEN_FPS, runMainLoop, val );
}

int main(int argc, char **args)
{
	//Initialize FreeGLUT
	glutInit(&argc, args);
	//Create OpenGL 2.1 context
	glutInitContextVersion( 2, 1 );
	 //Create Double Buffered Window
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("OpenGL");
	//Do post window/context creation initialization
	if( !initGL() )
	{
		cout << "Unable to initialize graphics library!" << endl;
		return (1);
	}
	 //Set rendering function
	glutDisplayFunc(render);
	//Set main loop
	glutTimerFunc(1000 / SCREEN_FPS, runMainLoop, 0);
	//Start GLUT main loop
	glutMainLoop();
	return (0);
}
