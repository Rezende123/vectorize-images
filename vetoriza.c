#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include <GL/glut.h>

#include "Ponto.h"
#include "winGL.h"
#include "tree/tree.h"
		
unsigned char* 	image = NULL;	// image file
int 			iHeight, 
				iWidth,
				edgeLevel = 10,
				iChannels;

tNode * imageTree;

bool 			desenha = false;

/// ***********************************************************************
/// ** 
/// ***********************************************************************

void negativaImage(unsigned char* img, int w, int h) {

	unsigned char 	aux;
	int 			i,
					j;
	
	if (img == NULL)
		return;

	for (j = 0 ; j < h ; j++) 
		for (i = 0 ; i < w ; i++) {
			int index = j*w+i;

			img[index] = 255 - img[index];
		}
}

// ***********************************************
// ******                                   ******
// ***********************************************

void desenhaVetorizacao() {
	
	// rotina que deve ser implementada para visualizacao da arvore
	// utilize a rotina desenhaQuadrante(p0, p1, cor)
	// fornecendo os pontos inicial e final do quadrante e a sua cor
	// funcao do valor do pixel ou da regiao que voce quer desenhar
	 
    edgeEfect(imageTree);

}
	
/// ***********************************************************************
/// ** 
/// ***********************************************************************

void vetorizaImagem() {
	
	printf("CANNY EFECT\n");
 
    tNode* root = parseArrayToTree(image, root, 0, iWidth * iHeight); 
    cannyEfect(root);
	parseTreeToArray(root, image);	
}

void edgeImage() {
	
	printf("EDGE EFECT LEVEL %d\n", edgeLevel);
	
    imageTree = parseArrayToQuadTree(image, imageTree, 0, edgeLevel, iWidth * iHeight, 1,0,0);
	// parseTreeToArray(root, image);	
	desenha = true;
	edgeLevel++;
}
	
/// ***********************************************************************
/// ** 
/// ***********************************************************************

void teclado(unsigned char key, int x, int y) {

	switch (key) {
		case 27		: 	exit(0);
						break;				
		case 'v'	:
		case 'V'	: 	vetorizaImagem();
						break;	
		case 'e'	:
		case 'E'	:	edgeImage();
						break;
		case 'q'	:
		case 'Q'	: 	desenha = !desenha;
						break;	

		case 'r'	: 	
		case 'R'	: 	negativaImage(image, iHeight, iWidth);
						break;			
		}
	glutPostRedisplay();
}
		
/// ***********************************************************************
/// **
/// ***********************************************************************

void mouse(int button, int button_state, int x, int y ) {

	if 	(button_state == GLUT_DOWN ) {
		switch (button) {
			
			case GLUT_LEFT_BUTTON	: 	printf("botao esquerdo?\n");
										break;
	
			case GLUT_RIGHT_BUTTON	:	printf("botao direito?\n");
										break;
			}
		glutPostRedisplay();
		}
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

void desenho(void) {

    glClear (GL_COLOR_BUFFER_BIT); 
    
    glColor3f (1.0, 1.0, 1.0);
    
    if (desenha)
    	desenhaVetorizacao();
    else
    	glDrawPixels( iWidth, iHeight, GL_LUMINANCE, GL_UNSIGNED_BYTE, image );
   	
    glutSwapBuffers ();
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

int main(int argc, char** argv) {
	
	char* filename = "images/Twitter.png";

    if (argc > 1)
		filename = argv[1];

	image = leImagem(filename);
			
	criaJanela(argc, argv);

    initOpenGL();
    
    initEventos();
	
    return 0;   
}
