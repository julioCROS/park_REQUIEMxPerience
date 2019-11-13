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
#include <time.h>

sf::Music park_music;
sf::Music MenuSelect_sound;
sf::Music MenuTheme;
sf::Music Awaken;
sf::Music Twice;

GLuint idTexturabackgroundINICIO;
GLuint idTexturabackgroundCREDITOS;

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

int volumeMUSIC = 100;

float rotacaoCLIPES = 0;
int t=0;
bool fog = 0;
float corFog[] = {0.96862745098,0.49411764705,0.49411764705};
float DensidadeFog = 0.0015;

int dia = 0;

float corAux = 0;

int tocou = 0;

int telaINICIO = 1;
int telaJOGO = 0;
int telaCREDITOS = 0;

float rotacaoBRINQUEDOS1 = 0.1;
float rotacaoBRINQUEDOS2 = 0.1;
float rotacaoBARCO = 0.1;
int estadoBARCO = 0;

float movELEV = 0;
int estadoELEV = 0;

float movPlanet1 = 0.1;
int estadoPL1 = 0;
float movPlanet2 = 0.1;
int estadoPL2 = 0;

float posLUZx = 0;
float posLUZy = 30;
float posLUZz = 0;

float intensidadeLUZ = 0;
float cont = 4;

GLfloat clipeX[100];
GLfloat clipeY[100];
GLfloat clipeZ[100];

float movCLIP = 0;

int gerou = 0;

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

float posX[10] = {0.583, 0.158, -0.278, -0.627, -0.747, -0.524, -0.119, 0.341, 0.612, 0.787};
float posY[10] = {0.464, 0.614, 0.579, 0.294, -0.119, -0.606, -0.788, -0.743, -0.436, -0.012};


float XicaraX[8] = {3.085,4.353,3.094,1.693,2.345,3.128,3.879,3.082};
float XicaraY[8] = {7.825,7.825,7.825,7.825,7.825,7.825,7.825,7.825};
float XicaraZ[8] = {-2.286,-1.42,-0.24,-1.551,-1.531,-2.828,-1.42,-0.776};
float XicaraROTy[8] = {0,0,0,0,180,180,180,180};

GLMmodel* grama = NULL;
GLMmodel* chao = NULL;
GLMmodel* estacionamento = NULL;

GLMmodel* banco = NULL;

GLMmodel* rodaGIGANTE = NULL;
GLMmodel* rgBASE = NULL;

GLMmodel* barco = NULL;
GLMmodel* barcoBASE = NULL;

GLMmodel* muro = NULL;

GLMmodel* planeta1 = NULL;
GLMmodel* planeta2 = NULL;
GLMmodel* planeta3 = NULL;
GLMmodel* planeta4 = NULL;

GLMmodel* barraca = NULL;

GLMmodel* carrossel = NULL;
GLMmodel* ccadeira = NULL;

GLMmodel* poste = NULL;

GLMmodel* cvoadora = NULL;

GLMmodel* carro = NULL;


GLMmodel* lixeira = NULL;

GLMmodel* placaND = NULL;
GLMmodel* placaNP = NULL;
GLMmodel* placaRG = NULL;
GLMmodel* placaCar = NULL;
GLMmodel* placaBarc = NULL;

GLMmodel* cabine = NULL;

GLMmodel* BaseElev = NULL;
GLMmodel* BancoElev = NULL;
GLMmodel* SegurancaElev = NULL;

GLMmodel* BaseXicara = NULL;
GLMmodel* BaseDasXicaras = NULL;
GLMmodel* Xicara = NULL;

GLMmodel* CasaFliperama = NULL;

GLMmodel* fundo = NULL;

GLMmodel* clipes = NULL;

// estrutura de dados que representará as coordenadas da câmera
struct {
  float x, y, z;
  float targetX, targetY, targetZ;
} camera;

void desenhaTELAcreditos(){
  // Habilita o uso de texturas
  glEnable(GL_TEXTURE_2D);
  // Começa a usar a textura que criamos
  glBindTexture(GL_TEXTURE_2D, idTexturabackgroundCREDITOS);

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

void desenhaTELAinicial(){
   glColor3f(corAux,corAux,corAux);
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

void desenhaCLIPES(){
  if(!clipes){
    clipes = glmReadOBJ("objs/paperclip/paperclip.obj");
    if (!clipes) exit(0);
  }
  glmDraw(clipes, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaFUNDO(){
  if(!fundo){
    fundo = glmReadOBJ("objs/cubofundotextura/fundopreto.obj");
    if (!fundo) exit(0);
  }
  glmDraw(fundo, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCASAfliperama(){
  if(!CasaFliperama){
    CasaFliperama = glmReadOBJ("objs/casa_filiperama/casafiliperama.obj");
    if (!CasaFliperama) exit(0);
  }
  glmDraw(CasaFliperama, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaXICARA(){
  if(!Xicara){
    Xicara = glmReadOBJ("objs/xicara/xicarajunto.obj");
    if (!Xicara) exit(0);
  }
  glmDraw(Xicara, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaBASEdasXicara(){
  if(!BaseDasXicaras){
    BaseDasXicaras = glmReadOBJ("objs/basexicara/basexicarajunto.obj");
    if (!BaseDasXicaras) exit(0);
  }
  glmDraw(BaseDasXicaras, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaBASExicara(){
  if(!BaseXicara){
    BaseXicara = glmReadOBJ("objs/basebrinquedoxicara/basebrinquedoxicara.obj");
    if (!BaseXicara) exit(0);
  }
  glmDraw(BaseXicara, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaSEGURANCAelev(){
  if(!SegurancaElev){
    SegurancaElev = glmReadOBJ("objs/seguranca_banco_elevador/segurancabancoelevador.obj");
    if (!SegurancaElev) exit(0);
  }
  glmDraw(SegurancaElev, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaBANCOelev(){
  if(!BancoElev){
    BancoElev = glmReadOBJ("objs/banco_elevador/bancoelevador.obj");
    if (!BancoElev) exit(0);
  }
  glmDraw(BancoElev, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaBASEelev(){
  if(!BaseElev){
    BaseElev = glmReadOBJ("objs/base_elevador/baseelevador.obj");
    if (!BaseElev) exit(0);
  }
  glmDraw(BaseElev, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCABINE(){
  if(!cabine){
    cabine = glmReadOBJ("objs/cabinerodagigante/cabine.obj");
    if (!cabine) exit(0);
  }
  glmDraw(cabine, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
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

void desenhaLIXEIRA(){
  if(!lixeira){
    lixeira = glmReadOBJ("objs/lixo/lixo.obj");
    if (!lixeira) exit(0);
  }
  glmDraw(lixeira, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCARRO(){
  if(!carro){
    carro = glmReadOBJ("objs/carrinho/carrinho.obj");
    if (!carro) exit(0);
  }
  glmDraw(carro, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCVoadora(){
  if(!cvoadora){
    cvoadora = glmReadOBJ("objs/cadeira/cadeira.obj");
    if (!cvoadora) exit(0);
  }
  glmDraw(cvoadora, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaPOSTE(){
  if(!poste){
    poste = glmReadOBJ("objs/poste/poste.obj");
    if (!poste) exit(0);
  }
  glmDraw(poste, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaBANCO(){
  if(!banco){
    banco = glmReadOBJ("objs/banco/banco.obj");
    if (!banco) exit(0);
  }
  glmDraw(banco, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCADEIRAcarrossel(){
  if(!ccadeira){
    ccadeira = glmReadOBJ("objs/cadeiracarrosselvoador/cadeiracarrosselvoador.obj");
    if (!ccadeira) exit(0);
  }
  glmDraw(ccadeira, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaCARROSSEL(){
  if(!carrossel){
    carrossel = glmReadOBJ("objs/carrossel_voador/carrosselvoador.obj");
    if (!carrossel) exit(0);
  }
  glmDraw(carrossel, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
}

void desenhaBARRACA(){
  if(!barraca){
    barraca = glmReadOBJ("objs/barraquinha/barraquinha.obj");
    if (!barraca) exit(0);
  }
  glmDraw(barraca, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
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

void desenhaBASErg(){
  if(!rgBASE){
    rgBASE = glmReadOBJ("objs/suporte_roda_gigante/suporterodagigante.obj");
    if (!rgBASE) exit(0);
  }
  glmDraw(rgBASE, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);
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
        case 'f':
            fog = !fog;
            break;
        case 27:    //aperte ESC para fechar
            exit(0);
            break;
        case 's':   //andar pelo plano X-Z utilizando W A S D
            if(modoCAM == PRIMEIRA_PESSOA){
              xCursor += (xCursor - camera.x)/61;
              yCursor += (yCursor - camera.y)/61;
              zCursor += (zCursor - camera.z)/61;
            }
            else{
              xCursor++;
            }
            break;
        case 'w':
            if(modoCAM == PRIMEIRA_PESSOA){
             xCursor -= (xCursor - camera.x)/61;
              yCursor -= (yCursor - camera.y)/61;
              zCursor -= (zCursor - camera.z)/61;
            }
            else{
              xCursor--;
            }
            break;
        case 'a':
            if(modoCAM != PRIMEIRA_PESSOA)
              zCursor++;
            break;
        case 'd':
            if(modoCAM != PRIMEIRA_PESSOA)
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
            break;
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

    if((telaJOGO == 1)){
      glEnable(GL_DEPTH_TEST);                // Ativa o Z buffer
      gluPerspective(60.0, (float)w/(float)h, 0.2, 400.0);    //funciona como se fosse o glOrtho, mas para o espaço 3D
    }
    if((telaINICIO == 1) || (telaCREDITOS == 1)||(t==1)){
      glOrtho(-1000, 1000, -1000, 1000, -1.0, 1.0);
    }
    glMatrixMode(GL_MODELVIEW);                             //ativa o modo de matriz de visualização para utilizar o LookAt
}

void inicializa(){
    glClearColor(1,1,1,1);
    glEnable(GL_BLEND);                                //ativa a mesclagem de cores
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //ativando o blend, podemos criar objetos transparentes

    idTexturabackgroundINICIO = carregaTextura("telas/telaINICIO.png");
    idTexturabackgroundCREDITOS = carregaTextura("telas/telaCREDITOS.png");

      xCursor = 0.709259;                                       //a câmera começa olhando para o ponto 0
      yCursor = 8.896676;
      zCursor = -7.770996;

}

void configFog(){
  glFogi(GL_FOG_MODE, GL_LINEAR);        // Linear, exp. ou exp²
  glFogfv(GL_FOG_COLOR, corFog);         // Cor
  glFogf(GL_FOG_DENSITY,DensidadeFog);      // Densidade
  glHint(GL_FOG_HINT, GL_DONT_CARE);  // Não aplicar se não puder
  glFogf(GL_FOG_START, 0.0f);         // Profundidade inicial
  glFogf(GL_FOG_END, 200.0f);           // Profundidade final

  if(fog == 1)
    glEnable(GL_FOG);
  if(fog == 0)
    glDisable(GL_FOG);
}

//função que desenhará tudo o que aparece na tela
void desenhaCena() {
    if(telaJOGO == 1){
      MenuTheme.setVolume(0);

      if(tocou == 0){
        park_music.setLoop(true);
        park_music.setVolume(100);
        park_music.play();
        tocou++;
      }

      // Lighting set up
      glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
      glEnable(GL_LIGHTING);
      glEnable(GL_LIGHT0);
      glEnable(GL_LIGHT1);

      // Set lighting intensity and color
      GLfloat qaAmbientLight[]	= {1.0, 1.0, 0.9, 1.0};
      GLfloat qaDiffuseLight[]	= {1.0, 0.8, 0.8, 1.0};
      GLfloat qaSpecularLight[]	= {1.0, 1.0, 1.0, 1.0};
      glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
      glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
      glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);


      // Set the light position
      GLfloat qaLight0Position[]	= {posLUZx, posLUZy, posLUZz};
      glLightfv(GL_LIGHT0, GL_POSITION, qaLight0Position);

      // Set material properties
      GLfloat qaBlack[] = {1.0, 1.0, 1.0, 1.0};
      GLfloat qaGreen[] = {1.0, 1.0, 0.75, 1.0};
      GLfloat qaWhite[] = {1.0, 1.0, 1.0, 1.0};
      glMaterialfv(GL_FRONT, GL_AMBIENT, qaGreen);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, qaGreen);
      glMaterialfv(GL_FRONT, GL_SPECULAR, qaWhite);
      glMaterialf(GL_FRONT, GL_SHININESS, intensidadeLUZ);


      //esfera de raio 50
      camera.x = 50 * sin(phi) * cos(teta);  //coordenada x denotada em coordenadas esféricas
      camera.z = 50 * sin(phi) * sin(teta); //coordenada z denotada em coordenadas esféricas
      camera.y = 50 * cos(phi);          //coordenada y denotada em coordenadas esféricas

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
        glTranslatef(2.542,8.820,2.23);
        glRotatef(rotacaoBRINQUEDOS1,0,0,1);
        for(int i = 0; i < 10; i++){
          glPushMatrix();
             glTranslatef(posX[i], posY[i], 0);
             glRotatef(-rotacaoBRINQUEDOS1,0,0,1);
             desenhaCABINE();
           glPopMatrix();
        }
        desenhaRG();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(2.539,8.278,1.883);
        desenhaBASErg();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(2.539,8.278,2.639);
        desenhaBASErg();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(-2.388,8.716,2.261);
        glTranslatef(0,0.85,0);
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
        glTranslatef(8.209,10.604 + movPlanet1,-6.428);
        desenhaPLANETA1();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(4.167,10.495 + movPlanet1,8.817);
        desenhaPLANETA2();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(-5.588,9.749 + movPlanet2,-7.788);
        desenhaPLANETA3();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(-8.178,11.184 + movPlanet2,5.786);
        desenhaPLANETA4();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(4.935,7.965,0.994);
        desenhaBARRACA();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(-4.935,7.965,0.994);
        glRotatef(180,0,1,0);
        desenhaBARRACA();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(0.733,7.965,-2.921);
        desenhaBARRACA();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(-0.733,7.965,-2.921);
        glRotatef(180,0,1,0);
       desenhaBARRACA();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(0,9.117,4.237);
        glRotatef(rotacaoBRINQUEDOS2,0,1,0);
       desenhaCARROSSEL();
      glPopMatrix();

       glPushMatrix();
         glTranslatef(0.013,9.286,4.24);
         glRotatef(-60,0,1,0);
         glRotatef(rotacaoBRINQUEDOS2,0,1,0);
         desenhaCADEIRAcarrossel();
       glPopMatrix();

      glPushMatrix();
        glTranslatef(-0.502,7.865,0);
        glRotatef(90,0,1,0);
        desenhaBANCO();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(-0.502,7.865,-1.16);
        glRotatef(90,0,1,0);
        desenhaBANCO();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(0.502,7.865,-1.16);
        glRotatef(270,0,1,0);
        desenhaBANCO();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(0.502,7.865,0);
        glRotatef(270,0,1,0);
        desenhaBANCO();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(0.502,7.865,1.885);
        glRotatef(270,0,1,0);
        desenhaBANCO();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(-0.502,7.865,1.885);
        glRotatef(90,0,1,0);
        desenhaBANCO();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(0.877,7.865,0.404);
        desenhaBANCO();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(2.521,7.865,0.404);
        desenhaBANCO();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(-0.877,7.865,0.404);
        desenhaBANCO();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(-2.521,7.865,0.404);
        desenhaBANCO();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(-0.877,7.865,1.509);
        glRotatef(180,0,1,0);
        desenhaBANCO();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(0.877,7.865,1.509);
        glRotatef(180,0,1,0);
        desenhaBANCO();
      glPopMatrix();

      for(int i = 0; i < 14; i ++){
       glPushMatrix();
       glTranslatef(POSTEx[i],POSTEy[i],POSTEz[i]);
       glRotatef(POSTErotY[i],0,1,0);
       desenhaPOSTE();
       glPopMatrix();
      }

      for(int i = 0; i < 12; i ++){
       glPushMatrix();
       glRotatef(rotacaoBRINQUEDOS1,0,1,0);
       glTranslatef(CvoadoraX[i],CvoadoraY[i],CvoadoraZ[i]);
       glRotatef(CvoadoraROTy[i],0,1,0);
       desenhaCVoadora();
       glPopMatrix();
      }

      for(int i = 0; i < 7; i ++){
       glPushMatrix();
       glTranslatef(CarroX[i],CarroY[i],CarroZ[i]);
       glRotatef(CarroROTy[i],0,1,0);
       desenhaCARRO();
       glPopMatrix();
      }

      for(int i = 0; i < 4; i ++){
       glPushMatrix();
       glTranslatef(LixeiraX[i],LixeiraY[i],LixeiraZ[i]);
       glRotatef(LixeiraROTy[i],0,1,0);
       desenhaLIXEIRA();
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

      /* glPushMatrix();
         glTranslatef(2.54,8.696,2.198);
         glRotatef(0,0,1,0);
         glRotatef(rotacaoBRINQUEDOS1,0,0,1);
         desenhaCABINE();
       glPopMatrix();*/

      glPushMatrix();
        glTranslatef(-2.813,7.473 + movELEV,-1.551);
        glScalef(0.234,0.234,0.234);
        desenhaBANCOelev();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(-2.813,7.473,-1.551);
        glScalef(0.234,0.234,0.234);
        desenhaBASEelev();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(-2.813,7.473 + movELEV,-1.551);
        glScalef(0.234,0.234,0.234);
        desenhaSEGURANCAelev();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(3.088,7.667,-1.508);
        glScalef(0.24,0.24,0.24);
        glRotatef(rotacaoBRINQUEDOS2,0,1,0);
        desenhaBASExicara();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(3.088,7.890,-1.529);
        glRotatef(rotacaoBRINQUEDOS2,0,1,0);
        desenhaBASEdasXicara();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(3.076, 8.019,-1.541);
        glRotatef(rotacaoBRINQUEDOS2,0,1,0);
        desenhaXICARA();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(-2.502,12.607,9.227);
        glRotatef(rotacaoBRINQUEDOS1,0,1,0);
        glScalef(0.47,0.47,0.47);
        desenhaGRAMA();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(-2.337,12.552,9.203);
        glScalef(0.342,0.342,0.342);
        desenhaCASAfliperama();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(xCursor,yCursor,zCursor);
        glScalef(0.6,0.6,0.6);
        desenhaFUNDO();
      glPopMatrix();


      if(gerou == 0){
        for(int i = 0; i < 50; i++){
          clipeX[i] = rand() % (12 + 1 + 12) - 12;
          clipeY[i] = rand() % (-5 + 1 + 20) - 20;
          clipeZ[i] = rand() % (11 + 1 + 11) - 11;
        }
        for(int i = 50; i < 100; i++){
          clipeX[i] = rand() % (12 + 1 + 12) - 12;
          clipeY[i] = 9 + (rand() % (-5 + 1 + 20) - 20);
          clipeZ[i] = rand() % (11 + 1 + 11) - 11;
        }
        gerou = 1;
      }

      for(int i = 0; i < 100; i++){
        glPushMatrix();
            glTranslatef(clipeX[i], clipeY[i] + movCLIP, clipeZ[i]);
            glRotatef(rotacaoCLIPES,4,3,2);
            glScalef(0.1,0.1,0.1);
            desenhaCLIPES();
        glPopMatrix();
      }

      glDisable(GL_LIGHTING);

      configFog();

      glutSetCursor(GLUT_CURSOR_NONE);     // esconde o cursor do sistema

      rotacaoBRINQUEDOS1 = rotacaoBRINQUEDOS1 - 1;
      rotacaoBRINQUEDOS2 = rotacaoBRINQUEDOS2 - 0.9;
      rotacaoCLIPES = rotacaoCLIPES + 12;

      movCLIP = movCLIP + 0.05;

      for(int i = 0; i < 100; i++){
        if(clipeY[i] + movCLIP > 40){
          clipeY[i] = (rand() % (-5 + 1 + 20) - 20);
          movCLIP = 0;
          gerou = 0;
        }
      }


      //CICLO DIA NOITE

      if(dia == 0){
        intensidadeLUZ = intensidadeLUZ - 0.1;
      }

      if(intensidadeLUZ >= 15){
        dia = 0;
      }

      if(dia == 1){
        intensidadeLUZ = intensidadeLUZ + 0.1;
      }

      if(intensidadeLUZ <= 0.1){
        dia = 1;
      }


      if(estadoBARCO == 0){
        rotacaoBARCO = rotacaoBARCO + 0.45;
      }

      if(estadoBARCO == 1){
        rotacaoBARCO = rotacaoBARCO - 0.45;
      }

      if(rotacaoBARCO >= 55){
        estadoBARCO = 1;
      }

      if(rotacaoBARCO < -55){
        estadoBARCO = 0;
      }


      if(estadoELEV == 0){
        movELEV = movELEV + 0.06;
      }

      if(estadoELEV == 1){
        movELEV = movELEV - 0.06;
      }

      if(movELEV >= 3.5){
        estadoELEV = 1;
      }

      if(movELEV < 0){
        estadoELEV = 0;
      }

      //***
      //MOVIMENTAÇÃO PLANETAS 1 E 2
      //***

      if(estadoPL1 == 0){
        movPlanet1 = movPlanet1 + 0.009;
      }

      if(estadoPL1 == 1){
        movPlanet1 = movPlanet1 - 0.009;
      }

      if(movPlanet1 >= 0.3){
        estadoPL1 = 1;
      }

      if(movPlanet1 < -0.3){
        estadoPL1 = 0;
      }

      //***
      //MOVIMENTAÇÃO PLANETAS 3 E 4
      //***

      if(estadoPL2 == 0){
        movPlanet2 = movPlanet2 + 0.003;
      }

      if(estadoPL2 == 1){
        movPlanet2 = movPlanet2 - 0.003;
      }

      if(movPlanet2 >= 0.3){
        estadoPL2 = 1;
      }

      if(movPlanet2 < -0.3){
        estadoPL2 = 0;
      }

    }

    if((telaINICIO == 1) && (telaCREDITOS == 0) && (telaJOGO == 0)){
      desenhaTELAinicial();
      MenuTheme.setLoop(true);
      MenuTheme.setVolume(100);
    }

    if(telaCREDITOS == 1){
      desenhaTELAcreditos();
    }


    redimensiona(glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
    glutSwapBuffers();

    corAux = corAux + 0.0030;

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

    if(((x > coodX(420)) && (x < coodX(685))) && ((y > coodY(535)) && (y < coodY(685)))){
      if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
        MenuSelect_sound.setVolume(100);
        MenuSelect_sound.play();
        telaINICIO = 0;
        telaCREDITOS = 1;
      }
    }

    if(((x > coodX(420)) && (x < coodX(685))) && ((y > coodY(615)) && (y < coodY(665)))){
      if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
        MenuSelect_sound.setVolume(100);
        MenuSelect_sound.play();
        exit(0);
      }
    }
  }

  if(telaCREDITOS == 1){
    if(((x > coodX(18)) && (x < coodX(400))) && ((y > coodY(655)) && (y < coodY(695)))){
      if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
        MenuSelect_sound.setVolume(100);
        MenuSelect_sound.play();
        Awaken.stop();
        park_music.stop();
        MenuTheme.play();
        corAux = 0;
        telaCREDITOS = 0;
        telaINICIO = 1;
      }
    }

    if(((x > coodX(70)) && (x < coodX(950))) && ((y > coodY(190)) && (y < coodY(595)))){
      if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        MenuSelect_sound.setVolume(100);
        MenuSelect_sound.play();
        MenuTheme.stop();
        Awaken.play();
      }
    }

    if(((x > coodX(375)) && (x < coodX(895))) && ((y > coodY(20)) && (y < coodY(150)))){
      if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        Twice.play();
      }
    }
  }

}

int main(int argc, char *argv[]) {

    srand(time(0));

    if(!park_music.openFromFile("music/mashup.ogg"))
      printf("\n ERRO AO CARREGAR mashup.ogg");

    if(!MenuTheme.openFromFile("music/SmashBrosBrawl.ogg"))
      printf("\n ERRO AO CARREGAR SmashBrosBrawl.ogg");

    if(!MenuSelect_sound.openFromFile("music/MenuSelectSOUND.ogg"))
      printf("\n ERRO AO CARREGAR MenuSelect.ogg");

    if(!Awaken.openFromFile("music/Awaken.ogg"))
      printf("\n ERRO AO CARREGAR Awaken.ogg");

    if(!Twice.openFromFile("music/Twice.ogg"))
      printf("\n ERRO AO CARREGAR Twice.ogg");

    glutInit(&argc, argv);
    glutInitContextVersion(1, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1024, 720);
    glutInitWindowPosition (0, 0);

    glutCreateWindow("twiceLAND - this is REQUIEM");

    if(telaINICIO == 1){
      MenuTheme.setLoop(true);
      MenuTheme.setVolume(100);
      MenuTheme.play();
    }


    //MouseFunc utilizada para clique do mouse nos menus/telas
    glutMouseFunc(cliqueMOUSE);
    //glutEnterGameMode();                 // fullscreen baby! (retire o comentário para ativar a tela cheia)

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
