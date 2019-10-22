
CC=gcc
OPCOES_COMPILADOR=-I. -I/../SOIL -lglut -lGLU -lGLEW -lGL -lSOIL -lm
TODOS_ARQUIVOS_PONTOH = libs/glm.h libs/sgi.h
TODOS_ARQUIVOS_OBJ = park.o libs/sgi.o libs/glm.o libs/glmimg.o libs/glm_util.o 

%.o: ../%.c $(TODOS_ARQUIVOS_PONTOH)
	$(CC) -o $@ -c $< $(OPCOES_COMPILADOR)

all: $(TODOS_ARQUIVOS_OBJ)
	gcc -o park $^ $(OPCOES_COMPILADOR)

run: all
	./park

clean:
	rm *.o park
