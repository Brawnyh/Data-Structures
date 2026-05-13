#include <stdlib.h>
#include <assert.h>

#include "skiplist.h"
#include "rng.h"

typedef struct s_Link {
    struct s_Node* next;
    struct s_Node* prev;
} Link;

typedef struct s_Node {
    int value;
    int nblevels;
    Link links[];
} Node;

struct s_SkipList {
    Node* sentinel;
    int nblevels;
    int size;
    RNG rng;
};

struct s_SkipListIterator {
    SkipList* list;
    Node* current;
    IteratorDirection direction;
};

static Node* node_create(int value, int nblevels) {
    Node* n = malloc(sizeof(Node) + sizeof(Link) * nblevels);
    n->value = value;
    n->nblevels = nblevels;
    for (int i = 0; i < nblevels; i++)
        n->links[i].next = n->links[i].prev = NULL;
    return n;
}

SkipList* skiplist_create(int nblevels) {
    SkipList* d = malloc(sizeof(SkipList) + sizeof(Node) + sizeof(Link) * nblevels);
    d->nblevels = nblevels;
    d->size = 0;
    d->rng = rng_initialize(0, nblevels);
    d->sentinel = (Node*)(d + 1);
    d->sentinel->value = 0;
    d->sentinel->nblevels = nblevels;
    for (int i = 0; i < nblevels; i++)
        d->sentinel->links[i].next = d->sentinel->links[i].prev = d->sentinel;
    return d;
}

void skiplist_delete(SkipList** d) {
    Node* curr = (*d)->sentinel->links[0].next;
    while (curr != (*d)->sentinel) {
        Node* next = curr->links[0].next;
        free(curr);
        curr = next;
    }
    free(*d);
    *d = NULL;
}

unsigned int skiplist_size(const SkipList* d) {
    return d->size;
}

SkipList* skiplist_insert(SkipList* d, int value) {
    Node* update[d->nblevels];
    Node* curr = d->sentinel;

    for (int i = d->nblevels - 1; i >= 0; i--) {
        while (curr->links[i].next != d->sentinel && curr->links[i].next->value < value)
            curr = curr->links[i].next;
        update[i] = curr;
    }

    if (curr->links[0].next != d->sentinel && curr->links[0].next->value == value)
        return d;

    int lvl = rng_get_value(&d->rng) + 1;
    Node* n = node_create(value, d->nblevels);

    for (int i = 0; i < lvl; i++) {
        n->links[i].next = update[i]->links[i].next;
        n->links[i].prev = update[i];
        update[i]->links[i].next->links[i].prev = n;
        update[i]->links[i].next = n;
    }

    d->size++;
    return d;
}

SkipList* skiplist_remove(SkipList* d, int value) {
    Node* update[d->nblevels];
    Node* curr = d->sentinel;

    for (int i = d->nblevels - 1; i >= 0; i--) {
        while (curr->links[i].next != d->sentinel && curr->links[i].next->value < value)
            curr = curr->links[i].next;
        update[i] = curr;
    }

    curr = curr->links[0].next;
    if (curr == d->sentinel || curr->value != value)
        return d;

    for (int i = 0; i < d->nblevels; i++) {
        if (update[i]->links[i].next != curr) break;
        update[i]->links[i].next = curr->links[i].next;
        curr->links[i].next->links[i].prev = update[i];
    }

    free(curr);
    d->size--;
    return d;
}

bool skiplist_search(const SkipList* d, int value, unsigned int* nb_operations) {
    *nb_operations = 0;
    Node* curr = d->sentinel;

    for (int i = d->nblevels - 1; i >= 0; i--) {
        while (curr->links[i].next != d->sentinel && curr->links[i].next->value <= value) {
            curr = curr->links[i].next;
            (*nb_operations)++;
            if (curr->value == value)
                return true;
        }
    }
    return false;
}

int skiplist_at(const SkipList* d, unsigned int i) {
    assert(i < (unsigned int)d->size);
    Node* curr = d->sentinel->links[0].next;
    for (unsigned int k = 0; k < i; k++)
        curr = curr->links[0].next;
    return curr->value;
}

void skiplist_map(const SkipList* d, ScanOperator f, void* environment) {
    Node* curr = d->sentinel->links[0].next;
    while (curr != d->sentinel) {
        f(curr->value, environment);
        curr = curr->links[0].next;
    }
}

SkipListIterator* skiplist_iterator_create(SkipList* d, IteratorDirection w) {
    SkipListIterator* it = malloc(sizeof(SkipListIterator));
    it->list = d;
    it->direction = w;
    it->current = (w == FORWARD_ITERATOR)
        ? d->sentinel->links[0].next
        : d->sentinel->links[0].prev;
    return it;
}

void skiplist_iterator_delete(SkipListIterator** it) {
    free(*it);
    *it = NULL;
}

SkipListIterator* skiplist_iterator_begin(SkipListIterator* it) {
    if (it->direction == FORWARD_ITERATOR)
        it->current = it->list->sentinel->links[0].next;
    else
        it->current = it->list->sentinel->links[0].prev;
    return it;
}

bool skiplist_iterator_end(SkipListIterator* it) {
    return it->current == it->list->sentinel;
}

SkipListIterator* skiplist_iterator_next(SkipListIterator* it) {
    if (it->direction == FORWARD_ITERATOR)
        it->current = it->current->links[0].next;
    else
        it->current = it->current->links[0].prev;
    return it;
}

int skiplist_iterator_value(SkipListIterator* it) {
    return it->current->value;
}