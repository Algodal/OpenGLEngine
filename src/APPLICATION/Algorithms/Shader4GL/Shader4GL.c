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
//  filename: Shader4GL.c                                                                                                               //
//  created: 2022-06-06 12:21 AM                                                                                                        //
//                                                                                                                                      //
//  description: Shader Library For OpenGL                                                                                              //
//                                                                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Shader4GL.h"

#include <SDL2/SDL.h>
#include "glad.h"

static void runCompileErrors(unsigned int shader, const char * type);

Shader4GL_t Shader4GL_NewFromFile(const char * vertf, const char * fragf) {
	Shader4GL_t shader;
	Shader4GL_LoadFile(&shader, vertf, fragf);
	return shader;
}

Shader4GL_t Shader4GL_NewFromMemory(const char * vert, const char * frag) {
	Shader4GL_t shader;
	Shader4GL_LoadMemory(&shader, vert, frag);
	return shader;
}

void Shader4GL_LoadFile(Shader4GL_t * this, const char * vertf, const char * fragf)
{
	SDL_RWops * vf = SDL_RWFromFile(vertf, "r");
	Sint64 vs = SDL_RWsize(vf);
	char vbuf[vs + 1]; vbuf[vs] = 0;
	SDL_RWread(vf, vbuf, vs, 1);

	SDL_RWops * ff = SDL_RWFromFile(fragf, "r");
	Sint64 fs = SDL_RWsize(ff);
	char fbuf[fs + 1]; fbuf[fs] = 0;
	SDL_RWread(ff, fbuf, fs, 1);

	Shader4GL_LoadMemory(this, vbuf, fbuf);
}

void Shader4GL_LoadMemory(Shader4GL_t * this, const char * vert, const char * frag)
{
	// vertex shader
	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vert, 0);
	glCompileShader(vertex);
	runCompileErrors(vertex, "VERTEX");

	// fragment shader
	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &frag, 0);
	glCompileShader(fragment);
	runCompileErrors(fragment, "FRAGMENT");

	// shader program
	this->id = glCreateProgram();
	glAttachShader(this->id, vertex);
	glAttachShader(this->id, fragment);
	glLinkProgram(this->id);
	runCompileErrors(this->id, "PROGRAM");

	// delete the shaders that are now linked
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader4GL_Delete(Shader4GL_t * this) {
	glDeleteProgram(this->id);
	this->id = 0;
}

void Shader4GL_Use(Shader4GL_t * this) {
	glUseProgram(this->id);
}

void Shader4GL_SetInt(Shader4GL_t * this, const char * name, int value)
{
	glUniform1i(glGetUniformLocation(this->id, name), value);
}

void Shader4GL_SetFloat(Shader4GL_t * this, const char * name, float value)
{
	glUniform1f(glGetUniformLocation(this->id, name), value);
}

static void runCompileErrors(unsigned int shader, const char * type)
{
	int success;
	char infoLog[1024];
	
	if (strcmp(type, "PROGRAM") == 0) 
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		
		if (success == 0) 
		{
			glGetShaderInfoLog(shader, 1024, 0, infoLog);
			SDL_Log(
				"ERROR::PROGRAM_LINKING_ERROR of type: %s\n"
				"%s\n"
				"------------------------------------------------",
				type, infoLog
			);
		}
	} 
	else
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (success == 0) 
		{
			glGetShaderInfoLog(shader, 1024, 0, infoLog);
			SDL_Log(
				"ERROR::SHADER_COMPILATION_ERROR of type: %s\n"
				"%s\n"
				"------------------------------------------------",
				type, infoLog
			);
		}
	} 
}










