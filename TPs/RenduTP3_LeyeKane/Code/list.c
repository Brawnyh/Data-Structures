/*-----------------------------------------------------------------*/
/*
 Licence Informatique - Structures de données
 Mathias Paulin (Mathias.Paulin@irit.fr)
 
 Implantation du TAD List vu en cours.
 */
/*-----------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"

typedef struct s_LinkedElement {
	int value;
	struct s_LinkedElement* previous;
	struct s_LinkedElement* next;
} LinkedElement;

/* Use of a sentinel for implementing the list :
 The sentinel is a LinkedElement* whose next pointer refer always to the head of the list and previous pointer to the tail of the list
 */
struct s_List {
	LinkedElement* sentinel;
	int size;
};

typedef struct {
    LinkedElement* tete;  
    LinkedElement* queue;  
} SubList;


/*-----------------------------------------------------------------*/

List* list_create(void) {
	List* l = NULL;
	l=malloc(sizeof(struct s_List)+sizeof(LinkedElement));
	
	l->sentinel=(LinkedElement*)(l+1);
	l->sentinel->previous=l->sentinel->next=l->sentinel;
	l->size=0;
	
	return l;
}

/*-----------------------------------------------------------------*/

List* list_push_back(List* l, int v) {
	(void)v;
	LinkedElement *e=malloc(sizeof(LinkedElement));
	e->value=v;
	e->next=l->sentinel;
	e->previous=e->next->previous;
	e->next->previous=e;
	e->previous->next=e;
	++(l->size);
	return l;
}

/*-----------------------------------------------------------------*/

void list_delete(ptrList* l) {
	LinkedElement *curr = (*l)->sentinel->next;
    while (curr != (*l)->sentinel) {
        LinkedElement *next = curr->next;
        free(curr);
        curr = next;
    }
    free(*l);
    *l = NULL;
	
}

/*-----------------------------------------------------------------*/

List* list_push_front(List* l, int v) {
	(void)v;
	LinkedElement *e=malloc(sizeof(LinkedElement));
	e->value=v;
	e->next=l->sentinel->next;
	e->previous=l->sentinel;
	e->next->previous=e;
	e->previous->next=e;
	++(l->size);
	return l;
}

/*-----------------------------------------------------------------*/

int list_front(const List* l) {
	(void)l;
	return l->sentinel->next->value;
	//return 0;
}

/*-----------------------------------------------------------------*/

int list_back(const List* l) {
	(void)l;
	return l->sentinel->previous->value;
}

/*-----------------------------------------------------------------*/

List* list_pop_front(List* l) {
	assert (!list_is_empty(l));
    LinkedElement *e=l->sentinel->next;
    e->next->previous=e->previous;
    e->previous->next=e->next;
    free(e);
    --(l->size);
	return l;
}

/*-----------------------------------------------------------------*/

List* list_pop_back(List* l){
	//LinkedElement *tmp=l->sentinel->previous;
	return l;
}

/*-----------------------------------------------------------------*/

List* list_insert_at(List* l, int p, int v) {
	(void)v;
	(void)p;
	LinkedElement *insert=l->sentinel->next;
	while(p--) insert=insert->next;
	LinkedElement *e=malloc(sizeof(LinkedElement));
	e->value=v;
	e->next=insert; 
    e->previous=insert->previous;
    e->next->previous=e;
    e->previous->next=e;
    ++(l->size);

	return l;
}

/*-----------------------------------------------------------------*/

List* list_remove_at(List* l, int p) {
	(void)p;
	LinkedElement *curr = l->sentinel->next;
	while(p-- > 0) curr = curr->next;
	curr->previous->next = curr->next;
	curr->next->previous = curr->previous;
	free(curr);
	--(l->size);
	return l;
}

/*-----------------------------------------------------------------*/

int list_at(const List* l, int p) {
	(void)l;
	LinkedElement *curr = l->sentinel->next;
	while(p-- > 0) curr = curr->next;
	return curr->value;
	
}

/*-----------------------------------------------------------------*/

bool list_is_empty(const List* l) {
	(void)l;
	return (l->size==0);
}

/*-----------------------------------------------------------------*/

int list_size(const List* l) {
	(void)l;
	return l->size;
}

/*-----------------------------------------------------------------*/

List* list_map(List* l, ListFunctor f, void* environment) {
	(void)f;
	(void)environment;
	for (LinkedElement *e=l->sentinel->next;e!=l->sentinel;e=e->next){
		e->value=f(e->value,environment);
	}
	return l;
}


/*--------------------------------------------------------------------*/

SubList list_split(SubList l) {
    LinkedElement* l1 = l.tete;
    LinkedElement* l2 = l.tete;

    while (l2 != l.queue && l2->next != l.queue) {
        l1 = l1->next;
        l2 = l2->next->next;
    }

    SubList milieu;
    milieu.queue = l1;
    milieu.tete = l1->next;
    l1->next->previous = NULL;
    l1->next = NULL;
    return milieu;
}
 

SubList list_merge(SubList gauche, SubList droite, OrderFunctor f) {
    SubList resultat;
    LinkedElement* courant;

    if (f(gauche.tete->value, droite.tete->value)) {
        resultat.tete = gauche.tete;
        courant = gauche.tete;
        gauche.tete = gauche.tete->next;
    } else {
        resultat.tete = droite.tete;
        courant = droite.tete;
        droite.tete = droite.tete->next;
    }

    while (gauche.tete != NULL && droite.tete != NULL) {
        if (f(gauche.tete->value, droite.tete->value)) {
            courant->next = gauche.tete;
            gauche.tete->previous = courant;
            courant = gauche.tete;
            gauche.tete = gauche.tete->next;
        } else {
            courant->next = droite.tete;
            droite.tete->previous = courant;
            courant = droite.tete;
            droite.tete = droite.tete->next;
        }
    }

    if (gauche.tete != NULL) {
        courant->next = gauche.tete;
        gauche.tete->previous = courant;
        resultat.queue = gauche.queue;
    } else {
        courant->next = droite.tete;
        droite.tete->previous = courant;
        resultat.queue = droite.queue;
    }

    return resultat;
}


SubList list_mergesort(SubList l, OrderFunctor f) {
    if (l.tete == NULL || l.tete == l.queue)
        return l;

    SubList milieu = list_split(l);
    SubList gauche = { l.tete, milieu.queue };
    SubList droite = { milieu.tete, l.queue };
    gauche = list_mergesort(gauche, f);
    droite = list_mergesort(droite, f);
    return list_merge(gauche, droite, f);
}


/*-----------------------------------------------------------------*/

List* list_sort(List* l, OrderFunctor f) {
	(void)f;
	SubList sl;
    sl.tete = l->sentinel->next;
    sl.queue = l->sentinel->previous;

    sl.tete->previous = NULL;
    sl.queue->next = NULL;

    sl = list_mergesort(sl, f);

    l->sentinel->next = sl.tete;
    sl.tete->previous = l->sentinel;
    l->sentinel->previous = sl.queue;
    sl.queue->next = l->sentinel;
	return l;
}

