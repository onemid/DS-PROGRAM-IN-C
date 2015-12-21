//
//  main.c
//  DS_HW1_ BST_TRAVERSAL
//
//  Created by GONG, YI-JHONG on 2015/11/26.
//  Copyright © 2015年 GONG, YI-JHONG. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct tree *treePtr;
typedef struct tree{
    char data;
    treePtr left;
    treePtr right;
}tree;

void addNode (treePtr root, char data){
    if (!root) {
        root = malloc(sizeof(root));
        if (root) {
            root->data = data;
            root->left = NULL;
            root->right = NULL;
        }
    }else{
        if (data < root->data) {
            addNode(root->left, data);
        }else{
            addNode(root->right, data);
        }
    }
}

void postfix (treePtr node){
    if (node) {
        postfix(node->left);
        postfix(node->right);
        printf("%c", node->data);
    }
}

int main(int argc, const char * argv[]) {
    treePtr root;
    char data_in;
    root = NULL;
    while (1) {
        data_in = getchar();
        if (data_in == ' ') {
            break;
        }
        addNode(root, data_in);
    }
    postfix(root);
    return 0;
}
