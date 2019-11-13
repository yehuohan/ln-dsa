
#include <stdio.h>
#include <malloc.h>

typedef struct QueueNode
{
    int index;
    int val;
}QueueNode;

typedef struct Queue
{
    QueueNode* node;
    int head;
    int tail;
    int cap;
    // Head >>>>>>>>>>>>> Tail
    // Front >>>>>>>>>>>> Rear
    // Front as max
}Queue;

void mq_init(Queue* mq, int cap)
{
    mq->node = (QueueNode*)malloc(sizeof(QueueNode) * cap);
    mq->head = 0;
    mq->tail = 0;
    mq->cap = cap;
}

void mq_free(Queue* mq) { free(mq->node); }
int mq_is_empty(Queue* mq){return (mq->tail < mq->head);}
int mq_is_full(Queue* mq){return ((mq->tail - mq->head + 1) == mq->cap);}

/*!
 * @brief 获取队头，即最大值
 *
 */
QueueNode mq_front(Queue* mq) { return mq->node[mq->head % mq->cap]; }

/*!
 * @brief 获取队尾元素
 *
 */
QueueNode mq_rear(Queue* mq) { return mq->node[mq->tail % mq->cap]; }

/*!
 * @brief Pop队头元素
 */
void mq_pop_front(Queue* mq) { mq->head ++; }

/*!
 * @brief Pop队尾元素
 */
void mq_pop_rear(Queue* mq) { mq->tail--; }

/*!
 * @brief 从队尾插入元素
 *
 */
void mq_push_rear(Queue* mq, QueueNode p)
{
    while(!mq_is_empty(mq) && mq_rear(mq).val < p.val)
        mq_pop_rear(mq);
    mq->tail++;
    mq->node[mq->tail % mq->cap].index = p.index;
    mq->node[mq->tail % mq->cap].val = p.val;
}

void mq_print(Queue* mq)
{
    printf("Head --> Tail:\n");
    for (int k = mq->head; k <= mq->tail; k ++)
        printf("%d ", mq->node[k % mq->cap].val);
    printf("\n");
}


int main(void)
{
    return 0;
}
