## Compiling

g++ -Wall -Wextra -Werror ascii.cpp -o a.out

## Why I write C++ like this

- I find easier to read underscore hello_world vs. helloWorld. Pros and cons can be read from here  [Link](https://whatheco.de/2011/02/10/camelcase-vs-underscores-scientific-showdown/)

## Learned through the project

- Conversion from spherical to cartesian coordinates

## Key graphics concepts

Term | Explanation
-----|---------
Linear filtering | Function also looks at the other texels around, and mixes the colours according to the distance to each centroid. This avoids the hard edges seen in resulting image.
Anisotropic filtering | Approximates the part of the image that is really seen. Computes the colour contained in the area by taking a fixed number of samples (the “anisotropic level”).
Mipmaps | At initialization time, you scale down your image by 2, until you will have only 1x1 image. When drawing mesh, you choose an image that is closest to size of the texel.
