#include "tree.h";

tNode* newNode(int data) 
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
    if (node == NULL) return newNode(data); 
  
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