
#include <stdio.h>
#include <malloc.h>
#include <string.h>

char* reverseString(char* s)
{
    int k = strlen(s); 
	char *rs = (char*)malloc(k+1);
	rs[k] = '\0';
	int i = 0; 
	int j = k - 1;
	while(1)
	{
        rs[i] = s[j];
        rs[j] = s[i];
	    i++;
	    j--;
	    if(i > j)
	        break;
	}
	return rs; 
}

int main()
{
    char* s = reverseString("hello world");
    printf("%s", s);
    return 0;
}
