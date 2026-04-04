#include "Queue.h"

int main(void){
    Queue*q=createQueue();

    for (int i=0;i<QueueSize;i++){
        queue_push(q,i);
        printf("%d",i);

    }

    return 0;
}