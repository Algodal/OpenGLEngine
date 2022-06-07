#####################################
#  OPENGLENGINE GENERATED MAKEFILE  #
#                                   #
#  © ALL RIGHTS RESERVED            #
#  ALGODAL™                         #
#                                   #
#  2022-06-07 02:56 AM              #
#####################################

ARGS=
INC= -Isrc/APPLICATION/Algorithms/Shader4GL -Isrc/CORE/GLAD
DEP= -Lbin
GCC= gcc
CFLAGS= -Wall -g `sdl2-config --cflags --libs`
EFLAGS= 
BFLAGS= 
FLAGS_SHARED= -fPIC
FLAGS_STATIC= 
LFLAGS_SHARED= --shared
LFLAGS_STATIC= -rcs
EXTERN_LIB_BIN= -lSDL2 -lSDL2_image -lGL -ldl
CLEAN_BIN= $(wildcard bin/*.*)
CLEAN_EXEC= $(wildcard bin/exec/*.*)
CLEAN_STATIC= $(wildcard bin/static/*.*)
CLEAN_SHARED= $(wildcard bin/shared/*.*)



########  BUILD  ########
build: bin/libOpenGLEngine.a
build-src: bin/libOpenGLEngine.a

#########  BIN  #########
bin/L01_Triangle.out: bin/exec/L01_Triangle.o bin/libOpenGLEngine.a | bin bin/exec bin/shared bin/static
	$(GCC) $(BFLAGS) $(CFLAGS) $(DEP) bin/exec/L01_Triangle.o -lOpenGLEngine $(EXTERN_LIB_BIN)  -o bin/L01_Triangle.out

bin/L01_Rectangle.out: bin/exec/L01_Rectangle.o bin/libOpenGLEngine.a | bin bin/exec bin/shared bin/static
	$(GCC) $(BFLAGS) $(CFLAGS) $(DEP) bin/exec/L01_Rectangle.o -lOpenGLEngine $(EXTERN_LIB_BIN)  -o bin/L01_Rectangle.out

bin/L02_Texture.out: bin/exec/L02_Texture.o bin/libOpenGLEngine.a | bin bin/exec bin/shared bin/static
	$(GCC) $(BFLAGS) $(CFLAGS) $(DEP) bin/exec/L02_Texture.o -lOpenGLEngine $(EXTERN_LIB_BIN)  -o bin/L02_Texture.out



###  STATIC LIBRARY  ###
bin/libOpenGLEngine.a: bin/static/glad.o bin/static/Shader4GL.o
	$(AR) $(LFLAGS_STATIC) -o bin/libOpenGLEngine.a bin/static/glad.o bin/static/Shader4GL.o



###  SHARED LIBRARY  ###
bin/libOpenGLEngine.so: bin/shared/glad.o bin/shared/Shader4GL.o
	$(GCC) $(LFLAGS_SHARED) -o bin/libOpenGLEngine.so bin/shared/glad.o bin/shared/Shader4GL.o



#####  EXEC OBJECT  #####
bin/exec/L01_Triangle.o: src/APPLICATION/Lessons/L01_Triangle.c src/CORE/GLAD/glad.h src/CORE/GLAD/khrplatform.h src/APPLICATION/Algorithms/Shader4GL/Shader4GL.h | bin bin/exec bin/shared bin/static
	gcc -c $(EFLAGS) $(CFLAGS) $(INC) src/APPLICATION/Lessons/L01_Triangle.c  -o bin/exec/L01_Triangle.o

bin/exec/L01_Rectangle.o: src/APPLICATION/Lessons/L01_Rectangle.c src/CORE/GLAD/glad.h src/CORE/GLAD/khrplatform.h src/APPLICATION/Algorithms/Shader4GL/Shader4GL.h | bin bin/exec bin/shared bin/static
	gcc -c $(EFLAGS) $(CFLAGS) $(INC) src/APPLICATION/Lessons/L01_Rectangle.c  -o bin/exec/L01_Rectangle.o

bin/exec/L02_Texture.o: src/APPLICATION/Lessons/L02_Texture.c src/CORE/GLAD/glad.h src/CORE/GLAD/khrplatform.h src/APPLICATION/Algorithms/Shader4GL/Shader4GL.h | bin bin/exec bin/shared bin/static
	gcc -c $(EFLAGS) $(CFLAGS) $(INC) src/APPLICATION/Lessons/L02_Texture.c  -o bin/exec/L02_Texture.o



####  STATIC OBJECT  ####
bin/static/glad.o: src/CORE/GLAD/glad.c src/CORE/GLAD/glad.h src/CORE/GLAD/khrplatform.h | bin bin/exec bin/shared bin/static
	gcc -c $(FLAGS_STATIC) $(CFLAGS) $(INC) src/CORE/GLAD/glad.c  -o bin/static/glad.o

bin/static/Shader4GL.o: src/APPLICATION/Algorithms/Shader4GL/Shader4GL.c src/CORE/GLAD/glad.h src/CORE/GLAD/khrplatform.h src/APPLICATION/Algorithms/Shader4GL/Shader4GL.h | bin bin/exec bin/shared bin/static
	gcc -c $(FLAGS_STATIC) $(CFLAGS) $(INC) src/APPLICATION/Algorithms/Shader4GL/Shader4GL.c  -o bin/static/Shader4GL.o



####  SHARED OBJECT  ####
bin/shared/glad.o: src/CORE/GLAD/glad.c src/CORE/GLAD/glad.h src/CORE/GLAD/khrplatform.h | bin bin/exec bin/shared bin/static
	gcc -c $(FLAGS_SHARED) $(CFLAGS) $(INC) src/CORE/GLAD/glad.c  -o bin/shared/glad.o

bin/shared/Shader4GL.o: src/APPLICATION/Algorithms/Shader4GL/Shader4GL.c src/CORE/GLAD/glad.h src/CORE/GLAD/khrplatform.h src/APPLICATION/Algorithms/Shader4GL/Shader4GL.h | bin bin/exec bin/shared bin/static
	gcc -c $(FLAGS_SHARED) $(CFLAGS) $(INC) src/APPLICATION/Algorithms/Shader4GL/Shader4GL.c  -o bin/shared/Shader4GL.o



#########  RUN  #########
L01_Triangle: bin/L01_Triangle.out
	./bin/L01_Triangle.out $(ARGS)

L01_Rectangle: bin/L01_Rectangle.out
	./bin/L01_Rectangle.out $(ARGS)

L02_Texture: bin/L02_Texture.out
	./bin/L02_Texture.out $(ARGS)



########  CLEAN  ########
clean:
ifeq ($(CLEAN_BIN),)
else
	rm $(CLEAN_BIN)
endif
ifeq ($(CLEAN_EXEC),)
else
	rm $(CLEAN_EXEC)
endif
ifeq ($(CLEAN_STATIC),)
else
	rm $(CLEAN_STATIC)
endif
ifeq ($(CLEAN_SHARED),)
else
	rm $(CLEAN_SHARED)
endif



###  OUTPUT FOLDERS  ###
bin:
	mkdir -p bin

bin/exec:
	mkdir -p bin/exec

bin/shared:
	mkdir -p bin/shared

bin/static:
	mkdir -p bin/static

