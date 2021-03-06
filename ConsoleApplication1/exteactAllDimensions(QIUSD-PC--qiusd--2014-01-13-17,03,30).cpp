//��ȡkey��Ϣ 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
using namespace std;

//dataset2_1000_1000_3_2_4_zipf_all_1
//dataset2_5000_5000_9_5_5_zipf_all_1

#define N 2000
#define DimensionNum 16
#define MaxLength 20


struct people
{
    int id;
    bool type;//org==0&&dup==1
    int dupid;

    int num[DimensionNum];
    int record[DimensionNum][MaxLength];
}peo[N + 10];


void outputNum(int x)
{
	if(x != -1 && x >= 0 && x < 100)
	{
		printf("%3d ", x/10);
	}
	else
	{
		printf("-1  ");
	}

	if(x != -1 && x >= 0 && x < 100)
	{
		printf("%3d ", x%10);
	}
	else
	{
		printf("-1  ");
	}
	return;
}

void init()
{
    int i,j,k;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < DimensionNum; j++)
        {
            for(int k = 0; k < MaxLength; k++)
            {
                peo[i].record[j][k] = -1;
            }
        }
    }
    return;
}


int main()
{
    freopen("dataset2000clean.txt","r",stdin);
    freopen("dataset2000extractALLDimensions.txt","w",stdout);
    

    int cnt = 0;
    char temps[1000];
    char tempc;
	int tempi=-1;
    
    init();

	printf("num, typ, dup, culture, sex, age, date_of_birth, title, given_name, surname, state, suburb, postcode, street_number, address_1, address_2, phone_number, soc_sec_id, blocking_number\n");


    for(int i = 0; i < N; i++)
    {
        //rec_id
        scanf("rec-%d-", &peo[i].num);
        scanf("%c", &tempc);
        if(tempc == 'o')
        {
            peo[i].type = 0;
            peo[i].dupid = -1;
			scanf("%s",temps);
        }
        else
        {
            peo[i].type = 1;
            scanf("up-%d", &peo[i].dupid);
        }

        //rec2_id
		scanf("%s",temps);

        //all 16 dimensions
        for(int j = 0; j < DimensionNum; j++)
        {
            scanf("%s", temps);
            if(temps[0] == '-')
                continue;
            int len = strlen(temps);
            for(int k = 0; k < len; k++)
            {
                peo[i].record[j][k] = temps[k] - '\0';
            }
        }

		//family_role
		gets(temps);
		
        //output info
        printf("%3d %3d %3d ",peo[i].num, peo[i].type, peo[i].dupid);

        for(int j = 0; j < DimensionNum; j++)
        {
            for (int k = 0; k < MaxLength; k++)
            {
                printf("%d ", peo[i].record[j][k]);
            }
        }



		printf("\n");

        
    }
    return 0;
}
