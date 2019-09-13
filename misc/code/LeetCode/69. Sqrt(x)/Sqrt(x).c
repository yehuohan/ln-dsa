
#include <stdio.h>
#include <math.h>

int mySqrt(int x)
{
    if(x < 0) return -1;
    if(x == 0) return 0;
    if(x == 1) return 1;
    if(x >= 2147395600) return 46340;
    // sqrt(2^31) = 46340.9500118.....

    int low = 0, up = x;
    int mid = (low + up)/2;
    if(mid > 46340)
    {
        mid = 46340;
        up = 46340*2;
    }
    int last = mid;
    do
    {
        if(mid*mid > x)
            up = mid;
        else
        {
            // 精度为1.0即可
            if((mid+1)*(mid+1) > x)
                break;
            low = mid;
        }
        last = mid;
        mid = (up + low)/2;
    }while(1);
    return mid;
}

float eps = 0.1f;

/*!
 * @brief 二分法
 *
 */
float sqrt2(int x)
{
    if(x < 0)
        return -1;

    float low = 0, up = x;
    float mid = (low + up)/2;
    float last = mid;
    do
    {
        if(mid*mid > x)
            up = mid;
        else
            low = mid;
        last = mid;
        mid = (up + low)/2;
    }while(abs(mid-last) >= eps);
    return mid;
}

float sqrtn2(int x)
{
    // 牛顿迭代法
    float val = x;
    float last;
    do
    {
        last = val;
        val = (val + x/val)/2;
    }while(abs(val-last)>eps);
    return val;
}

float InvSqrt(float x)
{
    // O(1) 神算法~~
    float xhalf = 0.5f*x;
    int i = *(int*)&x;              // get bits for floating VALUE
    i = 0x5f375a86 - (i>>1);        // gives initial guess y0       // what the fuck?
    x = *(float*)&i;                // convert bits BACK to float
    x = x*(1.5f-xhalf*x*x);         // Newton step, repeating increases accuracy
    x = x*(1.5f-xhalf*x*x);         // Newton step, repeating increases accuracy
    x = x*(1.5f-xhalf*x*x);         // Newton step, repeating increases accuracy

    return 1/x;
}

int main()
{
    int n = 123;
    printf("mySqrt  : %d\n", mySqrt(n));
    printf("Sqrt2   : %f\n", sqrt2(n));
    printf("Sqrtn2  : %f\n", sqrtn2(n));
    printf("InvSqrt : %f\n", InvSqrt(n));
    return 0;
}



