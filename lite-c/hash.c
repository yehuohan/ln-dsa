
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
    while (n->next)
        n = n->next;
    n->next = x;
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
    int index = hs_hash_key(key);
    if (hash->ht[index])
    {
        HashItemPtr n = hash->ht[index];
        while(n)
        {
            if (n->key == key)
            {
                if (val != NULL)
                    *val = n->val;
                return 1;
            }
            n = n->next;
        }
    }
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


int main(void)
{
    return 0;
}
