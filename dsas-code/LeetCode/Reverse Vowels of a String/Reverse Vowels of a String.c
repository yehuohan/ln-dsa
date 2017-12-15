#include <stdio.h>
#include <malloc.h>
#include <string.h>

int isVowel(char c)
{
    return strchr("aeiouAEIOU", c);
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
        c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
        return 1;
    return 0;
}

char *reverseVowels(char *s)
{
	// conuting the length of string
	int n = strlen(s);
    char* rs = (char*)malloc(sizeof(char) * (n+1));
    *(rs + n) = '\0';
	int i = 0;
	int j = n - 1;
    while(1)
    {
        while(i < j && !isVowel(*(s+i)))
        {
            rs[i] = s[i];
            i ++;
        }
        while(i < j && !isVowel(*(s+j)))
        {
            rs[j] = s[j];
            j--;
        }
        rs[i] = s[j];
        rs[j] = s[i];
        i ++;
        j --;
		if(i > j)
			break;
    }
    return rs;
}

int main()
{
    char* rs = reverseVowels("hello");
    printf("%s",rs);
	return 0;
}
