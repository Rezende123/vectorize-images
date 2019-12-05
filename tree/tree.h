typedef struct node  
{ 
    int data;
    int index;
    struct node *quad1; 
    struct node *quad2;  
    struct node *quad3;  
    struct node *quad4; 
} tNode; 

tNode* createNode(int data, int index);
tNode* insertNode(tNode* node, int data);
tNode* search(tNode* root, int data);
tNode* parseArrayToTree(unsigned char arr[], tNode* root, int i, int n);
tNode* parseArrayToQuadTree(unsigned char arr[], tNode* root, int i, int n);
void printTree(tNode *root, int space);
void cannyEfect(tNode *root);
void edgeEfect(tNode *root);
void parseTreeToArray(tNode *node, unsigned char * arr);