#include "binaryTree.h"

struct S_tree{
    binTree *parent;
    binTree *left;
    binTree *right;
    int val;

};


binTree *create(){
    return NULL;
}

boolean empty(binTree *t){
    return t==NULL;
}

binTree *cons(binTree left,binTree right,int val){
    binTree *t=malloc(sizeof(struct binTree));
    t->parent=NULL;
    if (t->left = left){
        t->left->parent=t;
    }
    if (t->right=right){
        t->right->parent=t;
    }
    t->val=value;
    return t;
}

int root(binTree *t){
    assert(!empty(t))
    return t->val;
    
}

binTree *parent(binTree *t){
    assert(!empty(t));
    return t->parent ;
    
}

binTree *left(binTree *t){
    assert(!empty(t));
    return t->left ;
    
}

binTree *right(binTree *t){
    assert(!empty(t));
    return t->right ;
    
}

binTree *add(binTree *t,int v){
    binTree *tmp=cons(create(),create(),v);

    if (val<t->left){
        t->left->parent=tmp->parent;
    }
}