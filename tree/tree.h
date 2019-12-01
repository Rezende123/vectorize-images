typedef struct node  
{ 
    int data; 
    struct node *left; 
    struct node *right; 
} tNode; 

tNode* createNode(int data);
tNode* insertNode(tNode* node, int data);
tNode* search(tNode* root, int data);
tNode* insertLevelOrder(int arr[], tNode* root, int i, int n);
void inOrder(tNode* root);