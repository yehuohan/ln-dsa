
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct SectionStr
{
    char*   str;
    int     n;
}SectionStr;

void secstr_init(SectionStr* ss, int n) {ss->str = (char*)malloc(sizeof(char)*n);ss->n = n;}
void secstr_free(SectionStr* ss) {free(ss->str);}

/** SectionStr比较(降序)函数 */
int secstr_cmp(const void* a, const void* b)
{
    const SectionStr* s1 = (const SectionStr*)a;
    const SectionStr* s2 = (const SectionStr*)b;
    return -strcmp(s1->str, s2->str);
}

/*!
 * @brief 查找s中所有的short sub-special string。
 *
 * short sub-special string: 从起点开始，满足条件且连续的最短的special string。
 *
 * @param s: 查找的源字符串
 * @param n: 源字符串长度
 * @param sec: 所有sub-special string section
 * @return 返回sec的元素个数
 * @retval None
 */
int secstr_find(const char* s, int n, SectionStr sec[])
{
    int cnt = 0;
    int index = 0, index_last = index, k = 0;
    while(index < n)
    {
        if (s[index] == '1') cnt ++;
        else cnt --;
        index ++;
        if (cnt == 0)
        {
            if (sec)
            {
                secstr_init(&sec[k], index - index_last);
                strncpy(sec[k].str, s + index_last, sec[k].n);
                index_last = index;
            }
            k++;
        }
    }
    return k;
}

/** 对sub-special string进行reorder */
void make_largest_special(char* s, int n)
{
    // recursion base
    if (n <= 2) return;

    if (secstr_find(s, n, NULL) <= 1)
    {
        make_largest_special(s+1, n-2);
        return;
    }

    // find secstr
    SectionStr* sec = (SectionStr*)malloc(sizeof(SectionStr) * (n/2));
    int         num = secstr_find(s, n, sec);

    // reroder recursion 
    for (int k = 0; k < num; k ++)
        make_largest_special(sec[k].str, sec[k].n);

    // reroder
    qsort(sec, num, sizeof(SectionStr), secstr_cmp);
    for (int k = 0, index = 0; k < num; k ++)
    {
        strncpy(s+index, sec[k].str, sec[k].n);
        index += sec[k].n;
        secstr_free(&sec[k]);
    }
    free(sec);
}

char* makeLargestSpecial(char* S)
{
    make_largest_special(S, strlen(S));
    return S;
}

int main()
{
#define N   51
    char str[N] = "11011000";
    char* s = str;
    printf("%d\n", secstr_find(s, strlen(s), NULL));

    printf("src: %s\n", s);
    char* ls = makeLargestSpecial(s);
    printf("des: %s\n", ls);
}
