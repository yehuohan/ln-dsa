
#include <stdio.h>
#include <malloc.h>


typedef struct Stack
{
    int* s;
    int top;
}Stack;

/*!
 * @brief 初始化Stack
 *
 * @param size: 栈容量
 * @return
 * @retval None
 */
void st_init(Stack* s, int size)
{
    s->s = (int*)malloc(sizeof(int) * size);
    s->top = -1;
}

void st_free(Stack* s) { free(s->s); }
int st_top(Stack* s) { return s->s[s->top]; }
int st_is_empty(Stack* s) { return (s->top < 0) ? 1 : 0; }

/*!
 * @brief 入栈
 *
 */
void st_push(Stack* s, int val) { s->s[++s->top] = val; }

/*!
 * @brief 出栈
 */
int st_pop(Stack* s)
{
    if (!st_is_empty(s))
    {
        s->top --;
        return s->s[s->top + 1];
    }
}


int main(void)
{
    return 0;
}
