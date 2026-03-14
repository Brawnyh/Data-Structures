#ifndef LISTE_H
#define LISTE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct s_Liste liste;
typedef int (*listeMapFunctor)(int);
liste *map(liste *l,listeMapFunctor f);

liste * createListe(void);

bool empty(liste *l);

liste *push_back(liste *l,int value);

liste *pop_front(liste *l);

liste *push_front(liste *l,int value);

liste *remove_at(liste *l,int pos)

void empty(const liste *l);











#endif