
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
void vec_init(Vector* vec)
{
    vec->array = (int*)malloc(sizeof(int) * CAP_SIZE);
    vec->size = 0;
}

/*!
 * @brief 释放Vector
 *
 */
void vec_free(Vector* vec) { free(vec->array); }

/*!
 * @brief 扩展Vector容量
 *
 */
void vec_expand(Vector* vec)
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
void vec_push_back(Vector* vec, int val)
{
    if (vec->size >= CAP_SIZE)
        vec_expand(vec);
    vec->array[vec->size++] = val;
}


int main(void)
{
    return 0;
}
