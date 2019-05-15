
int integerBreak(int n)
{
    // 递归法，减而治之
    if(n == 2)
        return 1;
    else if(n == 3)
        return 2;
    else if(n == 4)
        return 4;
    else
    {
        if(n - 3 > 4)
            return 3*integerBreak(n-3);
        else
            return 3*(n-3);
    }
}
