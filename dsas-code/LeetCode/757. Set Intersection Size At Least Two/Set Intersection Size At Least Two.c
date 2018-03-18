
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

/** 升序比较算法 */
int comp_interval(const void* ca, const void* cb)
{
    // a > b  : 1
    // a == b : 0
    // a < b  : -1
    int* a = (int*)ca;
    int* b = (int*)cb;
    // 按右端升序，右端相同时，按左端降序
    if ((a[1] < b[1]) ||
        (a[1] == b[1] && a[0] > b[0])) return -1;
    if (a[0] == b[0] && a[1] == b[1]) return 0;
    return 1;
}

void mov_interval(int a[2], int b[2]) {a[0] = b[0]; a[1] = b[1];}

/** 构造轴点 */
int sort_partition(int** tv, int lo, int hi)
{
    int povit[2] = {0};
    mov_interval(povit, tv[lo]);
    while (lo < hi)
    {
        while(lo < hi && comp_interval(tv[hi], povit) >= 0) hi --;
        mov_interval(tv[lo], tv[hi]);
        while(lo < hi && comp_interval(tv[lo], povit) <= 0) lo ++;
        mov_interval(tv[hi], tv[lo]);
    }
    mov_interval(tv[lo], povit);
    return lo;
}

/** 快速排序 */
void sort_interval(int** tv, int lo, int hi)
{
    if (hi - lo < 2) return;
    int mi = sort_partition(tv, lo, hi-1);
    sort_interval(tv, lo, mi);
    sort_interval(tv, mi+1, hi);
}

int intersectionSizeTwo(int** intervals, int intervalsRowSize, int intervalsColSize)
{
    if (intervalsRowSize == 0) return 0;

    // 先排序
    sort_interval(intervals, 0, intervalsRowSize);

    int size = 2;
    int i = intervals[0][1] - 1;
    int j = intervals[0][1];
    for (int k = 1; k < intervalsRowSize; k ++)
    {
        if (i < intervals[k][0] && intervals[k][0] <= j)
        {
            size ++;
            i = j;
            j = intervals[k][1];
        }
        else if (j < intervals[k][0])
        {
            size += 2;
            i = intervals[k][1] - 1;
            j = intervals[k][1];
        }
        else
        { }
    }
    return size;
}

int main()
{
    int row = 4;
    int col = 2;
    int** tv = (int**)malloc(sizeof(int*) * row);
    for (int k = 0; k < row; k ++)
        *(tv+k) = (int*)malloc(sizeof(int) * col);

    tv[0][0] = 1; tv[0][1] = 2;
    tv[1][0] = 2; tv[1][1] = 3;
    tv[2][0] = 2; tv[2][1] = 4;
    tv[3][0] = 4; tv[3][1] = 5;

    //sort_interval(tv, 0, row);
    //for (int k = 0; k < row; k ++)
    //    printf("%d, %d\n", tv[k][0], tv[k][1]);
    printf("Size: %d\n", intersectionSizeTwo(tv, row, col));

    for (int k = 0; k < row; k ++)
        free(*(tv+k));
    free(tv);
    return 0;
}
