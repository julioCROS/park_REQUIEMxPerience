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

//INSTALAÇÃO BIBLIOTECA "SFML AUDIO"
//sudo apt-get install libsfml-dev


enum CAMERAS { ESTATICA = 1, PRIMEIRA_PESSOA, TERCEIRA_PESSOA, BRINQUEDO1, BRINQUEDO2, BRINQUEDO3, BRINQUEDO_1_2_3};
int modoCAM = ESTATICA;            //variável responsável por guardar o modo de câmera que está sendo utilizado

int xMouse = 0, yMouse = 0;     //variáveis globais que serão usadas na função posicionaCamera
float xCursor, yCursor, zCursor;  //guarda o centro do cursor
float phi = 90, teta = 0;       //ângulos das coordenadas esféricas
float rotacao = 0.1;

int volumeMUSIC = 100;

GLMmodel* worldMAP = NULL;
GLMmodel* roda = NULL;


// estrutura de dados que representará as coordenadas da câmera
struct {
  float x, y, z;
  float targetX, targetY, targetZ;
} camera;

void desenhaPARQUE(){
  if(!worldMAP){
  	worldMAP = glmReadOBJ("data/Concept3_Mapa.obj");
  	if (!worldMAP) exit(0);
  }
  glmDraw(worldMAP, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);

}

void desenhaRODA(){
  if(!roda){
  	roda = glmReadOBJ("data/al.obj");
  	if (!roda) exit(0);
  }
  glmDraw(roda, GLM_TEXTURE | GLM_SMOOTH | GLM_COLOR);

}


void teclado(unsigned char key, int x, int y) {
    switch (key) {
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
    glEnable(GL_DEPTH_TEST);                // Ativa o Z buffer
    glViewport (0, 0, w, h);                //define a proporção da janela de visualização
    glMatrixMode (GL_PROJECTION);           //define o tipo de matriz de transformação que será utilizada
    glLoadIdentity();                       //carrega a matriz identidade do tipo GL_PROJECTION configurado anteriormente
    gluPerspective(60.0, (float)w/(float)h, 0.2, 400.0);    //funciona como se fosse o glOrtho, mas para o espaço 3D
    glMatrixMode(GL_MODELVIEW);                             //ativa o modo de matriz de visualização para utilizar o LookAt
}

void inicializa(){

    park_music.setLoop(true);
    park_music.setVolume(volumeMUSIC);
    park_music.play();

    glClearColor(1, 1, 1, 1);                          //cor de fundo branca
    glEnable(GL_BLEND);                                //ativa a mesclagem de cores
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //ativando o blend, podemos criar objetos transparentes
    xCursor = 0.709259;                                       //a câmera começa olhando para o ponto 0
    yCursor = 8.896676;
    zCursor = -7.770996;

    // Lighting set up
  	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  	glEnable(GL_LIGHTING);
  	glEnable(GL_LIGHT0);

  	// Set lighting intensity and color
  	GLfloat qaAmbientLight[]	= {0.4, 0.3, 0.2, 1.0};
  	GLfloat qaDiffuseLight[]	= {0.2, 0.2, 0.2, 0.5};
  	GLfloat qaSpecularLight[]	= {0.1, 1.0, 1.0, 1.0};
  	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
  	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
  	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

  	// Set the light position
  	GLfloat qaLightPosition[]	= {0, 20, 0};
  	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);


}

//função que desenhará tudo o que aparece na tela
void desenhaCena() {

    // Set material properties
    GLfloat qaBlack[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat qaGreen[] = {0.0, 1.0, 0.0, 1.0};
    GLfloat qaWhite[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT, qaGreen);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, qaGreen);
    glMaterialfv(GL_FRONT, GL_SPECULAR, qaWhite);
    glMaterialf(GL_FRONT, GL_SHININESS, 60.0);

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
      desenhaPARQUE();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(3,12,0);
      glRotatef(rotacao,0,0,1);
      glTranslatef(0,0,0);
      desenhaRODA();
    glPopMatrix();

    rotacao = rotacao - 0.6;
    glDisable(GL_LIGHTING);

    glutSwapBuffers();
}



int main(int argc, char *argv[]) {

      if(!park_music.openFromFile("mashup.ogg"))
    printf("\n ERRO AO CARREGAR mashup.ogg");

    glutInit(&argc, argv);
    glutInitContextVersion(1, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition (0, 0);

    glutCreateWindow("twiceLAND -TP2 PARK (JIHYO)");
    //glutEnterGameMode();                 // fullscreen baby! (retire o comentário para ativar a tela cheia)
    glutSetCursor(GLUT_CURSOR_NONE);     // esconde o cursor do sistema


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
