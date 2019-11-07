#include <SFML/Audio.hpp>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "libs/glm.h"
#include "libs/sgi.h"

sf::Music park_music;
sf::Music MenuSelect_sound;
sf::Music MenuTheme;

GLuint idTexturabackgroundINICIO;

//INSTALAÇÃO BIBLIOTECA "SFML AUDIO"
//sudo apt-get install libsfml-dev


enum CAMERAS { ESTATICA = 1, PRIMEIRA_PESSOA, TERCEIRA_PESSOA, BRINQUEDO1, BRINQUEDO2, BRINQUEDO3, BRINQUEDO_1_2_3};
int modoCAM = ESTATICA;            //variável responsável por guardar o modo de câmera que está sendo utilizado


GLuint carregaTextura(const char* arquivo) {
  GLuint idTextura = SOIL_load_OGL_texture(
    arquivo,
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
  );


  if (idTextura == 0) {
    printf("Erro do SOIL: '%s'\n", SOIL_last_result());
  }
  return idTextura;
}

int xMouse = 0, yMouse = 0;     //variáveis globais que serão usadas na função posicionaCamera
float xCursor, yCursor, zCursor;  //guarda o centro do cursor
float phi = 90, teta = 0;       //ângulos das coordenadas esféricas

int tocou = 0;

int telaINICIO = 1;
int telaJOGO = 0;

float rotacaoRG = 0.1;
float rotacaoBARCO = 0.1;
float movPlanet = 0.1;
float i = 0;

float cont = 4;

int highPlanet = 0;
int lowPlanet = 1;

float CCADEIRAx[6] = {0.013, 0.853, 0.77, -0.116, -0.831, -0.701};
float CCADEIRAy[6] = {9.272, 9.272, 9.272, 9.272, 9.272, 9.272};
float CCADEIRAz[6] = {3.301, 3.889, 4.771, 5.15, 4.594, 3.681};
float CCADEIRArotY[6] = {0, -60, -120, -180, -240, -300};


float CabineX[10] = {3.329,3.125,2.7,2.264,1.915,1.795,2.018,2.423,2.883,3.154};
float CabineY[10] = {8.802,9.218,9.428,9.393,9.108,8.695,8.208,8.026,8.071,8.378};
float CabineZ[10] = {2.23,2.23,2.23,2.23,2.23,2.23,2.23,2.23,2.23,2.23};
float CabineROTy[10] = {0,0,0,0,0,0,0,0,0,0};

float POSTEx[14] = {-0.421, 0.421, -0.421, 0.421, -0.421, 0.421, 1.306, 3.687, -1.306, -3.687, 1.306, 3.687, -1.306, -3.687};
float POSTEy[14] = {8.044, 8.044, 8.044, 8.044, 8.044, 8.044, 8.044, 8.044, 8.044, 8.044, 8.044, 8.044, 8.044, 8.044};
float POSTEz[14] = {-0.369,-0.369,-1.958,-1.958,2.239,2.239,1.409,1.409,1.409,1.409,0.466,0.466,0.466,0.466};
float POSTErotY[14] = {90,270,90,270,90,270,180,180,180,180,0,0,0,0};

float CvoadoraX[12] = {0.107,3.104,5.199,5.923,5.228,3.008,0,-2.849,-5.087,-5.79,-4.996,-2.815};
float CvoadoraY[12] = {5.033,5.033,5.033,5.033,5.033,5.033,5.033,5.033,5.033,5.033,5.033,5.033};
float CvoadoraZ[12] = {-5.847,-5.128,-2.914,0,2.973,5.098,5.922,5.11,3.011,0,-3.014,-5.14};
float CvoadoraROTy[12] = {0,-30,-60,-90,-120,-150,-180,-210,-240,-270,-300,-330};

float CarroX[7] = {3.201,2.62,2.006,1.364,-0.868,-1.675,-2.37};
float CarroY[7] = {7.97,7.97,7.97,7.97,7.97,7.97,7.97};
float CarroZ[7] = {-4.567,-4.567,-4.567,-4.567,-4.567,-4.567,-4.567};
float CarroROTy[7] = {0,0,0,0,0,0,0};

float LixeiraX[4] = {0.53,-0.53,0.53,-0.53};
float LixeiraY[4] = {7.825,7.825,7.825,7.825};
float LixeiraZ[4] = {0.403,0.403,1.531,1.531};
float LixeiraROTy[4] = {0,0,0,0};

int volumeMUSIC = 100;

GLMmodel* grama = NULL;
GLMmodel* chao = NULL;
GLMmodel* estacionamento = NULL;

GLMmodel* banco1 = NULL;
GLMmodel* banco2 = NULL;
GLMmodel* banco3 = NULL;
GLMmodel* banco4 = NULL;
GLMmodel* banco5 = NULL;
GLMmodel* banco6 = NULL;
GLMmodel* banco7 = NULL;
GLMmodel* banco8 = NULL;
GLMmodel* banco9 = NULL;
GLMmodel* banco10 = NULL;
GLMmodel* banco11 = NULL;
GLMmodel* banco12 = NULL;

GLMmodel* rodaGIGANTE = NULL;
GLMmodel* rgBASE1 = NULL;
GLMmodel* rgBASE2 = NULL;

GLMmodel* barco = NULL;
GLMmodel* barcoBASE = NULL;

GLMmodel* muro = NULL;

GLMmodel* planeta1 = NULL;
GLMmodel* planeta2 = NULL;
GLMmodel* planeta3 = NULL;
GLMmodel* planeta4 = NULL;

GLMmodel* barraca1 = NULL;
GLMmodel* barraca2 = NULL;
GLMmodel* barraca3 = NULL;
GLMmodel* barraca4 = NULL;

GLMmodel* carrossel = NULL;
GLMmodel* ccadeira1 = NULL;
GLMmodel* ccadeira2 = NULL;
GLMmodel* ccadeira3 = NULL;
GLMmodel* ccadeira4 = NULL;
GLMmodel* ccadeira5 = NULL;
GLMmodel* ccadeira6 = NULL;

GLMmodel* poste1 = NULL;
GLMmodel* poste2 = NULL;
GLMmodel* poste3 = NULL;
GLMmodel* poste4 = NULL;
GLMmodel* poste5 = NULL;
GLMmodel* poste6 = NULL;
GLMmodel* poste7 = NULL;
GLMmodel* poste8 = NULL;
GLMmodel* poste9 = NULL;
GLMmodel* poste10 = NULL;
GLMmodel* poste11 = NULL;
GLMmodel* poste12 = NULL;
GLMmodel* poste13 = NULL;
GLMmodel* poste14 = NULL;

GLMmodel* cvoadora1 = NULL;
GLMmodel* cvoadora2 = NULL;
GLMmodel* cvoadora3 = NULL;
GLMmodel* cvoadora4 = NULL;
GLMmodel* cvoadora5 = NULL;
GLMmodel* cvoadora6 = NULL;
GLMmodel* cvoadora7 = NULL;
GLMmodel* cvoadora8 = NULL;
GLMmodel* cvoadora9 = NULL;
GLMmodel* cvoadora10 = NULL;
GLMmodel* cvoadora11 = NULL;
GLMmodel* cvoadora12 = NULL;

GLMmodel* carro1 = NULL;
GLMmodel* carro2 = NULL;
GLMmodel* carro3 = NULL;
GLMmodel* carro4 = NULL;
GLMmodel* carro5 = NULL;
GLMmodel* carro6 = NULL;
GLMmodel* carro7 = NULL;

GLMmodel* lixeira1 = NULL;
GLMmodel* lixeira2 = NULL;
GLMmodel* lixeira3 = NULL;
GLMmodel* lixeira4 = NULL;

GLMmodel* placaND = NULL;
GLMmodel* placaNP = NULL;
GLMmodel* placaRG = NULL;
GLMmodel* placaCar = NULL;
GLMmodel* placaBarc = NULL;

GLMmodel* cabine1 = NULL;
GLMmodel* cabine2 = NULL;
GLMmodel* cabine3 = NULL;
GLMmodel* cabine4 = NULL;
GLMmodel* cabine5 = NULL;
GLMmodel* cabine6 = NULL;
GLMmodel* cabine7 = NULL;
GLMmodel* cabine8 = NULL;
GLMmodel* cabine9 = NULL;
GLMmodel* cabine10 = NULL;

// estrutura de dados que representará as coordenadas da câmera
struct {
  float x, y, z;
  float targetX, targetY, targetZ;
} camera;

void desenhaTELAinicial(){
  // Habilita o uso de texturas
  glEnable(GL_TEXTURE_2D);
  // Começa a usar a textura que criamos
  glBindTexture(GL_TEXTURE_2D, idTexturabackgroundINICIO);

  glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0, 0);
    glVertex3f(-1000,-1000, 0);

    glTexCoord2f(1, 0);
    glVertex3f(1000, -1000, 0);

    glTexCoord2f(1, 1);
    glVertex3f(1000, 1000, 0);

    glTexCoord2f(0, 1);
    glVertex3f(-1000, 1000, 0);
  glEnd();

  glDisable(GL_TEXTURE_2D);
}

void desenhaCABINE1(){
  if(!cabine1){
    cabine1 = glmReadOBJ("objs/cabinerodagigante/cabine.obj");
    if (!cabine1) exit(0);
  }
  glmDraw(cabine1, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCABINE2(){
  if(!cabine2){
    cabine2 = glmReadOBJ("objs/cabinerodagigante/cabine.obj");
    if (!cabine2) exit(0);
  }
  glmDraw(cabine2, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCABINE3(){
  if(!cabine3){
    cabine3 = glmReadOBJ("objs/cabinerodagigante/cabine.obj");
    if (!cabine3) exit(0);
  }
  glmDraw(cabine3, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCABINE4(){
  if(!cabine4){
    cabine4 = glmReadOBJ("objs/cabinerodagigante/cabine.obj");
    if (!cabine4) exit(0);
  }
  glmDraw(cabine4, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCABINE5(){
  if(!cabine5){
    cabine5 = glmReadOBJ("objs/cabinerodagigante/cabine.obj");
    if (!cabine5) exit(0);
  }
  glmDraw(cabine5, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCABINE6(){
  if(!cabine6){
    cabine6 = glmReadOBJ("objs/cabinerodagigante/cabine.obj");
    if (!cabine6) exit(0);
  }
  glmDraw(cabine6, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCABINE7(){
  if(!cabine7){
    cabine7 = glmReadOBJ("objs/cabinerodagigante/cabine.obj");
    if (!cabine7) exit(0);
  }
  glmDraw(cabine7, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCABINE8(){
  if(!cabine8){
    cabine8 = glmReadOBJ("objs/cabinerodagigante/cabine.obj");
    if (!cabine8) exit(0);
  }
  glmDraw(cabine8, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCABINE9(){
  if(!cabine9){
    cabine9 = glmReadOBJ("objs/cabinerodagigante/cabine.obj");
    if (!cabine9) exit(0);
  }
  glmDraw(cabine9, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCABINE10(){
  if(!cabine10){
    cabine10 = glmReadOBJ("objs/cabinerodagigante/cabine.obj");
    if (!cabine10) exit(0);
  }
  glmDraw(cabine10, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaPLACAnd(){
  if(!placaND){
    placaND = glmReadOBJ("objs/placa_nome/placanome.obj");
    if (!placaND) exit(0);
  }
  glmDraw(placaND, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaPLACAnp(){
  if(!placaNP){
    placaNP = glmReadOBJ("objs/placa_nome_parque/placanomeparque.obj");
    if (!placaNP) exit(0);
  }
  glmDraw(placaNP, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaPLACArg(){
  if(!placaRG){
    placaRG = glmReadOBJ("objs/placa_roda_gigante/placarodagigante.obj");
    if (!placaRG) exit(0);
  }
  glmDraw(placaRG, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaPLACAcar(){
  if(!placaCar){
    placaCar = glmReadOBJ("objs/placa_carrossel/placacarrosselvoador.obj");
    if (!placaCar) exit(0);
  }
  glmDraw(placaCar, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaPLACAbarc(){
  if(!placaBarc){
    placaBarc = glmReadOBJ("objs/placa_barco_viking/placabarcoviking.obj");
    if (!placaBarc) exit(0);
  }
  glmDraw(placaBarc, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaLIXEIRA1(){
  if(!lixeira1){
    lixeira1 = glmReadOBJ("objs/lixo/lixo.obj");
    if (!lixeira1) exit(0);
  }
  glmDraw(lixeira1, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaLIXEIRA2(){
  if(!lixeira2){
    lixeira2 = glmReadOBJ("objs/lixo/lixo.obj");
    if (!lixeira2) exit(0);
  }
  glmDraw(lixeira2, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaLIXEIRA3(){
  if(!lixeira3){
    lixeira3 = glmReadOBJ("objs/lixo/lixo.obj");
    if (!lixeira3) exit(0);
  }
  glmDraw(lixeira3, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaLIXEIRA4(){
  if(!lixeira4){
    lixeira4 = glmReadOBJ("objs/lixo/lixo.obj");
    if (!lixeira4) exit(0);
  }
  glmDraw(lixeira4, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCARRO1(){
  if(!carro1){
    carro1 = glmReadOBJ("objs/carrinho/carrinho.obj");
    if (!carro1) exit(0);
  }
  glmDraw(carro1, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCARRO2(){
  if(!carro2){
    carro2 = glmReadOBJ("objs/carrinho/carrinho.obj");
    if (!carro2) exit(0);
  }
  glmDraw(carro2, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCARRO3(){
  if(!carro3){
    carro3 = glmReadOBJ("objs/carrinho/carrinho.obj");
    if (!carro3) exit(0);
  }
  glmDraw(carro3, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCARRO4(){
  if(!carro4){
    carro4 = glmReadOBJ("objs/carrinho/carrinho.obj");
    if (!carro4) exit(0);
  }
  glmDraw(carro4, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCARRO5(){
  if(!carro5){
    carro5 = glmReadOBJ("objs/carrinho/carrinho.obj");
    if (!carro5) exit(0);
  }
  glmDraw(carro5, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCARRO6(){
  if(!carro6){
    carro6 = glmReadOBJ("objs/carrinho/carrinho.obj");
    if (!carro6) exit(0);
  }
  glmDraw(carro6, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCARRO7(){
  if(!carro7){
    carro7 = glmReadOBJ("objs/carrinho/carrinho.obj");
    if (!carro7) exit(0);
  }
  glmDraw(carro7, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCVoadora1(){
  if(!cvoadora1){
    cvoadora1 = glmReadOBJ("objs/cadeira/cadeira.obj");
    if (!cvoadora1) exit(0);
  }
  glmDraw(cvoadora1, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCVoadora2(){
  if(!cvoadora2){
    cvoadora2 = glmReadOBJ("objs/cadeira/cadeira.obj");
    if (!cvoadora2) exit(0);
  }
  glmDraw(cvoadora2, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCVoadora3(){
  if(!cvoadora3){
    cvoadora3 = glmReadOBJ("objs/cadeira/cadeira.obj");
    if (!cvoadora3) exit(0);
  }
  glmDraw(cvoadora3, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCVoadora4(){
  if(!cvoadora4){
    cvoadora4 = glmReadOBJ("objs/cadeira/cadeira.obj");
    if (!cvoadora4) exit(0);
  }
  glmDraw(cvoadora4, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCVoadora5(){
  if(!cvoadora5){
    cvoadora5 = glmReadOBJ("objs/cadeira/cadeira.obj");
    if (!cvoadora5) exit(0);
  }
  glmDraw(cvoadora5, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCVoadora6(){
  if(!cvoadora6){
    cvoadora6 = glmReadOBJ("objs/cadeira/cadeira.obj");
    if (!cvoadora6) exit(0);
  }
  glmDraw(cvoadora6, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCVoadora7(){
  if(!cvoadora7){
    cvoadora7 = glmReadOBJ("objs/cadeira/cadeira.obj");
    if (!cvoadora7) exit(0);
  }
  glmDraw(cvoadora7, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCVoadora8(){
  if(!cvoadora8){
    cvoadora8 = glmReadOBJ("objs/cadeira/cadeira.obj");
    if (!cvoadora8) exit(0);
  }
  glmDraw(cvoadora8, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCVoadora9(){
  if(!cvoadora9){
    cvoadora9 = glmReadOBJ("objs/cadeira/cadeira.obj");
    if (!cvoadora9) exit(0);
  }
  glmDraw(cvoadora9, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCVoadora10(){
  if(!cvoadora10){
    cvoadora10 = glmReadOBJ("objs/cadeira/cadeira.obj");
    if (!cvoadora10) exit(0);
  }
  glmDraw(cvoadora10, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCVoadora11(){
  if(!cvoadora11){
    cvoadora11 = glmReadOBJ("objs/cadeira/cadeira.obj");
    if (!cvoadora11) exit(0);
  }
  glmDraw(cvoadora11, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCVoadora12(){
  if(!cvoadora12){
    cvoadora12 = glmReadOBJ("objs/cadeira/cadeira.obj");
    if (!cvoadora12) exit(0);
  }
  glmDraw(cvoadora12, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaPOSTE1(){
  if(!poste1){
    poste1 = glmReadOBJ("objs/poste/poste.obj");
    if (!poste1) exit(0);
  }
  glmDraw(poste1, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaPOSTE2(){
  if(!poste2){
    poste2 = glmReadOBJ("objs/poste/poste.obj");
    if (!poste2) exit(0);
  }
  glmDraw(poste2, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaPOSTE3(){
  if(!poste3){
    poste3 = glmReadOBJ("objs/poste/poste.obj");
    if (!poste3) exit(0);
  }
  glmDraw(poste3, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaPOSTE4(){
  if(!poste4){
    poste4 = glmReadOBJ("objs/poste/poste.obj");
    if (!poste4) exit(0);
  }
  glmDraw(poste4, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaPOSTE5(){
  if(!poste5){
    poste5 = glmReadOBJ("objs/poste/poste.obj");
    if (!poste5) exit(0);
  }
  glmDraw(poste5, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaPOSTE6(){
  if(!poste6){
    poste6 = glmReadOBJ("objs/poste/poste.obj");
    if (!poste6) exit(0);
  }
  glmDraw(poste6, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaPOSTE7(){
  if(!poste7){
    poste7 = glmReadOBJ("objs/poste/poste.obj");
    if (!poste7) exit(0);
  }
  glmDraw(poste7, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaPOSTE8(){
  if(!poste8){
    poste8 = glmReadOBJ("objs/poste/poste.obj");
    if (!poste8) exit(0);
  }
  glmDraw(poste8, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaPOSTE9(){
  if(!poste9){
    poste9 = glmReadOBJ("objs/poste/poste.obj");
    if (!poste9) exit(0);
  }
  glmDraw(poste9, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaPOSTE10(){
  if(!poste10){
    poste10 = glmReadOBJ("objs/poste/poste.obj");
    if (!poste10) exit(0);
  }
  glmDraw(poste10, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaPOSTE11(){
  if(!poste11){
    poste11 = glmReadOBJ("objs/poste/poste.obj");
    if (!poste11) exit(0);
  }
  glmDraw(poste11, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaPOSTE12(){
  if(!poste12){
    poste12 = glmReadOBJ("objs/poste/poste.obj");
    if (!poste12) exit(0);
  }
  glmDraw(poste12, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaPOSTE13(){
  if(!poste13){
    poste13 = glmReadOBJ("objs/poste/poste.obj");
    if (!poste13) exit(0);
  }
  glmDraw(poste13, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaPOSTE14(){
  if(!poste14){
    poste14 = glmReadOBJ("objs/poste/poste.obj");
    if (!poste14) exit(0);
  }
  glmDraw(poste14, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaBANCO1(){
  if(!banco1){
    banco1 = glmReadOBJ("objs/banco/banco.obj");
    if (!banco1) exit(0);
  }
  glmDraw(banco1, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaBANCO2(){
  if(!banco2){
    banco2 = glmReadOBJ("objs/banco/banco.obj");
    if (!banco2) exit(0);
  }
  glmDraw(banco2, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaBANCO3(){
  if(!banco3){
    banco3 = glmReadOBJ("objs/banco/banco.obj");
    if (!banco3) exit(0);
  }
  glmDraw(banco3, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaBANCO4(){
  if(!banco4){
    banco4 = glmReadOBJ("objs/banco/banco.obj");
    if (!banco4) exit(0);
  }
  glmDraw(banco4, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaBANCO5(){
  if(!banco5){
    banco5 = glmReadOBJ("objs/banco/banco.obj");
    if (!banco5) exit(0);
  }
  glmDraw(banco5, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaBANCO6(){
  if(!banco6){
    banco6 = glmReadOBJ("objs/banco/banco.obj");
    if (!banco6) exit(0);
  }
  glmDraw(banco6, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaBANCO7(){
  if(!banco7){
    banco7 = glmReadOBJ("objs/banco/banco.obj");
    if (!banco7) exit(0);
  }
  glmDraw(banco7, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaBANCO8(){
  if(!banco8){
    banco8 = glmReadOBJ("objs/banco/banco.obj");
    if (!banco8) exit(0);
  }
  glmDraw(banco8, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaBANCO9(){
  if(!banco9){
    banco9 = glmReadOBJ("objs/banco/banco.obj");
    if (!banco9) exit(0);
  }
  glmDraw(banco9, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaBANCO10(){
  if(!banco10){
    banco10 = glmReadOBJ("objs/banco/banco.obj");
    if (!banco10) exit(0);
  }
  glmDraw(banco10, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaBANCO11(){
  if(!banco11){
    banco11 = glmReadOBJ("objs/banco/banco.obj");
    if (!banco11) exit(0);
  }
  glmDraw(banco11, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaBANCO12(){
  if(!banco12){
    banco12 = glmReadOBJ("objs/banco/banco.obj");
    if (!banco12) exit(0);
  }
  glmDraw(banco12, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCADEIRAcarrossel1(){
  if(!ccadeira1){
    ccadeira1 = glmReadOBJ("objs/cadeira/cadeira.obj");
    if (!ccadeira1) exit(0);
  }
  glmDraw(ccadeira1, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCADEIRAcarrossel2(){
  if(!ccadeira2){
    ccadeira2 = glmReadOBJ("objs/cadeira/cadeira.obj");
    if (!ccadeira2) exit(0);
  }
  glmDraw(ccadeira2, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCADEIRAcarrossel3(){
  if(!ccadeira3){
    ccadeira3 = glmReadOBJ("objs/cadeira/cadeira.obj");
    if (!ccadeira3) exit(0);
  }
  glmDraw(ccadeira3, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCADEIRAcarrossel4(){
  if(!ccadeira4){
    ccadeira4 = glmReadOBJ("objs/cadeira/cadeira.obj");
    if (!ccadeira4) exit(0);
  }
  glmDraw(ccadeira4, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCADEIRAcarrossel5(){
  if(!ccadeira5){
    ccadeira5 = glmReadOBJ("objs/cadeira/cadeira.obj");
    if (!ccadeira5) exit(0);
  }
  glmDraw(ccadeira5, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCADEIRAcarrossel6(){
  if(!ccadeira6){
    ccadeira6 = glmReadOBJ("objs/cadeira/cadeira.obj");
    if (!ccadeira6) exit(0);
  }
  glmDraw(ccadeira6, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCARROSSEL(){
  if(!carrossel){
    carrossel = glmReadOBJ("objs/carrossel_voador/carrosselvoador.obj");
    if (!carrossel) exit(0);
  }
  glmDraw(carrossel, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaBARRACA1(){
  if(!barraca1){
    barraca1 = glmReadOBJ("objs/barraquinha/barraquinha.obj");
    if (!barraca1) exit(0);
  }
  glmDraw(barraca1, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaBARRACA2(){
  if(!barraca2){
    barraca2 = glmReadOBJ("objs/barraquinha/barraquinha.obj");
    if (!barraca2) exit(0);
  }
  glmDraw(barraca2, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaBARRACA3(){
  if(!barraca3){
    barraca3 = glmReadOBJ("objs/barraquinha/barraquinha.obj");
    if (!barraca3) exit(0);
  }
  glmDraw(barraca3, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaBARRACA4(){
  if(!barraca4){
    barraca4 = glmReadOBJ("objs/barraquinha/barraquinha.obj");
    if (!barraca4) exit(0);
  }
  glmDraw(barraca4, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaPLANETA1(){
  if(!planeta1){
    planeta1 = glmReadOBJ("objs/planeta1/Planeta1.obj");
    if (!planeta1) exit(0);
  }
  glmDraw(planeta1, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaPLANETA2(){
  if(!planeta2){
    planeta2 = glmReadOBJ("objs/planeta2/planeta2.obj");
    if (!planeta2) exit(0);
  }
  glmDraw(planeta2, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaPLANETA3(){
  if(!planeta3){
    planeta3 = glmReadOBJ("objs/planeta3/planeta3.obj");
    if (!planeta3) exit(0);
  }
  glmDraw(planeta3, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaPLANETA4(){
  if(!planeta4){
    planeta4 = glmReadOBJ("objs/planeta4/planeta4.obj");
    if (!planeta4) exit(0);
  }
  glmDraw(planeta4, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaMURO(){
  if(!muro){
    muro = glmReadOBJ("objs/muro/muro.obj");
    if (!muro) exit(0);
  }
  glmDraw(muro, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaBARCO(){
  if(!barco){
    barco = glmReadOBJ("objs/barco/barco.obj");
    if (!barco) exit(0);
  }
  glmDraw(barco, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaBASEbrc(){
  if(!barcoBASE){
    barcoBASE = glmReadOBJ("objs/suporte_barco/suportebarco.obj");
    if (!barcoBASE) exit(0);
  }
  glmDraw(barcoBASE, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaRG(){
  if(!rodaGIGANTE){
    rodaGIGANTE = glmReadOBJ("objs/roda_gigante/rodagigantearo.obj");
    if (!rodaGIGANTE) exit(0);
  }
  glmDraw(rodaGIGANTE, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaBASE1rg(){
  if(!rgBASE1){
    rgBASE1 = glmReadOBJ("objs/suporte_roda_gigante/suporterodagigante.obj");
    if (!rgBASE1) exit(0);
  }
  glmDraw(rgBASE1, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaBASE2rg(){
  if(!rgBASE2){
    rgBASE2 = glmReadOBJ("objs/suporte_roda_gigante/suporterodagigante.obj");
    if (!rgBASE2) exit(0);
  }
  glmDraw(rgBASE1, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaGRAMA(){
  if(!grama){
  	grama = glmReadOBJ("objs/grama/grama.obj");
  	if (!grama) exit(0);
  }
  glmDraw(grama, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCHAO(){
  if(!chao){
  	chao = glmReadOBJ("objs/chao/chao.obj");
  	if (!chao) exit(0);
  }
  glmDraw(chao, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaESTACIONAMENTO(){
  if(!estacionamento){
  	estacionamento = glmReadOBJ("objs/chao_estacionamento/chaoestacionamento.obj");
  	if (!estacionamento) exit(0);
  }
  glmDraw(estacionamento, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void teclado(unsigned char key, int x, int y) {
    switch (key) {
        case 'b':    //aperte ESC para fechar
            telaINICIO = 0;
            telaJOGO = 1;
            break;
        case 27:    //aperte ESC para fechar
            exit(0);
            break;
        case 's':   //andar pelo plano X-Z utilizando W A S D
            if(modoCAM == PRIMEIRA_PESSOA){
              xCursor += (xCursor - camera.x)/47;
              yCursor += (yCursor - camera.y)/47;
              zCursor += (zCursor - camera.z)/47;

              camera.x += (xCursor - camera.x)/47;
              camera.y += (yCursor - camera.y)/47;
              camera.z += (zCursor - camera.z)/47;
            }
            else{
              xCursor++;
            }
            break;
        case 'w':
            if(modoCAM == PRIMEIRA_PESSOA){
              xCursor -= (xCursor - camera.x)/47;
              yCursor -= (yCursor - camera.y)/47;
              zCursor -= (zCursor - camera.z)/47;

              camera.x -= (xCursor - camera.x)/47;
              camera.y -= (yCursor - camera.y)/47;
              camera.z -= (zCursor - camera.z)/47;
            }
            else{
              xCursor--;
            }
            break;
        case 'a':
            zCursor++;
            break;
        case 'd':
            zCursor--;
            break;
        case '7':
            modoCAM = BRINQUEDO_1_2_3; //RODA GIGANTE, CARROSEL E BARCO
            break;
        case '6':
            modoCAM = BRINQUEDO3; //BARCO
            break;
        case '5':
            modoCAM = BRINQUEDO2; //CARROSEL SUPERIOR
            break;
        case '4':
            modoCAM = BRINQUEDO1; //RODA GIGANTE
            break;
        case '3':
            modoCAM = TERCEIRA_PESSOA;
            break;
        case '2':
            modoCAM = PRIMEIRA_PESSOA;
            break;
        case '1':
            modoCAM = ESTATICA;
        default:
            break;
    }
}

//capturar posicionamento do mouse
void posicionaCamera(int x, int y){
    // variáveis que guardam o vetor 2D de movimento do mouse na tela
    // xMouse e yMouse são os valores de x e y no frame anterior
    float xChange = x - xMouse;
    float yChange = y - yMouse;

    // este exemplo usa coordenadas esféricas para controlar a câmera...
    // teta e phi guardam a conversão do vetor 2D para um espaço 3D
    // com coordenada esférica
    teta = (teta + xChange/150);
    phi = (phi - yChange/150);

    // guarda o x e y do mouse para usar naint  comparação do próximo frame
    xMouse = x;
    yMouse = y;
}


// callback de atualização
void atualiza(int time) {
    glutPostRedisplay();
    glutTimerFunc(time, atualiza, time);
}

void redimensiona(int w, int h){
    glViewport (0, 0, w, h);                //define a proporção da janela de visualização
    glMatrixMode (GL_PROJECTION);           //define o tipo de matriz de transformação que será utilizada
    glLoadIdentity();                       //carrega a matriz identidade do tipo GL_PROJECTION configurado anteriormente

    if(telaJOGO == 1){
      glEnable(GL_DEPTH_TEST);                // Ativa o Z buffer
      gluPerspective(60.0, (float)w/(float)h, 0.2, 400.0);    //funciona como se fosse o glOrtho, mas para o espaço 3D
    }
    if(telaINICIO == 1){
      glOrtho(-1000, 1000, -1000, 1000, -1.0, 1.0);
    }
    glMatrixMode(GL_MODELVIEW);                             //ativa o modo de matriz de visualização para utilizar o LookAt
}

void inicializa(){
    glClearColor(1,1,1,1);
    glEnable(GL_BLEND);                                //ativa a mesclagem de cores
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //ativando o blend, podemos criar objetos transparentes

    idTexturabackgroundINICIO = carregaTextura("telas/telaINICIO.png");

      /*  park_music.setLoop(true);
        park_music.setVolume(volumeMUSIC);
        park_music.play(); */

      xCursor = 0.709259;                                       //a câmera começa olhando para o ponto 0
      yCursor = 8.896676;
      zCursor = -7.770996;

      if(telaJOGO == 1){
        // Lighting set up
      	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
      	glEnable(GL_LIGHTING);
      	glEnable(GL_LIGHT0);

      	// Set lighting intensity and color
      	GLfloat qaAmbientLight[]	= {1.0, 1.0, 0.9, 1.0};
      	GLfloat qaDiffuseLight[]	= {1.0, 0.8, 0.8, 1.0};
      	GLfloat qaSpecularLight[]	= {1.0, 1.0, 1.0, 1.0};
      	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
      	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
      	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

      	// Set the light position
      	GLfloat qaLightPosition[]	= {0, 10, 0};
      	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);

        // Set material properties
        GLfloat qaBlack[] = {0.0, 0.0, 1.0, 1.0};
        GLfloat qaGreen[] = {0.7, 1.0, 0.45, 1.0};
        GLfloat qaWhite[] = {1.0, 1.0, 1.0, 1.0};
        glMaterialfv(GL_FRONT, GL_AMBIENT, qaGreen);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, qaGreen);
        glMaterialfv(GL_FRONT, GL_SPECULAR, qaWhite);
        glMaterialf(GL_FRONT, GL_SHININESS, 0.6);
    }


  }

//função que desenhará tudo o que aparece na tela
void desenhaCena() {

    if(telaJOGO == 1){
      MenuTheme.setVolume(0);

      //esfera de raio 100
      camera.x = 10 * sin(phi) * cos(teta);  //coordenada x denotada em coordenadas esféricas
      camera.z = 10 * sin(phi) * sin(teta); //coordenada z denotada em coordenadas esféricas
      camera.y = 10 * cos(phi);          //coordenada y denotada em coordenadas esféricas

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // carrega a matriz identidade do modelo de visualização,
      // sempre utilize antes de usar LookAt
      glLoadIdentity();

      //define um LookAt diferente para cada modo da câmera, veja abaixo o
      // uso de cada um
      switch (modoCAM) {
      case BRINQUEDO_1_2_3:
          gluLookAt(0, 10, 9,
                    0, 9, 0,
                    0, 1, 0);
              break;
      case BRINQUEDO3:
          gluLookAt(-5, 8.5, 4,
                    -1, 9, 0,
                    0, 1, 0);
              break;
      case BRINQUEDO2:
          gluLookAt(3, 10, 5,
                    -15, 6, 0,
                    0, 1, 0);
              break;
      case BRINQUEDO1:
          gluLookAt(5, 9, 4,
                    0, 9, 0,
                    0, 1, 0);
              break;
      case TERCEIRA_PESSOA:
          gluLookAt(xCursor+camera.x, camera.y, zCursor+camera.z,//câmera posicionada na casca da esfera calculada (terceira pessoa)
              xCursor+0, 0, zCursor+0,                          //centro da esfera, o ponto em que estamos olhando
              0, 1, 0);                                        //vetor UP, apontando para o eixo Y (para cima)
          break;

      case PRIMEIRA_PESSOA:
          gluLookAt( xCursor, yCursor, zCursor,                    //já aqui, a câmera está posicionada no centro da esfera
              xCursor+camera.x, camera.y, zCursor+camera.z,     //e a câmera estará olhando para a casca da esfera (primeira pessoa)
              0, 1, 0);                                        //vetor UP, apontando para o eixo Y (para cima)
          break;

        case ESTATICA:
        default:
            gluLookAt(20, 13, 1,   // Z=200
                      0, 9, 0,    // (0, 0, 0) origem do mundo
                      0, 1, 0);  //nesse exemplo mais simples, estamos no ponto Z=200 olhando para o ponto 0
            break;
      }
      glColor3f(1,1,1);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      glEnable(GL_LIGHTING);


      glPushMatrix();
        glTranslatef(0,7.549,0);
        //glRotatef(rotacao,0,1,0);
        desenhaGRAMA();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(0,7.541,0);
        desenhaCHAO();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(0,7.72,-4.556);
        desenhaESTACIONAMENTO();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(2.542,8.694,2.23);
        glRotatef(rotacaoRG,0,0,1);
        desenhaRG();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(2.539,8.278,1.883);
        desenhaBASE1rg();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(2.539,8.278,2.639);
        desenhaBASE2rg();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(-2.388,8.716,2.261);
        glRotatef(rotacaoBARCO,0,0,1);
        desenhaBARCO();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(-2.376,8.713,2.446);
        desenhaBASEbrc();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(0,8.641,-3.603);
        desenhaMURO();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(8.209,10.604 + movPlanet,-6.428);
        desenhaPLANETA1();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(4.167,10.495 + movPlanet,8.817);
        desenhaPLANETA2();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(-5.588,9.749 + movPlanet,-7.788);
        desenhaPLANETA3();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(-8.178,11.184 + movPlanet,5.786);
        desenhaPLANETA4();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(4.935,7.965,0.994);
        desenhaBARRACA1();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(-4.935,7.965,0.994);
        glRotatef(180,0,1,0);
        desenhaBARRACA2();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(0.733,7.965,-2.921);
        desenhaBARRACA3();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(-0.733,7.965,-2.921);
        glRotatef(180,0,1,0);
       desenhaBARRACA4();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(0,9.117,4.237);
       desenhaCARROSSEL();
      glPopMatrix();


      for(int i = 0; i < 6; i ++){
       glPushMatrix();
       glTranslatef(CCADEIRAx[i],CCADEIRAy[i],CCADEIRAz[i]);
       glRotatef(CCADEIRArotY[i],0,1,0);
       if(i == 0){
        glScalef(0.229,0.229,0.229);
        desenhaCADEIRAcarrossel1();
        }
       if(i == 1){
        glScalef(0.229,0.229,0.229);
        desenhaCADEIRAcarrossel2();
        }
       if(i == 2){
        glScalef(0.229,0.229,0.229);
        desenhaCADEIRAcarrossel3();
        }
       if(i == 3){
        glScalef(0.229,0.229,0.229);
        desenhaCADEIRAcarrossel4();
        }
       if(i == 4){
        glScalef(0.229,0.229,0.229);
        desenhaCADEIRAcarrossel5();
        }
       if(i == 5){
        glScalef(0.229,0.229,0.229);
        desenhaCADEIRAcarrossel6();
        }
        glPopMatrix();
      }

      glPushMatrix();
        glTranslatef(-0.502,7.865,0);
        glRotatef(90,0,1,0);
        desenhaBANCO1();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(-0.502,7.865,-1.16);
        glRotatef(90,0,1,0);
        desenhaBANCO2();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(0.502,7.865,-1.16);
        glRotatef(270,0,1,0);
        desenhaBANCO3();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(0.502,7.865,0);
        glRotatef(270,0,1,0);
        desenhaBANCO4();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(0.502,7.865,1.885);
        glRotatef(270,0,1,0);
        desenhaBANCO5();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(-0.502,7.865,1.885);
        glRotatef(90,0,1,0);
        desenhaBANCO6();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(0.877,7.865,0.404);
        desenhaBANCO7();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(2.521,7.865,0.404);
        desenhaBANCO8();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(-0.877,7.865,0.404);
        desenhaBANCO9();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(-2.521,7.865,0.404);
        desenhaBANCO10();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(-0.877,7.865,1.509);
        glRotatef(180,0,1,0);
        desenhaBANCO11();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(0.877,7.865,1.509);
        glRotatef(180,0,1,0);
        desenhaBANCO12();
      glPopMatrix();

      for(int i = 0; i < 14; i ++){
       glPushMatrix();
       glTranslatef(POSTEx[i],POSTEy[i],POSTEz[i]);
       glRotatef(POSTErotY[i],0,1,0);
       if(i == 0){
        desenhaPOSTE1();
        }
       if(i == 1){
        desenhaPOSTE2();
        }
       if(i == 2){
        desenhaPOSTE3();
        }
       if(i == 3){
        desenhaPOSTE4();
        }
       if(i == 4){
        desenhaPOSTE5();
        }
       if(i == 5){
        desenhaPOSTE6();
        }
       if(i == 6){
         desenhaPOSTE7();
         }
       if(i == 7){
         desenhaPOSTE8();
         }
       if(i == 8){
         desenhaPOSTE9();
         }
       if(i == 9){
         desenhaPOSTE10();
         }
       if(i == 10){
         desenhaPOSTE11();
         }
       if(i == 11){
         desenhaPOSTE12();
         }
       if(i == 12){
          desenhaPOSTE13();
          }
       if(i == 13){
          desenhaPOSTE14();
        }
        glPopMatrix();
      }

      for(int i = 0; i < 12; i ++){
       glPushMatrix();
       glRotatef(rotacaoRG,0,1,0);
       glTranslatef(CvoadoraX[i],CvoadoraY[i],CvoadoraZ[i]);
       glRotatef(CvoadoraROTy[i],0,1,0);
       if(i == 0){
        desenhaCVoadora1();
        }
       if(i == 1){
        desenhaCVoadora2();
        }
       if(i == 2){
        desenhaCVoadora3();
        }
       if(i == 3){
        desenhaCVoadora4();
        }
       if(i == 4){
        desenhaCVoadora5();
        }
       if(i == 5){
        desenhaCVoadora6();
        }
       if(i == 6){
         desenhaCVoadora7();
         }
       if(i == 7){
         desenhaCVoadora8();
         }
       if(i == 8){
         desenhaCVoadora9();
         }
       if(i == 9){
         desenhaCVoadora10();
         }
       if(i == 10){
         desenhaCVoadora11();
         }
       if(i == 11){
         desenhaCVoadora12();
         }
        glPopMatrix();
      }

      for(int i = 0; i < 7; i ++){
       glPushMatrix();
       glTranslatef(CarroX[i],CarroY[i],CarroZ[i]);
       glRotatef(CarroROTy[i],0,1,0);
       if(i == 0){
        desenhaCARRO1();
        }
       if(i == 1){
        desenhaCARRO2();
        }
       if(i == 2){
        desenhaCARRO3();
        }
       if(i == 3){
        desenhaCARRO4();
        }
       if(i == 4){
        desenhaCARRO5();
        }
       if(i == 5){
        desenhaCARRO6();
        }
       if(i == 6){
        desenhaCARRO7();
        }
        glPopMatrix();
      }

      for(int i = 0; i < 4; i ++){
       glPushMatrix();
       glTranslatef(LixeiraX[i],LixeiraY[i],LixeiraZ[i]);
       glRotatef(LixeiraROTy[i],0,1,0);
       if(i == 0){
        desenhaLIXEIRA1();
        }
       if(i == 1){
        desenhaLIXEIRA2();
        }
       if(i == 2){
        desenhaLIXEIRA3();
        }
       if(i == 3){
        desenhaLIXEIRA4();
        }
        glPopMatrix();
      }

      glPushMatrix();
        glTranslatef(-2.441,8.654,-3.62);
        desenhaPLACAnd();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(2.441,8.654,-3.62);
        desenhaPLACAnp();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(2.497,7.984,1.632);
        desenhaPLACArg();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(-0.016,7.984,3.576);
        desenhaPLACAcar();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(-2.369,7.984,1.632);
        desenhaPLACAbarc();
      glPopMatrix();

      for(int i = 0; i < 10; i ++){
       glPushMatrix();
       glTranslatef(CabineX[i],CabineY[i],CabineZ[i]);
       glRotatef(CabineROTy[i],0,1,0);
       if(i == 0){
        desenhaCABINE1();
        }
       if(i == 1){
        desenhaCABINE2();
        }
       if(i == 2){
        desenhaCABINE3();
        }
       if(i == 3){
        desenhaCABINE4();
        }
       if(i == 4){
        desenhaCABINE5();
        }
       if(i == 5){
        desenhaCABINE6();
        }
       if(i == 6){
        desenhaCABINE7();
        }
       if(i == 7){
        desenhaCABINE8();
       }
       if(i == 8){
        desenhaCABINE9();
       }
       if(i == 9){
        desenhaCABINE10();
       }
        glPopMatrix();
      }

      glDisable(GL_LIGHTING);

    //  park_music.setLoop(true);
       park_music.setVolume(100);
    //  park_music.play();

      rotacaoRG = rotacaoRG - 0.15;
      //rotacaoBARCO = rotacaoBARCO + 0.15;
    }

    if(telaINICIO == 1){
      desenhaTELAinicial();
      MenuTheme.setLoop(true);
      MenuTheme.setVolume(100);
    }



    redimensiona(glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
    glutSwapBuffers();

}


int coodX(int x) {
  return (glutGet(GLUT_WINDOW_WIDTH) * x) / 1024;
}

int coodY(int y) {
  return (glutGet(GLUT_WINDOW_HEIGHT) * y) / 720;
}

void cliqueMOUSE(int button, int state,int x, int y){
  if(telaINICIO == 1){
    if(((x > coodX(420)) && (x < coodX(685))) && ((y > coodY(460)) && (y < coodY(510)))){
      if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
        MenuSelect_sound.setVolume(100);
        MenuSelect_sound.play();
        telaJOGO = 1;
        telaINICIO = 0;
      }
    }

    if(((x > 420) && (x < 685)) && ((y > 535) && (y < 685))){
      if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
        MenuSelect_sound.setVolume(100);
        MenuSelect_sound.play();
        //CONFIGURACOES
      }
    }

    if(((x > 420) && (x < 685)) && ((y > 615) && (y < 665))){
      if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
        MenuSelect_sound.setVolume(100);
        MenuSelect_sound.play();
        exit(0);
      }
    }



  }

}

int main(int argc, char *argv[]) {

    if(!park_music.openFromFile("music/mashup.ogg"))
      printf("\n ERRO AO CARREGAR mashup.ogg");

    if(!MenuTheme.openFromFile("music/SmashBrosBrawl.ogg"))
      printf("\n ERRO AO CARREGAR SmashBrosBrawl.ogg");

    if(!MenuSelect_sound.openFromFile("music/MenuSelectSOUND.ogg"))
      printf("\n ERRO AO CARREGAR MenuSelect.ogg");

    glutInit(&argc, argv);
    glutInitContextVersion(1, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1024, 720);
    glutInitWindowPosition (0, 0);

    glutCreateWindow("twiceLAND -TP2 PARK (JIHYO)");

    if(telaINICIO == 1){
      MenuTheme.setLoop(true);
      MenuTheme.setVolume(100);
      MenuTheme.play();
    }

    park_music.setLoop(true);
   park_music.setVolume(0);
    park_music.play();



    //MouseFunc utilizada para clique do mouse nos menus/telas
    glutMouseFunc(cliqueMOUSE);
    //glutEnterGameMode();                 // fullscreen baby! (retire o comentário para ativar a tela cheia)
    if(telaJOGO == 1){
      glutSetCursor(GLUT_CURSOR_NONE);     // esconde o cursor do sistema
    }

    glutDisplayFunc(desenhaCena);
    glutReshapeFunc(redimensiona);
    // atualização próxima de 60fps (1000/16) = 62.5 fps
    glutTimerFunc(16, atualiza, 16);

    glutKeyboardFunc(teclado);
    // usada para capturar o posicionamento do mouse
    glutPassiveMotionFunc(posicionaCamera);

    inicializa();
    glutMainLoop();



    return 0;
}
