#include "rbtree.h"
#include "rbtree.c"
#include<stdio.h>

int main(int argc, char *argv[]) {
    rbtree *t = new_rbtree();

    rbtree_insert(t,10);
    rbtree_insert(t,5);
    rbtree_insert(t,8);
    rbtree_insert(t,34);
    rbtree_insert(t,67);
    rbtree_insert(t,23);
    rbtree_insert(t,156);
    rbtree_insert(t,24);
    rbtree_insert(t,2);
    rbtree_insert(t,12);

    printf("root\n");
    printf("key: %d \n", t->root->key);
    printf("color: %d \n", t->root->color);
    printf("parent: %d \n\n", t->root->parent->key);

    printf("root->left\n");
    printf("key: %d \n", t->root->left->key);
    printf("color: %d \n", t->root->left->color);
    printf("parent: %d \n\n", t->root->left->parent->key);

    printf("root->left->left\n");
    printf("key: %d \n", t->root->left->left->key);
    printf("color: %d \n", t->root->left->left->color);
    printf("parent: %d \n\n", t->root->left->left->parent->key);

    printf("root->left->left->left\n");
    printf("key: %d \n", t->root->left->left->left->key);
    printf("color: %d \n", t->root->left->left->left->color);
    printf("parent: %d \n\n", t->root->left->left->left->parent->key);
    
    printf("root->left->right\n");
    printf("key: %d \n", t->root->left->right->key);
    printf("color: %d \n", t->root->left->right->color);
    printf("parent: %d \n\n", t->root->left->right->parent->key);
        
    printf("root->left->right->right\n");
    printf("key: %d \n", t->root->left->right->right->key);
    printf("color: %d \n", t->root->left->right->right->color);
    printf("parent: %d \n\n", t->root->left->right->right->parent->key);

    printf("root->right\n");
    printf("key: %d \n", t->root->right->key);
    printf("color: %d \n", t->root->right->color);
    printf("parent: %d \n\n", t->root->right->parent->key);

    printf("root->right->left\n");
    printf("key: %d \n", t->root->right->left->key);
    printf("color: %d \n", t->root->right->left->color);
    printf("parent: %d \n\n", t->root->right->left->parent->key);

    printf("root->right->right\n");
    printf("key: %d \n", t->root->right->right->key);
    printf("color: %d \n", t->root->right->right->color);
    printf("parent: %d \n\n", t->root->right->right->parent->key);

    printf("root->right->right->right\n");
    printf("key: %d \n", t->root->right->right->right->key);
    printf("color: %d \n", t->root->right->right->right->color);
    printf("parent: %d \n\n", t->root->right->right->right->parent->key);

    printf("root->right->left->left\n");
    printf("key: %d \n", t->root->right->left->left->key);
    printf("color: %d \n", t->root->right->left->left->color);
    printf("parent: %d \n\n", t->root->right->left->left->parent->key);
    
    printf("root->right->left->right\n");
    printf("key: %d \n", t->root->right->left->right->key);
    printf("color: %d \n", t->root->right->left->right->color);
    printf("parent: %d \n\n", t->root->right->left->right->parent->key);

    // rbtree_insert(t,8);
    // rbtree_insert(t,7);
    // rbtree_insert(t,9);
    // rbtree_insert(t,3);
    // rbtree_insert(t,6);
    // rbtree_insert(t,4);
    // rbtree_insert(t,5);
    // rbtree_insert(t,12);
    // printf("%d ", t->root->key);
    // printf("%d \n", t->root->color);
    // printf("%d ", t->root->left->key);
    // printf("%d \n", t->root->left->color);
    // printf("%d ", t->root->left->left->key);
    // printf("%d \n", t->root->left->left->color);
    
    // printf("%d ", t->root->left->left->left->key);
    // printf("%d \n", t->root->left->left->left->color);

    // printf("%d ", t->root->left->left->right->key);
    // printf("%d \n", t->root->left->left->right->color);

    // printf("%d ", t->root->left->right->key);
    // printf("%d \n", t->root->left->right->color);


    // printf("%d ", t->root->right->key);
    // printf("%d \n", t->root->right->color);
    // printf("%d ", t->root->right->right->key);
    // printf("%d \n", t->root->right->right->color);
    // printf("%d", t->root->right->color);

    return 0;
}