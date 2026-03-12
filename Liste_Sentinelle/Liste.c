#include "Liste.h"


//conceptualmente es una lista doublement chainee con sentinel apuntando a prev y next
typedef struct s_linkedList{
    struct s_linkedList *next;
    struct s_linkedList *prev;
    int value;
}LinkedList;

struct s_Liste{
    LinkedList *sentinel;
    int gauge;

};


liste *createListe(void){
    //liste *l=malloc(sizeof(struct s_Liste));
    //l->sentinel=malloc(sizeof(LinkedList));//es mejor evitar hacer dos mallocs 
    //l->sentinel->prev=l->sentinel->next=l->sentinel;
    liste *l=malloc(sizeof(struct s_Liste)) * sizeof(struct s_linkedList) ;
    l->sentinel=(LinkedList*)(l+1);
    l->sentinel->prev=l->sentinel->next=l->sentinel;
    l->gauge=0;
    return l;

}

void empty(const liste *l){
    return l->gauge==0;
}


liste *push_back(liste *l,int v){
    LinkedList *e=malloc(sizeof(LinkedList));
    e->value=v;
    e->next=l->sentinel;
    e->prev=e->next->prev;
    e->next->prev=e;
    e->prev->next=e;
    ++(l->gauge);
    return l;

}

//no estael test de null pointer
liste *push_front(liste *l,int v){
    LinkedList *e=malloc(sizeof(LinkedList));
    e->value=v;
    e->next=l->sentinel->next;
    e->prev=l->sentinel;
    e->next->prev=e;
    e->prev->next=e;
    ++(l->gauge);
    return l;  
}


liste *pop_front(liste *l){
    assert(empty(l));
    LinkedList *e=l->sentinel->next;
    e->next->prev=e->prev;
    e->prev->next=e->next;
    free(e);
    --(l->gauge);
    return l;  
}

liste* insert_at(liste *l,int pos,int v){
    assert(0<=pos && pos<=l->gauge);
    LinkedList *insert =l->sentinel->next;
    while(p--) insert =insert->next;
    LinkedList *e=malloc(sizeof(LinkedList));
    e->value=v;
    e->next=insert; 
    e->prev=insert->prev;
    e->next->prev=e;
    e->prev->next=e;
    ++(l->gauge);
    return l;
}   


liste *remove_at(liste *l,int pos){
    assert(0<=pos && pos<l->gauge);
    LinkedList *remove=l->sentinel->next;
    while(pos--) remove=remove->next;
    remove->next->prev=remove->prev;
    remove->prev->next=remove->next;
    free(remove);
    --(l->gauge);
    return l;  
}

list *map(liste *l,listeMapFunctor f){
    for (LinkedList *e =l->sentinel->next; e!=l->sentinel; e=e->next){
        e->value=f(e->value);
    }
    return l;
}