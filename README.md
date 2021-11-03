# Graphics-Nerd
Graphics nerd is my excercise project to learn C++ and OpenGL Graphics library.

## Why I write C++ like this

- I find easier to read underscore hello_world vs. helloWorld. Pros and cons can be read from here  [Link](https://whatheco.de/2011/02/10/camelcase-vs-underscores-scientific-showdown/

## Learned through the project

- C++ OOP
- Object files parsing (*.obj)
- Freetype parsing
- Conversion from spherical to cartesian coordinates
- Double buffering
- Vertex Buffer Objects
- HLSL Shader language

## Key graphics concepts

Term | Explanation
-----|---------
Linear filtering | Function also looks at the other texels around, and mixes the colours according to the distance to each centroid. This avoids the hard edges seen in resulting image.
Anisotropic filtering | Approximates the part of the image that is really seen. Computes the colour contained in the area by taking a fixed number of samples (the “anisotropic level”).
Mipmaps | At initialization time, you scale down your image by 2, until you will have only 1x1 image. When drawing mesh, you choose an image that is closest to size of the texel.

OpenGL objects:

	// create object
	unsigned int objectId = 0;
	glGenObject(1, &objectId);
	// bind/assign object to context
	glBindObject(GL_WINDOW_TARGET, objectId);
	// set options of object currently bound to GL_WINDOW_TARGET
	glSetObjectOption(GL_WINDOW_TARGET, GL_OPTION_WINDOW_WIDTH,  800);
	glSetObjectOption(GL_WINDOW_TARGET, GL_OPTION_WINDOW_HEIGHT, 600);
	// set context target back to default
	glBindObject(GL_WINDOW_TARGET, 0);

We first create an object and store a reference to it as an id (the real object's data is stored behind the scenes). Then we bind the object (using its id) to the target location of the context (the location of the example window object target is defined as GL_WINDOW_TARGET). Next we set the window options and finally we un-bind the object by setting the current object id of the window target to 0.
[From OpenGL tutorial](https://learnopengl.com/Getting-started/OpenGL)

The first part of the pipeline is the vertex shader that takes as input a single vertex. The main purpose of the vertex shader is to transform 3D coordinates into different 3D coordinates (more on that later) and the vertex shader allows us to do some basic processing on the vertex attributes. It transforms coordinates to normalized device coordinates.

The main purpose of the fragment shader is to calculate the final color of a pixel and this is usually the stage where all the advanced OpenGL effects occur.
