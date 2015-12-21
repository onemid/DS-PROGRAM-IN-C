//
//  main.c
//  DS_HW3_AVLTree
//
//  Created by GONG, YI-JHONG on 2015/12/21.
//  Copyright © 2015年 GONG, YI-JHONG. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int key;
    struct node *left;
    struct node *right;
    int height;
}node;

int max (int a, int b);

int height (struct node *N){
    if (!N) {
        return 0;
    }
    return  N->height;
}

int max(int a, int b){
    return (a > b) ? a : b;
}

struct node* newNode(int key){
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

/* FUNCTION FOR RR LL RL LR*/

struct node *rightRotate(struct node *y){
    struct node *x = y->left;
    struct node *T2 = x->right;
    
    x->right = y;
    y->left = T2;
    
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    
    return x;
}

struct node *leftRotate(struct node *x){
    struct node *y = x->right;
    struct node *T2 = y->left;
    
    y->left = x;
    x->right = T2;
    
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    
    return y;
}

int getBalance(struct node *N){
    if (!N) {
        return 0;
    }
    return height(N->left) - height(N->right);
}

struct node* insert(struct node* node, int key){
    if (!node) return (newNode(key));
    if (key < node->key) {
        node->left = insert(node->left, key);
    }else{
        node->right = insert(node->right, key);
    }
    
    node->height = max(height(node->left), height(node->right)) + 1;
    
    int balance = getBalance(node);
    
    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    return node;
}

/* ORDER PRINTING */

void inOrder(struct node *root){
    if (root) {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

void postOrder(struct node *root){
    if (root) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->key);
    }
}

int main(int argc, const char * argv[]) {
    int tmp;
    struct node *root = NULL;
    
    while (1) {
        scanf("%d", &tmp);
        if (tmp == -1) {
            break;
        }
        root = insert(root, tmp);
    }
    
    printf("In-Order:");
    inOrder(root);
    printf("\nPost-Order:");
    postOrder(root);
    printf("\n");
    
    return 0;
}
