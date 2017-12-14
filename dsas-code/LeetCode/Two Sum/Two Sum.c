
#include <stdio.h>
#include <malloc.h>

#define HASH_SIZE       1021

typedef struct HashItem
{
    int key;
    int val;
    struct HashItem* next;
}HashItem;
typedef HashItem* HashItemPtr;

typedef struct HashTable
{
    HashItemPtr* ht;
}HashTable;

/*!
 * @brief 初始化HashItem
 */
void hs_init_item(HashItemPtr* hi, int key, int val)
{
    HashItemPtr x = (HashItemPtr)malloc(sizeof(HashItem));
    x->key = key;
    x->val = val;
    x->next = NULL;

    if (!*hi)
    {
        *hi = x;
        return;
    }

    HashItemPtr n = *hi;
    HashItemPtr p;
    while (n)
    {
        p = n;
        n = n->next;
    }
    p->next = x;
}

/*!
 * @brief 释放HashItem
 */
void hs_free_item(HashItemPtr hi)
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
void hs_init(HashTable* hash)
{
    hash->ht = (HashItemPtr*)malloc(sizeof(HashItemPtr) * HASH_SIZE);
    for (int k = 0; k < HASH_SIZE; k ++)
        hash->ht[k] = NULL;
}

/*!
 * @brief 释放HashTable
 */
void hs_free(HashTable* hash)
{
    for (int k = 0; k < HASH_SIZE; k ++)
        if (hash->ht[k])
            hs_free_item(hash->ht[k]);
    free(hash->ht);
}

/*!
 * @brief 计算Hash键
 */
int hs_hash_key(int key)
{
    if (key < 0)
        key = -key;
    return key % HASH_SIZE;
}

/*!
 * @brief 添加key-value
 */
void hs_put_keyval(HashTable* hash, int key, int val)
{
    int index = hs_hash_key(key);
    hs_init_item(&hash->ht[index], key, val);
}

/*!
 * @brief 根据key读取值
 */
int hs_get_val(HashTable* hash, int key, int* val)
{
    HashItemPtr n = hash->ht[hs_hash_key(key)];
    while(n)
    {
        if (n->key == key)
        {
            *val = n->val;
            return 1;
        }
        n = n->next;
    }
    return 0;
}

/*!
 * @brief 判断是否存在key
 */
int hs_contain_val(HashTable* hash, int key)
{
    if (hash->ht[hs_hash_key(key)])
        return 1;
    return 0;
}

/*!
 * @brief 输出HashTable
 */
void hs_print(const HashTable* hash)
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
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target)
{
    int* ret = (int*)malloc(sizeof(int)*2);

#if (0)
    // Brute force蛮力法, O(n^2)
    for (int k = 0; k < numsSize; k ++)
    {
        for (int j = k + 1; j < numsSize; j ++)
        {
            if (nums[k] + nums[j] == target)
            {
                ret[0] = k;
                ret[1] = j;
                return ret;
            }
        }
    }
#else
    // 哈希表法
    HashTable hash;
    hs_init(&hash);
    for (int k = 0; k < numsSize; k ++)
        hs_put_keyval(&hash, nums[k], k);
    for (int k = 0; k < numsSize; k ++)
    {
        if (hs_contain_val(&hash, target - nums[k]))
        {
            ret[0] = k;
            if (hs_get_val(&hash, target - nums[k], ret+1)
                    && ret[1] != ret[0])
                    break;
        }
    }
    hs_free(&hash);
#endif
    return ret;
}

int main(void)
{
    int nums[] = { 0,2,4,6};
    int size = sizeof(nums) / sizeof(int);
    int target = 8;
    int* ret = twoSum(nums, size, target);

    printf("%d, %d\n",ret[0], ret[1]);
    free(ret);

    return 0;
}
