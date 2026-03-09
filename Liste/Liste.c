#include "Liste.h"

//on fera que la representation dynamique
//on aura une jauge et un chainage double



typedef struct s_LinkedList{
    int value;
    struct s_LinkedList *prev;
    struct s_LinkedList *next;
} Linkedlist;


struct s_list{
    struct s_LinkedList * head;
    struct s_LinkedList * tail;
    int gauge; //numero de elementoss

};

list *CreateListe(void){
    list *l =malloc(sizeof(struct s_list));
    l->head=NULL;
    l->tail=NULL;
    l->gauge=0;
    return l;

}


list *push_back(list *l,int v){
    Linkedlist**e=l->gauge ? &(l->tail->next) : &(l->head);
    *e=malloc(sizeof(Linkedlist));
    (*e)->value=v;
    (*e)->next=NULL;
    (*e)->prev=l->tail;
    l->tail=*e;
    l->gauge+=1;
    return l;
    
}

list *push_front(list *l,int v){
    Linkedlist **e = l->gauge ? &(l->head->prev) : &(l->tail);
    *e=malloc(sizeof(Linkedlist));
    (*e)->value=v;
    (*e)->next=l->head;
    (*e)->prev=NULL;
    l->head=*e;
    return l;
    
}

list *pop_front(list *l){
    assert(!empty(l));
    Linkedlist *e=l->head;
    l->head=e->next;
    if (l->head){
        l->head->prev=NULL;
    }else{
        l->tail=l->head;//si solo hay un elemento
        
    }
    --(l->gauge);
    free(e);
    return l;
}

int front(const list *l){
    assert(!empty(l));
    return l->head->value;
}

int back(const list *l){
    assert(!empty(l));
    return l->tail->value;
}

int at(const list *l,int p){
    assert(!empty(l) && 0<=p && l->gauge);
    Linkedlist *e=l->head;
    while(p--){
        e=e->next;
    }
    return (e->value);
}


/*el problema de introducir insert_at es que contiene muchos casos particulares lo cual genera
muchos ifs else de ahi la notion de sentinelle.
*/

list *insert_at(list *l,int p,int v){
    assert((0<=p) && (p<=l->gauge));
    Linkedlist *insert = l->head;
    
    while (p--) insert = insert->next;
    Linkedlist *e =malloc(sizeof(Linkedlist));
    e->value=v; e->next=insert;
    e->prev=(insert ? insert->prev :l->tail);

    if (e->prev){
        e->prev->next=e;
        
    }else{
        l->head=e;
    }if(e->next){
        e->next->prev=e;
    }else{
        l->tail=e;
    }
    ++(l->gauge);
    return l;

}

list *remove_at(list *l,int p){
    assert((0<=p) && (p<l->gauge));
    Linkedlist *remove=l->head;
    while (p--) remove=remove->next;
    if (remove->prev){
        remove->prev->next=remove->next;
    }else{
        l->head=remove->next;
    }if(remove->next){
        remove->next->prev =remove->prev;
    }else{
        l->tail=remove->prev;
    }
    free(remove);
    --(l->gauge);
    return l;
}

bool empty(list *l){
    return (l->gauge==0);
}






int size(list *l){
    return (l->gauge);
}
