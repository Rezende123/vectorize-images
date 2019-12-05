#include "../Ponto.h"

typedef struct node  
{ 
    int data;
    int index;
    tPonto *pointX;
    tPonto *pointY;
    struct node *quad1; 
    struct node *quad2;  
    struct node *quad3;  
    struct node *quad4; 
} tNode; 

tNode* createNode(int data, int index);
tPonto* createPoint(int x, int y);
tNode* insertNode(tNode* node, int data);
tNode* search(tNode* root, int data);
tNode* parseArrayToTree(unsigned char arr[], tNode* root, int i, int n);
tNode* parseArrayToQuadTree(unsigned char arr[], tNode* root, int level,
    int pointLevel, int iArea, int idQuad, int lastW, int lastH);
void printTree(tNode *root, int space);
void cannyEfect(tNode *root);
void edgeEfect(tNode *root);
void parseTreeToArray(tNode *node, unsigned char * arr);