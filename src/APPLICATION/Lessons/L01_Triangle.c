//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2022 Alrick Grandison                                                                                                 //
//                                                                                                                                      //
//  This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable             //
//  for any damages arising from the use of this software. Permission is granted to anyone to use this software for any                 //
//  purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:      //
//                                                                                                                                      //
//  1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.                 //
//     If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.  //
//  2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.           //
//  3. This notice may not be removed or altered from any source distribution.                                                          //
//                                                                                                                                      //
//                                                                                                                                      //
//  filename: L01_Triangle.c                                                                                                            //
//  created: 2022-06-05 11:33 PM                                                                                                        //
//                                                                                                                                      //
//  description: Draw A Simple Triangle                                                                                                 //
//                                                                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>
#include "glad.h"

#include "Shader4GL.h"

// SDL
static SDL_Window * WINDOW = 0;
static SDL_GLContext CONTEXT = 0;

// Loop
static int RUNNING = 0;

enum {
// Dimension
WIDTH  = 800,
HEIGHT = 600
};

static void createTriangle();
static void drawTriangle();
static void destroyTriangle();

int main(int argc, char * argv[]) {
	if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_Log("SDL Initialized Successfully");

	//Use OpenGL 3.3 core
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

	// Create an application window with the following settings:
	WINDOW = SDL_CreateWindow (
		"SDL - OpenGL App",                  // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		WIDTH,              // width, in pixels
		HEIGHT,             // height, in pixels
		SDL_WINDOW_OPENGL                  // flags - see below
	);

	// Check that the window was successfully created
	if (WINDOW == 0) {
		// In the case that the window could not be made...
		SDL_Log("Could not create window: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	CONTEXT = SDL_GL_CreateContext( WINDOW );

	if( CONTEXT == 0 ) {
		SDL_Log( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
		return EXIT_FAILURE;
	}

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		SDL_Log( "Failed to initialize GLAD! SDL Error: %s\n", SDL_GetError() );
		return EXIT_FAILURE;
	}

	glViewport(0, 0, WIDTH, HEIGHT);

	//Use Vsync
	if( SDL_GL_SetSwapInterval( 1 ) < 0 ) {
		printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
	}

	// START THE GAME
	RUNNING = 1;
	SDL_Event event;
	createTriangle();
	
	// GAME LOOP
	while ( RUNNING ) {
		glClearColor(0.2f, 0.2f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		drawTriangle();
		
		SDL_GL_SwapWindow( WINDOW );
		
		while ( SDL_PollEvent( &event ) ) {  
			if ( event.type == SDL_QUIT ) {
				RUNNING = 0;
			}
		}
	}

	// DESTROY
	destroyTriangle();
	
	SDL_DestroyWindow ( WINDOW );
	SDL_Log("Destroyed Window");

	SDL_GL_DeleteContext ( CONTEXT ); 
	SDL_Log("Destroyed Context");

	SDL_Quit();
	SDL_Log("Quit SDL");

	return EXIT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////////
/////   TRIANGLE

static Shader4GL_t triangleShader;
static unsigned int triangleVAO;
static unsigned int triangleVBO;

static float triangleVertices[] = {
	// positions         // colors
	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
	 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
};

static void createTriangle () {
	// load shader
	triangleShader = Shader4GL_NewFromFile("data/color.vert", "data/color.frag");
	
	glGenVertexArrays(1, &triangleVAO);
	glGenBuffers(1, &triangleVBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(triangleVAO);

	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	SDL_Log("Created Triangle");
}

static void drawTriangle() {
	Shader4GL_Use(&triangleShader);
	glBindVertexArray(triangleVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
}

static void destroyTriangle() {
	glDeleteVertexArrays(1, &triangleVAO);
    	glDeleteBuffers(1, &triangleVBO);
    	Shader4GL_Delete(&triangleShader);
    	
    	SDL_Log("Destroyed Triangle");
}










