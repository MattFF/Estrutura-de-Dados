#include <stdio.h>
#include <stdlib.h>

/*
1 - Todo nó da arvore ou é vermelho ou é preto.
2 - A raiz é preta.
3 - Toda folha (NULL) é preta.
4 - Se um nó é vermelho, então ambos os filhos são pretos.
5 - Para todo nó, todos os caminhos do nó até as folhas
    contêm o mesmo número de nós pretos. 
*/

typedef enum color {
    RED, BLACK
} Color;

typedef struct node {
    int data;
    Color color;
    struct node *left;
    struct node *right;
    struct node *parent;
} Node;

void rse(Node **root, Node *curr) {
    Node *temp = curr;
    curr = curr->right;
    temp->right = curr->left;
    curr->left = temp;
    if(temp->parent == NULL)
        *root = curr;
    else if(temp->parent->right == temp)
        temp->parent->right = curr;
    else
        temp->parent->left = curr;
    //Alteração do pai
    curr->parent = temp->parent;
    temp->parent = curr;
    if(temp->right != NULL) 
        temp->right->parent = temp;
}

void rsd(Node **root, Node *curr) {
    Node *temp = curr;
    curr = curr->left;
    temp->left = curr->right;
    curr->right = temp;
    if(temp->parent == NULL) 
        *root = curr;
    else if(temp->parent->right == temp)
        temp->parent->right = curr;
    else
        temp->parent->left = curr;
    //Alteração do pai
    curr->parent = temp->parent;
    temp->parent = curr;
    if(temp->left != NULL) 
        temp->left->parent = temp;
}

Node* maxElement(Node **root) {
    if(*root == NULL) return NULL;
    Node *temp = *root;
    while(temp->right != NULL) 
        temp = temp->right;
    return temp;
}

int haveChildrenRed(Node **root) {
    if(*root == NULL) {
        printf("WTF ??\n");
        exit(0);
    }
    if((*root)->left == NULL && (*root)->right == NULL) return 0;
    if((*root)->right == NULL) {
        if((*root)->left->color == RED) return 1;
        else return 0;
    }
    if((*root)->right->color == RED) return 1;
    else return 0;
}

int haveChildrenBlack(Node **root) {
    if(*root == NULL) {
        printf("WTF ??\n");
        exit(0);
    }
    if((*root)->left == NULL && (*root)->right == NULL) return 1;
    if((*root)->left->color == BLACK && (*root)->right->color == BLACK) return 1;
    return 0;
}

int childrenRightBlack(Node **root){
    if(*root == NULL) {
        printf("WTF ??\n");
        exit(0);
    }
    if((*root)->right == NULL) return 1;
    if((*root)->right->color == BLACK) return 1;
    return 0; 
}

int childrenLeftBlack(Node **root){
    if(*root == NULL) {
        printf("WTF ??\n");
        exit(0);
    }
    if((*root)->left == NULL) return 1;
    if((*root)->left->color == BLACK) return 1;
    return 0; 
}

void deleteFix(Node **root, Node **curr) {
    if((*curr)->color == RED) return;

    if(haveChildrenRed(curr)) { // FUNCIONA
        if((*curr)->left != NULL) 
            (*curr)->left->color = BLACK;
        else (*curr)->right->color = BLACK;
    } else {
        Node *parent = (*curr)->parent;
        while(parent != NULL) {
            if(parent->left == (*curr)) {
                if(parent->right != NULL && parent->right->color == RED) {
                    rse(&(*root), parent);
                    parent->color = RED;
                    parent->parent->color = BLACK;
                } 
                if(haveChildrenBlack(&parent->right)){
                    parent->right->color = RED;
                    if(parent->color == RED) {
                        parent->color = BLACK;
                        return;
                    } else { 
                        (*curr) = parent;
                        parent = (*curr)->parent;
                    }
                } else {
                    if(childrenRightBlack(&parent->right)) {
                        rsd(&(*root), parent->right);
                        parent->right->color = BLACK;
                        parent->right->right->color = RED;
                    }
                    rse(&(*root), parent);
                    parent->parent->color = parent->color;
                    parent->color = BLACK;
                    parent->parent->right->color = BLACK;
                    return;
                }
            } else {
                if(parent->left != NULL && parent->left->color == RED) {
                    rsd(&(*root), parent);
                    parent->color = RED;
                    parent->parent->color = BLACK;
                } else if(haveChildrenBlack(&parent->left)){
                    parent->left->color = RED;
                    if(parent->color == RED) {
                        parent->color = BLACK;
                        return;
                    } else {
                        (*curr) = parent;
                        parent = (*curr)->parent;
                    }
                } else {
                    if(childrenLeftBlack(&parent->left)) {
                        rse(&(*root), parent->left);
                        parent->left->color = BLACK;
                        parent->left->left->color = RED;
                    }
                    rsd(&(*root), parent);
                    parent->parent->color = parent->color;
                    parent->color = BLACK;
                    parent->parent->left->color = BLACK;
                    return;
                }
            }
        }
    }
}

void delete(Node **root, Node **curr, int data){
    if(data == (*curr)->data) {
        Node *temp;
        if((*curr)->left == NULL) {
            deleteFix(root, curr);
            temp = (*curr);
            *curr = (*curr)->right;
            if(*curr != NULL)
                (*curr)->parent = temp->parent;
            free(temp);
        }
        else if((*curr)->right == NULL) {
            deleteFix(root, curr);
            temp = (*curr);
            *curr = (*curr)->left;
            if(*curr != NULL)
                (*curr)->parent = temp->parent;
        } else {
            temp = maxElement(&(*curr)->left);
            (*curr)->data = temp->data;
            delete(root, &(*curr)->left, temp->data);
        }
    } else if (data > (*curr)->data)
        delete(root, &(*curr)->right, data);
    else
        delete(root, &(*curr)->left, data); 
}

void insertFix(Node **root, Node **curr) {
    Node *parent = NULL;
    Node *grandParent = NULL;
    while(*curr != *root && (*curr)->parent->color == RED) {
        parent = (*curr)->parent;
        grandParent = (*curr)->parent->parent;
        if(parent == grandParent->left) {
            //Caso 1
            if(grandParent->right != NULL && grandParent->right->color == RED) {
                parent->color = BLACK;
                grandParent->right->color = BLACK;
                grandParent->color = RED;
                *curr = grandParent;
            } else if(*curr == parent->right) { //Caso 2
                rse(root, parent);
                *curr = parent;
                parent = (*curr)->parent;
            }
            if((*curr)->parent != NULL) { //Caso 3
                (*curr)->parent->color = BLACK;
                if((*curr)->parent->parent != NULL) {
                    (*curr)->parent->parent->color = RED;
                    rsd(root, (*curr)->parent->parent);
                }
            }
        } else {
            //Caso 1
            if(grandParent->left != NULL && grandParent->left->color == RED) {
                parent->color = BLACK;
                grandParent->left->color = BLACK;
                grandParent->color = RED;
                *curr = grandParent;
            } else if(*curr == parent->left) { //Caso 2
                *curr = parent;
                parent = (*curr)->parent;
                rsd(root, *curr);
            }
            if((*curr)->parent != NULL) { //Caso 3
                (*curr)->parent->color = BLACK;
                if((*curr)->parent->parent != NULL) {
                    (*curr)->parent->parent->color = RED;
                    rse(root, (*curr)->parent->parent);
                }
            }
        }
    }
}

Node* getNode(int data) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;
    newNode->color = RED;
    newNode->right = NULL;
    newNode->left = NULL;
    newNode->parent = NULL;
    return newNode;
}

void insert(Node **root, Node *newNode) {
    if(*root == NULL) 
        *root = newNode;
    else if(newNode->data > (*root)->data) {
        insert(&(*root)->right, newNode);
        (*root)->right->parent = *root;
    } else {
        insert(&(*root)->left, newNode);
        (*root)->left->parent = *root;
    }
}

void rbInsert(Node **root, int data) {
    Node *newNode = getNode(data);
    insert(root, newNode);
    insertFix(root, &newNode);
    (*root)->color = BLACK;    
}

void preOrder(Node **root) {
    if(*root == NULL) return;
    if((*root)->parent == NULL)
        printf("(Root: %d) Color: %s\n", (*root)->data, 
        (*root)->color == 0 ? "RED":"BLACK");
    else
        printf("(Node: %d - [%d]) Color: %s\n", (*root)->data, (*root)->parent->data, 
        (*root)->color == 0 ? "RED":"BLACK");
    preOrder(&(*root)->left);
    preOrder(&(*root)->right);
}

void posOrder(Node **root) {
    if(*root == NULL) return;
    preOrder(&(*root)->left);
    preOrder(&(*root)->right);
    if((*root)->parent == NULL)
        printf("(Root: %d) Color: %s\n", (*root)->data, 
        (*root)->color == 0 ? "RED":"BLACK");
    else
        printf("(Node: %d - [%d]) Color: %s\n", (*root)->data, (*root)->parent->data, 
        (*root)->color == 0 ? "RED":"BLACK");
}

void inOrder(Node **root) {
    if(root == NULL) return;
    preOrder(&(*root)->left);
    if((*root)->parent == NULL)
        printf("(Root: %d) Color: %s\n", (*root)->data, 
        (*root)->color == 0 ? "RED":"BLACK");
    else
        printf("(Node: %d - [%d]) Color: %s\n", (*root)->data, (*root)->parent->data, 
        (*root)->color == 0 ? "RED":"BLACK");
    preOrder(&(*root)->right);
}

int main () {

    Node *root = NULL;
    int i, arr[8] = {25, 30, 10, 20, 40, 60, 50, 70};
    for(i = 0; i < 8; ++i) rbInsert(&root, arr[i]);
    preOrder(&root);
    printf("\n");
    delete(&root, &root, 40);
    preOrder(&root);
    return 0;
}