#include <stdio.h>
#include <stdlib.h>

#include "QueueArray.h"

Queue_t *Queue_1 = NULL;
QueueStatus_t ret = QUEUE_NOK;
uint32 maxSize, noElemnts;

int Var1 = 502;
float Var2 = 502.55;
char Var3 = 'N';

void *returnVal = NULL;

int main(void)
{
    printf("Enter the queue max size: ");
    scanf("%u", &maxSize);

    /*create queue*/
    Queue_1 = CreateQueue(maxSize, &ret); printf("CreateQueue-> %i\n", ret);

    printf("======================\n");

    /*Adding diffrant type of data*/
    ret = EnqueueElement(Queue_1, &Var1); printf("Add(1)-> %i\n", ret);
    ret = EnqueueElement(Queue_1, &Var2); printf("Add(2)-> %i\n", ret);
    ret = EnqueueElement(Queue_1, &Var3); printf("Add(3)-> %i\n", ret);
    ret = EnqueueElement(Queue_1, &Var3); printf("Add(3)-> %i\n", ret);

    printf("======================\n");

    /*DequeueElement*/
    returnVal = DequeueElement(Queue_1, &ret); printf("Dequeue(1)-> %i\n", ret);
    printf("first DequeueElement >> %i\n", *((int *)returnVal));

    returnVal = DequeueElement(Queue_1, &ret); printf("Dequeue(2)-> %i\n", ret);
    printf("second DequeueElement >> %f\n", *((float *)returnVal));

    returnVal = DequeueElement(Queue_1, &ret); printf("Dequeue(3)-> %i\n", ret);
    printf("third DequeueElement >> %c\n", *((char *)returnVal));

    // returnVal = DequeueElement(Queue_1, &ret); printf("Dequeue(3)-> %i\n", ret);
    // printf("third DequeueElement >> %i\n", *((int *)returnVal));

    GetQueueCount(Queue_1, &noElemnts);
    printf("noElemnts = %u\n", noElemnts);
    printf("======================\n");
    ret = EnqueueElement(Queue_1, &Var1); 
    ret = EnqueueElement(Queue_1, &Var2);

    GetQueueCount(Queue_1, &noElemnts);
    printf("noElemnts = %u\n", noElemnts);

    returnVal = QueueRear(Queue_1, &ret); printf("QueueRear(1)-> %i\n", ret);
    printf("QueueRear >> %f\n", *((float *)returnVal));

    returnVal = QueueFront(Queue_1, &ret); printf("QueueRear(1)-> %i\n", ret);
    printf("QueueFront >> %i\n", *((int *)returnVal));
    
    GetQueueCount(Queue_1, &noElemnts);
    printf("noElemnts = %u\n", noElemnts);

    return 0;
}