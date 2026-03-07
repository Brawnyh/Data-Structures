#include "Liste.h"

//on fera que la representation dynamique
//on aura une jauge et un chainage double



struct s_LinkedList{
    int value;
    struct s_LinkedList *prev;
    struct s_LinkedList *next;
}Linkedlist;


struct s_list{
    struct s_liste * head;
    struct s_liste * tail;
    unsigned int gauge; //numero de elementoss

};

list *CreateListe(void){
    list *l =malloc(sizeof(struct s_list));
    l->head=NULL;
    l->tail=NULL;
    l->gauge=0;
    return l;

}

bool empty(list *l){
    return (l->gauge==0);
}

list push ;



int size(list *l){
    return (l->gauge);
}
