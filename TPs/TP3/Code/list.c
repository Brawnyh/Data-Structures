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


/*-----------------------------------------------------------------*/

List* list_create(void) {
	List* l = NULL;
	l=malloc(sizeof(struct s_List)*sizeof(LinkedElement));
	
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
	*l=NULL;
	free(l);
	
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
	return l->sentinel->value;
	//return 0;
}

/*-----------------------------------------------------------------*/

int list_back(const List* l) {
	(void)l;
	//linkedList tmp=l->sentinel
	//while(!tempty) tmp=tmp->next
	//return tmp->value
	return 0;
}

/*-----------------------------------------------------------------*/

List* list_pop_front(List* l) {
	assert (list_is_empty(l));
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
	LinkedElement *curr=malloc(sizeof(LinkedElement));
	curr=l->sentinel;
	while(p!=0){
		curr=curr->next;
	}
	//curr->value=NULL;
	curr->previous->next=curr->next;
	
	return l;
}

/*-----------------------------------------------------------------*/

int list_at(const List* l, int p) {
	(void)l;
	return p;
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

/*-----------------------------------------------------------------*/

List* list_sort(List* l, OrderFunctor f) {
	(void)f;
	return l;
}

