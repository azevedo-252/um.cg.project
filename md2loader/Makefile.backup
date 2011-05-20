#Makefile para compilar a biblioteca MD2Loader
#Gera o ficheiro md2loader.o para ser linkado ao programa principal

#Bibliotecas glut
LIBSGL = -lGL -lGLU -lglut -lGLEW
#Compilador
CC=g++

OUTPUT=md2loader.o

SRC=	DataManager.h \
	Image.cpp \
	Image.h \
	Md2Model.cpp \
	Md2Model.h \
	Md2Player.cpp \
	Md2Player.h \
	Texture.cpp \
	Texture.h \
	TextureManager.h
		
default: md2loader

clean:
	rm -f *.gch *.o

md2loader:
	@echo "Compiling MD2Loader Library"
	$(CC) -c $(LIBSGL) $(SRC)
	@echo "Done"
