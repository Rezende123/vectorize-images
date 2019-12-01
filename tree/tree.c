#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"
#define LEVEL_DISTANCE 1 

tNode* createNode(int data, int index) 
{ 
  tNode* node = (tNode*) malloc(sizeof(tNode)); 
  
  node->data = data; 
  node->index = index; 
  
  node->left = NULL; 
  node->right = NULL; 
  return  node; 
}

tNode* insertNode(tNode* node, int data) 
{ 
    if (node == NULL) return createNode(data, 0); 
  
    if (data < node->data) 
        node->left  = insertNode(node->left, data); 
    else if (data > node->data) 
        node->right = insertNode(node->right, data);    
  
    return node; 
}

tNode* search(tNode* root, int data) 
{
    if (root == NULL || root->data == data) 
       return root; 

    if (root->data < data) 
       return search(root->right, data); 

    return search(root->left, data); 
}

tNode* parseArrayToTree(unsigned char arr[], tNode* root, int i, int n) 
{ 
    if (i < n) 
    { 
        tNode* temp = createNode(arr[i], i); 
        root = temp;

        root->left = parseArrayToTree(arr, root->left, 2 * i + 1, n); 
        root->right = parseArrayToTree(arr, root->right, 2 * i + 2, n); 
    } 
    return root; 
}

void cannyEfect(tNode *root) {
    if (root == NULL) 
        return; 

    if (
        ((
            (root->right != NULL && root->right->data == 255) && 
            (root->left != NULL && root->left->data == 0)
        ) ||
        (
            (root->right != NULL && root->right->data == 0) && 
            (root->left != NULL && root->left->data == 255)
        ))) {
        root->right->data = root->left->data = 125;
    }

    if (root->data == 255) {
        root->data = 0;
    }

    cannyEfect(root->left);

    cannyEfect(root->right);
}

void parseTreeToArray(tNode *node, unsigned char * arr)
{
     if(node == NULL)
          return;

     arr[node->index] = node->data;

     if(node->left != NULL)
          parseTreeToArray(node->left, arr);
     if(node->right != NULL)
          parseTreeToArray(node->right, arr);
}

void printTree(tNode *root, int space) 
{ 
    if (root == NULL) 
        return; 
        
    space += LEVEL_DISTANCE; 
    
    printTree(root->right, space); 
    
    printf("\n"); 
    for (int i = LEVEL_DISTANCE; i < space; i++) 
        printf(" "); 
    printf("%d\n", root->data); 
    
    printTree(root->left, space); 
} 
