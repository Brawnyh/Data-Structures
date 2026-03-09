#include "Liste.h"

typedef struct s_linkedList{
    struct s_linkedList *next;
    struct s_linkedList *prev;
    int value;
}LinkedList;

struct s_Liste{
    LinkedList *head;
    LinkedList *tail;
    int gauge;

};


liste *createListe(void){
    liste *l=malloc(sizeof(struct s_Liste));
    l->head=NULL;
    l->queue=NULL;
    l->gauge=0;
    return l;

}

liste *push_back(liste *l){
    LinkedList **e= l->gauge? &(l->tail->next):&(l->head)
}