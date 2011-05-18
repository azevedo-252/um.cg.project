#Pasta do md2loader
MD2L=md2loader
INIPARSER = iniparser
OUTPUT=main

COMPILERFLAGS = -Wall -funrool-loops -O2 -ffast-math

#Bibliotecas glut
LIBSGL = -lGL -lGLU -lglut -lGLEW
LIBSIL = -lIL
LIBSAL = -lalut

#Compilador
CC=g++

SRC=Radar.cpp \
    Towers.cpp \
    Bullets.cpp \
    Config.cpp \
    Camera.cpp \
    GLManager.cpp \
    InputManager.cpp \
    Textures.cpp \
    Map.cpp \
    Vertex.cpp \
    Player.cpp \
    Model_MD2.cpp \
    Tower.cpp \
    Bullet.cpp \
    Rainbow.cpp \
    Toilet.cpp \
    SkyBox.cpp \
    Keys.cpp \
    Key.cpp \
    Sound.cpp \
    Model.cpp \
    Frame.cpp \
    Plane.cpp \
    Frustum.cpp \
    Lighting.cpp

	

OBJ=$(SRC:.cpp=.o)
OBJH=$(SRC:.cpp=.h)

OBJ_OTHER= Main.cpp
	
.cpp.o:
	$(CC) -c -o $@ $? $(LIBSGL) $(LIBSIL) $(LIBSAL) -D$(USERNAME)
.o:
	$(CC) -c -o $@ $? $(LIBSGL) $(LIBSIL) $(LIBSAL) -D$(USERNAME)
	
.cpp.h:


default: lazy

.PHONY: md2loader
md2loader:
	cd md2loader; make

.PHONY: iniparser
iniparser:
	cd iniparser; make

all: $(OBJ) $(OBJH) md2loader lazy

lazy: $(OBJ) $(OBJH)
	$(CC) -o $(OUTPUT) $(OBJ_OTHER) $(OBJ) $(OBJH) $(MD2L)/*.o $(INIPARSER)/*.o $(LIBSGL) $(LIBSIL) $(LIBSAL)

exec: lazy
	./main

clean:
	rm -f $(OBJ) $(OUTPUT)
