#ifndef LISTE_H
#define LISTE_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define TailleMax 16

typedef struct s_list list;

list *CreateListe(void);

bool empty(list *l);

list *push_back(list *l,int v);

list *pop_front(list *l);

list *pop_back(list *l);

int size(list *l);

int back (const list *l);

int front(const list *l);

list *insert_at(list *l,unsigned int i,int v);

list *remove_at(list *l,unsigned int i,int v);

int at(const list *l,unsigned int i);




#endif

