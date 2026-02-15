#include "find.h"

int find(char *arr, int n)
{
    int count = 0;
    int length_group = 0;
    for(int i = 0; i < n; i++)
    {
        if(arr[i]=='0' or arr[i]=='1')
        {
            length_group += 1;
        }else if(arr[i]==' ' or arr[i]=='\0')
        {
            if(length_group==5)
            {
                count += 1;
            }
            length_group = 0;
        }
    }
    if(length_group == 5)
    count++;

    return count;
}
