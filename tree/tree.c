#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"
#define LEVEL_DISTANCE 10 

tNode* createNode(int data) 
{ 
  // Allocate memory for new node  
  tNode* node = (tNode*) malloc(sizeof(tNode)); 
  
  // Assign data to this node 
  node->data = data; 
  
  // Initialize left and right children as NULL 
  node->left = NULL; 
  node->right = NULL; 
  return  node; 
}

tNode* insertNode(tNode* node, int data) 
{ 
    if (node == NULL) return createNode(data); 
  
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

tNode* insertLevelOrder(int arr[], tNode* root, int i, int n) 
{ 
    if (i < n) 
    { 
        tNode* temp = createNode(arr[i]); 
        root = temp;

        root->left = insertLevelOrder(arr, root->left, 2 * i + 1, n); 
        root->right = insertLevelOrder(arr, root->right, 2 * i + 2, n); 
    } 
    return root; 
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
