#include "Liste.h"

int main(void){
    liste *l=createListe();
    for (int i=0;i<5;i++){
        push_back(l,i);
        //printf("%d",front(l));
        printf("%d",back(l));
        
    }
   return 0;
    

}