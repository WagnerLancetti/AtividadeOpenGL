// Este código está baseado nos exemplos disponíveis no livro 
// "OpenGL SuperBible", 2nd Edition, de Richard S. e Wright Jr.
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

GLfloat angle, fAspect;

void DesenhaEixos(void);
void Inicializa (void);
void EspecificaParametrosVisualizacao(GLboolean);
void AlteraTamanhoJanela(GLsizei, GLsizei);
void GerenciaMouse(int, int, int, int);
void UpdateProjection(GLboolean);

void DesenhaEixos(void)
{
	glBegin(GL_LINES);
		glColor3f(1,1,1);
		glColor3f(1,1,1);
		glColor3f(1,1,1);
		glVertex3f(1,1,1);
		glVertex3f(10.0f, 0.0f, 0.0f);
		glVertex3f(1,1,0);
		glVertex3f(0.0f, 10.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 10.0f);
	glEnd();
}

void DrawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_LINE_LOOP);
    for (int ii = 0; ii < num_segments; ii++)   {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 
        float x = r * cosf(theta);//calculate the x component 
        float y = r * sinf(theta);//calculate the y component 
        glVertex2f(x + cx, y + cy);//output vertex 
    }
    glEnd();
}

void drawFilledSun(int x, int y){
    int i;
    double radius = 1;
    //glColor3ub(253, 184, 19);     
    glColor3ub(0, 0, 0);
    double twicePi = 2.0 * 3.142;
    glBegin(GL_TRIANGLE_FAN); //BEGIN CIRCLE
    glVertex2f(x, y); // center of circle
    for (i = 0; i <= 20; i++)   {
        glVertex2f (
            (x + (radius * cos(i * twicePi / 20))), (y + (radius * sin(i * twicePi / 20)))
            );
    }
    glEnd(); //END
}


            
// Função callback chamada para fazer o desenho
void Desenha(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    gluLookAt(0,0,20, 0,0,0, 0,1,0);
    
    // Monta o eixo Y (barra vertical preta)
    glColor3ub(0,0,0); // Define a cor preta até ser alterada
    glBegin(GL_QUADS);
        glVertex2f(0.0, 0.0);
        glVertex2f(0.1, 0.0);
        glVertex2f(0.1, 5.5);
        glVertex2f(0.0, 5.5);
    glEnd();
    // Monta o eixo X (barra horizontal preta)
    glBegin(GL_QUADS);
        glVertex2f(0.0, 0.0);
        glVertex2f(0.0, 0.1);
        glVertex2f(7.0, 0.1);
        glVertex2f(7.0, 0.0);
    glEnd();
    // Monta o primeiro retangulo preto
    glBegin(GL_QUADS);
        glVertex2f(4.5, 2.0);
        glVertex2f(5.5, 2.0);
        glVertex2f(5.5, 5.0);
        glVertex2f(4.5, 5.0);
    glEnd();
    // Monta o segundo retangulo amarelo
    glColor3ub(255,255,0); // Muda a cor para amarelo
    glBegin(GL_QUADS);
        glVertex2f(3.5, 5.0);
        glVertex2f(6.5, 5.0);
        glVertex2f(6.5, 6.0);
        glVertex2f(3.5, 6.0);
    glEnd();
    // Monta o primeiro triângulo (à esquerda)
    glColor3ub(255,0,0); // Muda a cor para vermelho
    glBegin(GL_TRIANGLES);
        glVertex2f(3.5, 6.0);
        glVertex2f(4.5, 6.0);
        glVertex2f(4.0, 7.0);
    glEnd();
    // Monta o segundo triângulo (à direita)
    glColor3ub(0,0,255); // Muda a cor para azul
    glBegin(GL_TRIANGLES);
        glVertex2f(5.5, 6.0);
        glVertex2f(6.5, 6.0);
        glVertex2f(6.0, 7.0);
    glEnd();
    
    
	glutSwapBuffers();
}

// Inicializa parâmetros de rendering
void Inicializa (void)
{ 
	GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0}; 
	GLfloat luzDifusa[4]={0.8,0.7,0.7,1.0};		 // "cor" 
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho" 
	GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};

	// Capacidade de brilho do material
	//GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 
	GLint especMaterial = 60;

 	// Especifica a cor
 	glClearColor(1,1,1,0);
    //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);

	// Define a refletância do material 
	//glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);  
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

    angle=45;
	EspecificaParametrosVisualizacao(false);
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(GLboolean toogle)
{
	UpdateProjection(toogle);
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

	// Especifica o tamanho da viewport
    glViewport(0, 0, w, h);
 
	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao(false);
}

// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	GLboolean toogle = false;
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-in
			toogle = !toogle;
		}
	EspecificaParametrosVisualizacao(toogle);
	glutPostRedisplay();
}

void UpdateProjection(GLboolean toggle)
{
  static GLboolean s_usePerspective = GL_TRUE;

  // toggle the control variable if appropriate
  if (toggle)
    s_usePerspective = !s_usePerspective;

  // select the projection matrix and clear it out
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // choose the appropriate projection based on the currently toggled mode
  if (s_usePerspective)
  {
    // set the perspective with the appropriate aspect ratio
    gluPerspective(angle,fAspect,5,500);
  }
  else
  {
    // set up an orthographic projection with the same near clip plane
    glOrtho(-100*fAspect, 100*fAspect, -100, 100, 5, 500);
  }

  // select modelview matrix and clear it out
  glMatrixMode(GL_MODELVIEW);
} // end UpdateProjection


void GerenciaTecladoEsc(unsigned char key, int x, int y){
      if (key == 27){// Termina o programa quando a tecla ESC for pressionada
            exit(0);
      }
}



// Programa Principal
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800,600);
	glutCreateWindow("Atividade Avaliativa");
	glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
	glutMouseFunc(GerenciaMouse);
	glutKeyboardFunc(GerenciaTecladoEsc); // Sair com a tecla ESC
	Inicializa();
	glColor3f(1.0, 1.0, 1.0);
	glutMainLoop();
}
