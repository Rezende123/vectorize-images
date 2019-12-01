#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node  
{ 
    int data; 
    struct node *left; 
    struct node *right; 
} tNode; 

tNode* createNode(int data);
tNode* insertNode(tNode* node, int data);
tNode* search(tNode* root, int data);