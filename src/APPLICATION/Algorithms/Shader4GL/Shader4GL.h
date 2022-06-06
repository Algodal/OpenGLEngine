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
//  filename: Shader4GL.h                                                                                                               //
//  created: 2022-06-06 12:21 AM                                                                                                        //
//                                                                                                                                      //
//  description: Shader Library For OpenGL                                                                                              //
//                                                                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef ___H_SHADER4GL___
#define ___H_SHADER4GL___

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
	unsigned int id;
} Shader4GL_t;

Shader4GL_t Shader4GL_NewFromFile(const char * vertf, const char * fragf);
Shader4GL_t Shader4GL_NewFromMemory(const char * vert, const char * frag);
void Shader4GL_LoadFile(Shader4GL_t * this, const char * vertf, const char * fragf);
void Shader4GL_LoadMemory(Shader4GL_t * this, const char * vert, const char * frag);
void Shader4GL_Delete(Shader4GL_t * this);
void Shader4GL_Use(Shader4GL_t * this);
void Shader4GL_SetInt(Shader4GL_t * this, const char * name, int value);
void Shader4GL_SetFloat(Shader4GL_t * this, const char * name, float value);


#ifdef __cplusplus
}
#endif

#endif //___H_SHADER4GL___










