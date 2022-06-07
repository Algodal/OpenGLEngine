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
//  filename: L02_Texture.c                                                                                                             //
//  created: 2022-06-07 12:57 AM                                                                                                        //
//                                                                                                                                      //
//  description: Texture for OpenGL                                                                                                     //
//                                                                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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

static void createTexture();
static void drawTexture();
static void destroyTexture();

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
	
	if( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) ) {
		SDL_Log( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
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
	createTexture();
	
	// GAME LOOP
	while ( RUNNING ) {
		glClearColor(0.2f, 0.2f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		drawTexture();
		
		SDL_GL_SwapWindow( WINDOW );
		
		while ( SDL_PollEvent( &event ) ) {  
			if ( event.type == SDL_QUIT ) {
				RUNNING = 0;
			}
		}
	}

	// DESTROY
	destroyTexture();
	
	IMG_Quit();
	SDL_Log("Destroyed Image Loader");
	
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

static Shader4GL_t textureShader;
static unsigned int textureVAO;
static unsigned int textureVBO;
static unsigned int textureEBO;
static unsigned int textureTEX;

static float textureVertices[] = {
	// positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
};

unsigned int textureIndices[] = { 
    	0, 1, 3, // first triangle
        1, 2, 3  // second triangle
};  

static void createTexture () {
	// load shader
	textureShader = Shader4GL_NewFromFile("data/tex.vert", "data/tex.frag");
	
	glGenVertexArrays(1, &textureVAO);
	glGenBuffers(1, &textureVBO);
	glGenBuffers(1, &textureEBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(textureVAO);

	glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textureVertices), textureVertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, textureEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(textureIndices), textureIndices, GL_STATIC_DRAW); 
	
	// load and create a texture 
	// -------------------------
	glGenTextures(1, &textureTEX);
	glBindTexture(GL_TEXTURE_2D, textureTEX); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	SDL_Surface * image = IMG_Load("data/wall.png");
	if (image) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		SDL_Log("Failed to load texture");
	}
	SDL_FreeSurface(image);
	
	SDL_Log("Created Texture");
}

static void drawTexture() {
	Shader4GL_Use(&textureShader);
	glBindVertexArray(textureVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

static void destroyTexture() {
	glDeleteVertexArrays(1, &textureVAO);
    	glDeleteBuffers(1, &textureVBO);
    	Shader4GL_Delete(&textureShader);
    	
    	SDL_Log("Destroyed Texture");
}
























