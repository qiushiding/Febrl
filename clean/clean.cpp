//把文件中的第一行（表头），空行，逗号去除 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
using namespace std;

//dataset2_1000_1000_3_2_4_zipf_all_1
//dataset2_5000_5000_9_5_5_zipf_all_1

int main()
{
    
    freopen("dataset10000.txt","r",stdin);
    freopen("dataset10000clean.txt","w",stdout);

    int i,j;
    int cnt=0;
    char s1[1000];
	char s2[1000];
    gets(s1);
    
    while(gets(s1)) 
    {
        if(s1[0]=='r')
        {
            int len = strlen(s1);
			int flag=0;
			int lens2 = 0 ;
            for(i = 0; i < len; i++)
            {
                if(s1[i]!=' ')
                {
                    if(s1[i]==',')
                    {
						if(flag==1)
						{
							s2[lens2++]='-';
							s2[lens2++]='1';
						}
						s2[lens2++]=' ';
						s2[lens2++]=' ';
						flag=1;
                    }
                    else
                    {
						flag=0;
                        s2[lens2++]=s1[i];
                    }
                }
            }
			s2[lens2]='\0';
			printf("%s",s2);
            puts("");
        }
    }
    
    //system("pause");
    return 0;
}
