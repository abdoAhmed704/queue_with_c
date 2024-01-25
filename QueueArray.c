#include "QueueArray.h"

static uint8 QueueIsFull(Queue_t *queue_obj)
{
    return (queue_obj->QueueMaxSize == queue_obj->ElementCount);
}

static uint8 QueueIsEmpty(Queue_t *queue_obj)
{
    return (queue_obj->ElementCount == 0);
}

Queue_t *CreateQueue(uint32 maxSize, QueueStatus_t *ret_status)
{
    Queue_t *queue_ptr = NULL;

    if (!ret_status)
    {
        *ret_status = QUEUE_NOK;
        queue_ptr = NULL;
    }
    else
    {

        queue_ptr = malloc(sizeof(Queue_t));
        if (NULL == queue_ptr)
        {
            queue_ptr = NULL;
            *ret_status = QUEUE_NULL_POINTER;
        }

        else
        {
            queue_ptr->QueueMaxSize = maxSize;
            queue_ptr->QueueFront = -1;
            queue_ptr->QueueRear = -1;
            queue_ptr->ElementCount = 0;
            queue_ptr->QueueArray = (void **)calloc(queue_ptr->QueueMaxSize, sizeof(void *));
            if (!queue_ptr->QueueArray)
            {
                free(queue_ptr);
                queue_ptr = NULL;
                *ret_status = QUEUE_NULL_POINTER;
            }
            else
            {
                *ret_status = QUEUE_OK;
            }

        }

    }
    return (queue_ptr);
}

QueueStatus_t EnqueueElement(Queue_t *queue_obj, void *item_ptr)
{
    QueueStatus_t ret_status = QUEUE_NOK;

    if (!queue_obj || ! item_ptr)
    {
        ret_status = QUEUE_NULL_POINTER;
    }
    else
    {
        if (QueueIsFull(queue_obj))
        {
            ret_status = QUEUE_FULL;
        }
        else
        {
            if (queue_obj->ElementCount == 0)
            {
                queue_obj->QueueFront = 0;
                queue_obj->ElementCount = 1;
            }
            else
            {
                (queue_obj->ElementCount)++;
            }
            (queue_obj->QueueRear)++;
            if (queue_obj->QueueRear == (queue_obj->QueueMaxSize))
                queue_obj->QueueRear = 0;
            queue_obj->QueueArray[queue_obj->QueueRear] = item_ptr;
            
            ret_status = QUEUE_OK;
        }
    }
    return (ret_status);
}

void *DequeueElement(Queue_t *queue_obj, QueueStatus_t *ret_status)
{
    void *value = NULL;
    if (!queue_obj || !ret_status)
    {
        *ret_status = QUEUE_NULL_POINTER;
    }
    else
    {
        if (QueueIsEmpty(queue_obj))
        {
            *ret_status = QUEUE_EMPTY;
            value = NULL;
        }  
        else
        {
            value = queue_obj->QueueArray[queue_obj->QueueFront];
            (queue_obj->QueueFront)++;
            if (queue_obj->QueueFront == queue_obj->QueueMaxSize)/*BUT THERE IS MORE ELEMENTS*/
            {
                queue_obj->QueueFront = 0;
            }
            /*if there is One Element*/
            if (queue_obj->ElementCount == 1)
            {
                queue_obj->QueueRear = -1;
                queue_obj->QueueFront = -1;
            }
            (queue_obj->ElementCount)--;
            *ret_status = QUEUE_OK;
        }

    }
    return (value);
}

void *QueueFront(Queue_t *queue_obj, QueueStatus_t *ret_status)
{
    void *returnValue = NULL;

    if (!queue_obj || !ret_status)
    {
        returnValue = NULL;
        *ret_status = QUEUE_NULL_POINTER;
    }
    else
    {
        if(QueueIsEmpty(queue_obj))
        {
            returnValue = NULL;
            *ret_status = QUEUE_EMPTY;
        }
        else
        {
            returnValue = queue_obj->QueueArray[queue_obj->QueueFront];
            *ret_status = QUEUE_OK;
        }
    }
    return returnValue;
}

void *QueueRear(Queue_t *queue_obj, QueueStatus_t *ret_status)
{
    void *returnValue = NULL;

    if (!queue_obj || !ret_status)
    {
        returnValue = NULL;
        *ret_status = QUEUE_NULL_POINTER;
    }
    else
    {
        if(QueueIsFull(queue_obj))
        {
            returnValue = NULL;
            *ret_status = QUEUE_EMPTY;
        }
        else
        {
            returnValue = queue_obj->QueueArray[queue_obj->QueueRear];
            *ret_status = QUEUE_OK;
        }
    }
    return returnValue;
}

QueueStatus_t GetQueueCount(Queue_t *queue_obj, uint32 *QueueCount)
{
    QueueStatus_t returnStatus = QUEUE_NOK;
    if (!queue_obj || !QueueCount)
    {
        returnStatus = QUEUE_NULL_POINTER;
    }
    else
    {
        *QueueCount = queue_obj->ElementCount;
        returnStatus = QUEUE_OK;
    }
    return (returnStatus);
}

QueueStatus_t DestroyQueue(Queue_t *queue_obj)
{
    QueueStatus_t returnStatus = QUEUE_NOK;
    if (!queue_obj)
        returnStatus = QUEUE_NULL_POINTER;
    else
    {
        free(queue_obj->QueueArray);
        queue_obj->QueueArray = NULL;
        free(queue_obj);
        queue_obj = NULL;
        returnStatus = QUEUE_OK;
    }
    return (returnStatus);
}