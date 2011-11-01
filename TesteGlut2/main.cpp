
#define GLUT_DISABLE_ATEXIT_HACK
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <gl/glut.h>
#include <iostream>
using namespace std;

GLint view_w, view_h;

GLfloat light_diffuse[] = {1.0, 0.0, 0.0, 1.0};  // Red diffuse light.
GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};  // Infinite light location.
GLfloat n[6][3] = {  // Normals for the 6 faces of a cube.
  {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
  {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
GLint faces[6][4] = {  // Vertex indices for the 6 faces of a cube.
  {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
  {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };
GLfloat v[8][3];  // Will be filled in with X,Y,Z vertexes. 

void criaCubo(void)
{
     // definindo vértices do cubo
     v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;
     v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1;
     v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;
     v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
     v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;
     v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1;
}

void drawBox(void)
{
  int i;
  
  criaCubo();

  for (i = 0; i < 6; i++) {
    glBegin(GL_QUADS);
    glNormal3fv(&n[i][0]);
    glVertex3fv(&v[faces[i][0]][0]);
    glVertex3fv(&v[faces[i][1]][0]);
    glVertex3fv(&v[faces[i][2]][0]);
    glVertex3fv(&v[faces[i][3]][0]);
    glEnd();
  }
}

void drawSphere(void)
{
     glutSolidSphere(1.0, 20, 20);     
}

void SelecaoCor(int cor)
{         
}

void SelecaoMenu(int selecao)
{
     switch(selecao)
     {
                    case 2:
                         exit(0);
                         break;                    
     }     
}

void CriaMenu(void)
{
     int menu;
     glutCreateMenu(SelecaoMenu);
     glutAddMenuEntry("Selecione Cor",1);
     glutAddMenuEntry("Sair",2);
     glutAttachMenu(GLUT_RIGHT_BUTTON);
          
}

void display(void)
{
  // limpa tela
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  drawBox();
  glutSwapBuffers();
}

void init(void)
{
  // Habilitar luz
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
  

  // Use depth buffering for hidden surface elimination.
  glEnable(GL_DEPTH_TEST);

  // Setup the view of the cube.
  glMatrixMode(GL_PROJECTION);
  gluPerspective( 
    // field of view in degree
    60.0,
    // aspect ratio
    1.0,
    // Z near
    1.0, 
    // Z far
    30.0);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 5.0,  // eye is at (0,0,5)
    0.0, 0.0, 0.0,      // center is at (0,0,0)
    0.0, 1.0, 0.);      // up is in positive Y direction

  // Adjust cube position to be asthetic angle.
  glTranslatef(0.0, 0.0, -1.0);
  glRotatef(60, -1.0, 0.0, 0.0);
  //glRotatef(-20, 0.0, 0.0, 1.0);
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{ 
    // Especifica as dimensões da Viewport
    glViewport(0, 0, w, h);
    view_w = w;
    view_h = h;                   

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();    
}

void MotionMouse(int x, int y)
{
     // chamada quando o mouse é movido com o botão pressionado
     cout << "x = " << x << "; y = " << y << endl;
     glutPostRedisplay();     
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("Trabalho Final de Computação Gráfica");
  CriaMenu();
  glutDisplayFunc(display);
  //glutReshapeFunc(AlteraTamanhoJanela);
  glutMotionFunc(MotionMouse);
  init();
  glutMainLoop();
  return 0;             // ANSI C requires main to return int.
}
