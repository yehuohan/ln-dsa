
bool isPowerOfFour(int num) {
    int n0  = 0x00000001;      // n = 0
    int n1  = n0 << 2;
    int n2  = n1 << 2;
    int n3  = n2 << 2;
    int n4  = n3 << 2;
    int n5  = n4 << 2;
    int n6  = n5 << 2;
    int n7  = n6 << 2;
    int n8  = n7 << 2;
    int n9  = n8 << 2;
    int n10 = n9 << 2;
    int n11 = n10 << 2;
    int n12 = n11 << 2;
    int n13 = n12 << 2;
    int n14 = n13 << 2;
    int n15 = n14 << 2;
    
    if((num == n0)
        ||(num == n1)
        ||(num == n2)
        ||(num == n3)
        ||(num == n4)
        ||(num == n5)
        ||(num == n6)
        ||(num == n7)
        ||(num == n8)
        ||(num == n9)
        ||(num == n10)
        ||(num == n11)
        ||(num == n12)
        ||(num == n13)
        ||(num == n14)
        ||(num == n15))
    {
        return true;
    }
    else 
    {
        return false;
    }
}
