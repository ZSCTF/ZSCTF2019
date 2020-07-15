#include<stdio.h>
static char key[]="abcdefghiABCDEFGHIJKLMNjklmn0123456789opqrstuvwxyzOPQRSTUVWXYZ";
static char end[]="zsctf2019happy";

void er(void)
{
    printf("error");
}

void cmp(int *offest)
{
    int i=0;
    char str[16];
    while(offest[i]<62 && offest[i]>=0)
    {
        str[i]=key[i];
        ++i;
    }
    str[i]=0;
    if(!strcmp(str,end))
        printf("Great!!This is flag");
    else
        er();
}


int main(void)
{
    int i;
    char input[24]=0;
    int check[24]=0;
    printf("Input your flag:\n");
    scanf_s("%s",&input,20);
    if(!strlen(input))
    {
        er();
    }
    
    for ( i = 0; input[i]; ++i )
    {
        printf("%d", input[i]);
        if ( input[i] > '9' || input[i] < '0' )
        {
            if ( input[i] > 'z' || input[i] < 'a' )
            {
                if ( input[i] > 'Z' || input[i] < 'A' )
                    er();
                else
                    check[i] = input[i] - 29;
            }
            else
            {
                check[i] = input[i] - 87;
            }
        }
        else
        {
            check[i] = input[i] - 48;
        }
    }

    cmp(check);

    return 0;
}