#include "Liste.h"

int main(void){
    list *l = CreateListe();
    for (int i=0;i<5;i++){
        push_back(l,i);
        //printf("%d",front(l));
        printf("%d",back(l));
        
    }
    printf("\n");
    return 0;
}