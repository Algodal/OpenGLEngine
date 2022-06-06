# OpenGLEngine
This is a learning development exercise to become familiar with OpenGL.  The second goal is to create useful algorithms that can be re-used in other projets.  We will be guided mostly by the tutorial, [LearnOpenGL](https://learnopengl.com/) with the difference being that we will only be coding in C and using C 3rd-party libraries.  We will be using [SDL](https://www.libsdl.org/) for our windows and [GLAD](https://glad.dav1d.de/) for our OpenGL interface.

This project is for 2 main purposes as said before:
* Learn OpenGL
* Build Algorithms to make it easier to use OpenGL

We will also use 3rd-party libraries as we continue our learning.  We will link them here as we learn them.
We may also, tweak or edit, third-party libraries (and these derivatives will go in our tweaked folders).  
We will also link any algorithms we create here.

## Algorithms
* [Shader4GL](src/APPLICATION/Algorithms/Shader4GL/) - Convenience for Loading a Shader Program.  Handles debug and de-allocating individual shaders.

## Useful Quotes
* LearnOpenGL: Sending data to the graphics card from the CPU is relatively slow, so wherever we can we try to send as much data as possible at once. 

## Building
* This project is built for linux (unix).  If you are using windows you will have to research on your own how to build it.
* We generate a makefile (using an internal tool).  All you need to do is run make. If you using something other than make (do your own research).
* We will depend on these libraries: `-lSDL2 -lGL -ldl` (for linux).  Do your own research if on another platform.
* Besides that we are using a simple Text Editor (everybody has one of those).
* [GLAD](https://glad.dav1d.de/) - you can use the one we already have generated or generate your own ( it doesn't matter). 
* When running a program, its expected that the root folder is the working directory.  All paths references are according to this.

## License
This project is licensed under the zlib license - see the [LICENSE](LICENSE) file for details.
© All rights reserved.

## Project Managers
* Lead:		Alrick Grandison


## Authors
See [AUTHORS](AUTHORS) for full list.

## Contributing
See [CONTRIBUTING.md](CONTRIBUTING.md) for how to contribute.


<br/><br/>
