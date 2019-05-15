
#include <stdio.h>
#include <malloc.h>

typedef struct QueueNode
{
    int index;
    int val;
}QueueNode;

typedef struct MonoQueue
{
    QueueNode* node;
    int head;
    int tail;
    int cap;
    // Head >>>>>>>>>>>>> Tail
    // Front >>>>>>>>>>>> Rear
}MonoQueue;

void mq_init(MonoQueue* mq, int cap)
{
    mq->node = (QueueNode*)malloc(sizeof(QueueNode) * cap);
    mq->head = 0;
    mq->tail = 0;
    mq->cap = cap;
}

void mq_free(MonoQueue* mq) { free(mq->node); }
int mq_is_empty(MonoQueue* mq){return (mq->tail < mq->head);}
int mq_is_full(MonoQueue* mq){return ((mq->tail - mq->head + 1) == mq->cap);}

/*!
 * @brief 获取队头，即最大值
 *
 */
QueueNode mq_front(MonoQueue* mq) { return mq->node[mq->head % mq->cap]; }

/*!
 * @brief 获取队尾元素
 *
 */
QueueNode mq_rear(MonoQueue* mq) { return mq->node[mq->tail % mq->cap]; }

/*!
 * @brief Pop队头元素
 */
void mq_pop_front(MonoQueue* mq) { mq->head ++; }

/*!
 * @brief Pop队尾元素
 */
void mq_pop_rear(MonoQueue* mq) { mq->tail--; }

/*!
 * @brief 从队尾插入元素
 *
 */
void mq_push_rear(MonoQueue* mq, QueueNode p)
{
    while(!mq_is_empty(mq) && mq_rear(mq).val < p.val)
        mq_pop_rear(mq);
    mq->tail++;
    mq->node[mq->tail % mq->cap].index = p.index;
    mq->node[mq->tail % mq->cap].val = p.val;
}

void mq_print(MonoQueue* mq)
{
    printf("Head --> Tail:\n");
    for (int k = mq->head; k <= mq->tail; k ++)
        printf("%d ", mq->node[k % mq->cap].val);
    printf("\n");
}


/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize)
{
#if(1)
    if(numsSize == 0)
    {
        *returnSize = 0;
        return (int*)0;
    }
    if(k == 1)
    {
        *returnSize = numsSize;
        return nums;
    }

    *returnSize = numsSize - k + 1;
    int  retSize = *returnSize;
    int* ret = (int*)malloc(sizeof(int) * (retSize));

    MonoQueue mq;
    mq_init(&mq, numsSize);
    for (int n = 0; n < k; n ++)
    {
        QueueNode p;
        p.index = n;
        p.val = nums[n];
        mq_push_rear(&mq, p);
    }
    for (int n = 0; n < retSize; n ++)
    {
        ret[n] = mq_front(&mq).val;
        if (mq_front(&mq).index <= n)
            mq_pop_front(&mq);
        QueueNode p;
        p.index = n + k;
        p.val = nums[n + k];
        mq_push_rear(&mq, p);
    }
    mq_free(&mq);

    return ret;

#else

    // LeetCode上看到的一个算法，真正的O(n)
    int n = numsSize;
    if (n==0)
    {
        *returnSize = 0;
        return NULL;
    }
    
    *returnSize = n-k+1>0 ? n-k+1 : 1;
    int*ret = (int*)malloc(sizeof(int)*(*returnSize));
    int left[n], right[n];
    int i,j;
    left[0] = nums[0];
    right[n-1] = nums[n-1];
    for (i = 1; i < n; i++)
    {
        left[i] = (i%k == 0) ? nums[i] : (nums[i]>left[i-1] ? nums[i]:left[i-1]);
        j = n - i -1;
        right[j] = (j%k == 0) ? nums[j] : (nums[j]>right[j+1] ? nums[j]:right[j+1]);
    }
    for (i = 0; i < *returnSize; i++)
        ret[i] = right[i] > left[i+k-1] ? right[i] : left[i+k-1];

    printf("\nLeft:\n");
    for (i = 0; i < n; i++)
        printf("%2d", left[i]);
    printf("\nRight:\n");
    for (i = 0; i < n; i++)
        printf("%2d", right[i]);
    printf("\n");
    
    return ret;
#endif
}

int main(void)
{
    int nums[] = { 1,3,-1,-3,5,3,6,7 };
    int numsSize = sizeof(nums) / sizeof(int);
    int k = 3;
    int retSize;
    int* ret = maxSlidingWindow(nums, numsSize, k, &retSize);

    for (int n = 0; n < retSize; n ++)
        printf("%d  ", ret[n]);

    return 0;
}
