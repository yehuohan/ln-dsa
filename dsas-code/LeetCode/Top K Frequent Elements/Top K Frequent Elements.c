
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define CAP_SIZE        5

typedef struct Vector
{
    int* array;
    int size;
}Vector;
typedef Vector* VectorPtr;

/*!
 * @brief 初始化Vector
 */
void initVector(Vector* vec)
{
    vec->array = (int*)malloc(sizeof(int) * CAP_SIZE);
    vec->size = 0;
}

/*!
 * @brief 释放Vector
 *
 */
void freeVector(Vector* vec)
{
    free(vec->array);
}

/*!
 * @brief 扩展Vector容量
 *
 */
void expandVector(Vector* vec)
{
    int* t = (int*)malloc(sizeof(int) * vec->size*2);
    for (int k = 0; k < vec->size; k ++)
        t[k] = vec->array[k];
    free(vec->array);
    vec->array = t;
}

/*!
 * @brief 插入Vector元素
 *
 */
void pushVector(Vector* vec, int val)
{
    if (vec->size >= CAP_SIZE)
        expandVector(vec);
    vec->array[vec->size++] = val;
}


#define HASH_SIZE       1021

// Hash <key=number, val=freq>
typedef struct HashItem
{
    int key;
    int val;
    int visited;
    struct HashItem* next;
}HashItem;
typedef HashItem* HashItemPtr;

typedef struct HashTable
{
    int num;
    HashItemPtr* ht;
}HashTable;

/*!
 * @brief 初始化HashItem
 */
int initHashItem(HashItemPtr* hi, int key, int val)
{
    if (!*hi)
    {
        *hi = (HashItemPtr)malloc(sizeof(HashItem));
        (*hi)->key = key;
        (*hi)->val = val;
        (*hi)->visited = 0;
        (*hi)->next = NULL;
    }
    else
    {
        HashItemPtr n = *hi;
        HashItemPtr p;
        while (n)
        {
            if (n->key == key)
            {
                n->val += val;
                return 0;       // 未插入新key-val
            }
            p = n;
            n = n->next;
        }
        HashItemPtr x = (HashItemPtr)malloc(sizeof(HashItem));
        x->key = key;
        x->val = val;
        x->visited = 0;
        x->next = NULL;
        p->next = x;
    }
    // 插入新key-val
    return 1;
}

/*!
 * @brief 释放HashItem
 */
void freeHashItem(HashItemPtr hi)
{
    HashItemPtr n = hi, t;
    while(n)
    {
        t = n;
        n = n->next;
        free(t);
    }
}

/*!
 * @brief 初始化HashTable
 */
void initHash(HashTable* hash)
{
    hash->ht = (HashItemPtr*)malloc(sizeof(HashItemPtr) * HASH_SIZE);
    for (int k = 0; k < HASH_SIZE; k ++)
        hash->ht[k] = NULL;
    hash->num = 0;
}

/*!
 * @brief 释放HashTable
 */
void freeHash(HashTable* hash)
{
    for (int k = 0; k < HASH_SIZE; k ++)
        if (hash->ht[k])
            freeHashItem(hash->ht[k]);
    free(hash->ht);
}

/*!
 * @brief 计算Hash键
 */
int hashKey(int key)
{
    if (key < 0)
        key = -key;
    return key % HASH_SIZE;
}

/*!
 * @brief 添加key-value
 */
void putKeyVal(HashTable* hash, int key, int val)
{
    int index = hashKey(key);
    if (initHashItem(&hash->ht[index], key, val))
        hash->num ++;
}

/*!
 * @brief 根据key读取值
 */
int getVal(HashTable* hash, int key, int* val)
{
    HashItemPtr n = hash->ht[hashKey(key)];
    while(n)
    {
        if (n->key == key)
        {
            // 只能取出一次键值
            if (!n->visited)
            {
                *val = n->val;
                n->visited = 1;
                return 1;
            }
            else
                break;
        }
        n = n->next;
    }
    return 0;
}

/*!
 * @brief 判断是否存在key
 */
int containVal(HashTable* hash, int key)
{
    if (hash->ht[hashKey(key)])
        return 1;
    return 0;
}

/*!
 * @brief 输出HashTable
 */
void printHash(const HashTable* hash)
{
    for (int k = 0; k < HASH_SIZE; k ++)
    {
        HashItemPtr n = hash->ht[k];
        if (n)
            printf("\n");
        while (n)
        {
            printf("(%d, %d)", n->key, n->val);
            n = n->next;
        }
    }
    printf("\n");
}


/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* topKFrequent(int* nums, int numsSize, int k, int* returnSize)
{
    // HashTable排序
    int* ret = (int*)malloc(sizeof(int) * k);

    if (1 == k && k == numsSize)
    {
        ret[0] = nums[0];
        *returnSize = k;
        return ret;
    }

    HashTable hash;
    initHash(&hash);
    for (int n = 0; n < numsSize; n ++)
        putKeyVal(&hash, nums[n], 1);

    VectorPtr* sort = (VectorPtr*)malloc(sizeof(VectorPtr) * numsSize);
    int index;
    for (int n = 0; n < numsSize; n ++)
        sort[n] = NULL;
    for (int n = 0; n < numsSize; n ++)
    {
        if (getVal(&hash, nums[n], &index))
        {
            // 下标从0开始，而frequency >= 1
            index--;
            if (!sort[index])
            {
                sort[index] = (Vector*)malloc(sizeof(Vector));
                initVector(sort[index]);
            }
            pushVector(sort[index], nums[n]);
        }
    }

    index = 0;
    for (int n = numsSize - 1; n >= 0; n --)
    {
        if (sort[n])
        {
            for (int i = 0; i < sort[n]->size; i++)
            {
                ret[index++] = sort[n]->array[i];
                if (index >= k)
                    goto LOOP_END;
            }
        }
    }
LOOP_END:
    for (int n = 0; n < numsSize; n ++)
        if (sort[n])
            freeVector(sort[n]);
    free(sort);

    //printHash(&hash);

    *returnSize = k;
    return ret;
}

int main()
{
    int nums[] = { 6,0,1,4,9,7,-3,1,-4,-8,4,-7,-3,3,2,-3,9,5,-4,0};
    int size = sizeof(nums) / sizeof(int);
    int k = 6;
    int ret_size;
    int* ret = topKFrequent(nums, size, k, &ret_size);
    for (int k = 0; k < ret_size; k ++)
        printf("%d  ", ret[k]);
}
