#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "tree.h"
#include "../winGL.h"
#define LEVEL_DISTANCE 1 

tNode* createNode(int data, int index) 
{ 
  tNode* node = (tNode*) malloc(sizeof(tNode)); 
  
  node->data = data; 
  node->index = index; 
  
  node->quad1 = NULL; 
  node->quad2 = NULL; 
  node->quad3 = NULL; 
  node->quad4 = NULL; 
  return  node; 
}

tPonto * createPoint(int x, int y) {
    tPonto * point = malloc(sizeof (tPonto));
    
    point->x = x;
    point->y = y;

    return point;
}

tNode* insertNode(tNode* node, int data) 
{ 
    if (node == NULL) return createNode(data, 0); 
  
    if (data < node->data) 
        node->quad1  = insertNode(node->quad1, data); 
    else if (data > node->data) 
        node->quad2 = insertNode(node->quad2, data);    
  
    return node; 
}

tNode* search(tNode* root, int data) 
{
    if (root == NULL || root->data == data) 
       return root; 

    if (root->data < data) 
       return search(root->quad2, data); 

    return search(root->quad1, data); 
}

tNode* parseArrayToTree(unsigned char arr[], tNode* root, int i, int n) 
{ 
    if (i < n) 
    { 
        tNode* temp = createNode(arr[i], i); 
        root = temp;

        root->quad1 = parseArrayToTree(arr, root->quad1, 2 * i + 1, n); 
        root->quad2 = parseArrayToTree(arr, root->quad2, 2 * i + 2, n); 
    } 
    return root; 
}

int getWidthByIdQuad(int idQuad, int side, int lastW) {
    int width = (idQuad%2 == 0) ? side : 0;
    return width + lastW;
}
int getHeightByIdQuad(int idQuad, int side, int lastH) {
    int height = (idQuad > 2) ? side : 0;
    return height + lastH;
}

tNode* parseArrayToQuadTree(unsigned char arr[], tNode* root, int level, 
    int pointLevel, int iArea, int idQuad, int lastW, int lastH) 
{ 
    int amountQuads = pow(2, level);
    int side = sqrt(iArea);
    int iAreaQuad = iArea / amountQuads;
    int allColors = 0;

    int width = getWidthByIdQuad(idQuad, side, lastW);
    int height = getHeightByIdQuad(idQuad, side, lastH);
    int pX = width + side, pY = height + side;
    
    for (int i = width; i < pX; i++)
    {        
        for (int j = height; j < pY; j++)
        {
            allColors += arr[i*side+j];
        }
    }
    
    if (level < pointLevel && side > 4) 
    { 
        root = createNode((allColors/iAreaQuad), 0);
        root->pointX = createPoint(pX, pY);
        root->pointY = createPoint(width, height);

        int iNextArea = pow(( side/2 ), 2);
        
        root->quad1 = parseArrayToQuadTree(arr, root->quad1, level + 1, 
            pointLevel, iNextArea, 1, 0, 0); 
        root->quad2 = parseArrayToQuadTree(arr, root->quad2, level + 1, 
            pointLevel, iNextArea, 2, pX, 0); 
        root->quad3 = parseArrayToQuadTree(arr, root->quad3, level + 1, 
            pointLevel, iNextArea, 3, 0, pY); 
        root->quad4 = parseArrayToQuadTree(arr, root->quad4, level + 1, 
            pointLevel, iNextArea, 4, pX, pY); 
    } 
    return root;
}

void cannyEfect(tNode *root) {
    if (root == NULL) 
        return; 

    if (
        ((
            (root->quad2 != NULL && root->quad2->data == 255) && 
            (root->quad1 != NULL && root->quad1->data == 0)
        ) ||
        (
            (root->quad2 != NULL && root->quad2->data == 0) && 
            (root->quad1 != NULL && root->quad1->data == 255)
        ))) {
        root->quad2->data = root->quad1->data = 125;
    }

    if (root->data == 255) {
        root->data = 0;
    }

    cannyEfect(root->quad1);

    cannyEfect(root->quad2);
}

void edgeEfect(tNode *root) {
    if (root == NULL) 
        return;

    if (root->quad1 == NULL && root->quad2 == NULL &&
        root->quad3 == NULL && root->quad4 == NULL) {
        // printf("ROOT %d\n", root->data);
        desenhaQuadrante(*root->pointX, *root->pointY, root->data);
    } else {
        edgeEfect(root->quad1);

        edgeEfect(root->quad2);

        edgeEfect(root->quad3);

        edgeEfect(root->quad4);
    }

}

void parseTreeToArray(tNode *node, unsigned char * arr)
{
     if(node == NULL)
          return;

     arr[node->index] = node->data;

     if(node->quad1 != NULL)
          parseTreeToArray(node->quad1, arr);
     if(node->quad2 != NULL)
          parseTreeToArray(node->quad2, arr);
     if(node->quad3 != NULL)
          parseTreeToArray(node->quad3, arr);
     if(node->quad4 != NULL)
          parseTreeToArray(node->quad4, arr);
}

void printTree(tNode *root, int space) 
{ 
    if (root == NULL) 
        return; 
        
    space += LEVEL_DISTANCE; 
    
    printTree(root->quad2, space); 
    
    printf("\n"); 
    for (int i = LEVEL_DISTANCE; i < space; i++) 
        printf(" "); 
    printf("%d\n", root->data); 
    
    printTree(root->quad1, space); 
} 
