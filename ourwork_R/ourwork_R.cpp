//ourwork
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
#include<math.h>
#include <time.h>
#include "RTree.h"
using namespace std;
#define INF 2100000000


#define N 2000
#define AllDimesionNum 16
#define DimensionNum 8
#define CharNum 2
#define MaxLength 20

#define FIELD_VALUE_MIN -1
#define FIELD_VALUE_MAX 26

#define DISTANCE_THRESHOLD 1000
#define MULTIPLY_NUMBER 100000


struct people
{
    int id;
    //org==0&&dup==1
    bool type;
    int dupid;

    int record[DimensionNum][MaxLength];
    int field[DimensionNum * CharNum];
}peo[N + 10];


struct peoDistance
{
	int dis;
	int num;
};

//function list
int calPeoDistance(people px, people py);
bool MySearchCallback(int id, void* arg);
void input();
void init();
int CountAllTheDup();
bool cmpDup(people px, people py);
bool cmpDis(peoDistance dx, peoDistance dy);

int nowIndex = 0;
int searchOut = 0;
int hitOut = 0;

int hitCnt[1000];
int dupCnt[1000];


bool MySearchCallback(int id, void* arg)
{
	int index = id % MULTIPLY_NUMBER;
	int num = id / MULTIPLY_NUMBER;

	//if(calPeoDistance(peo[nowIndex], peo[index]) <= DISTANCE_THRESHOLD)
	int distance = calPeoDistance(peo[nowIndex], peo[index]);
    //printf("id = %d nowindex = %d index = %d distance = %d\n", id, nowIndex, index, distance);
    if(nowIndex > index)
	    hitCnt[distance]++;
	//printf("nowIndex = %d, nowNum = %d, Hit data rect %d ", nowIndex, peo[nowIndex].num, id);
	if(num == peo[nowIndex].id && nowIndex > index)
	{
		dupCnt[distance]++;
		//searchOut ++;
		//printf("search out!");
	}
	return true; // keep going
}

//输入函数
void input()
{
	int i;
    int cnt = 0;
    char temps[1000];
    char tempc = '\0';
	int tempi=-1;
	gets(temps);//the header

    for(i = 0; i < N; i++)
    {
		scanf("%d",&peo[i].id);
		scanf("%d",&peo[i].type);
		scanf("%d", &peo[i].dupid);

        for(int j = 0; j < AllDimesionNum; j++)
        {
            for(int k = 0; k < MaxLength; k++)
            {
                scanf("%d", &peo[i].record[j][k]);
                if(peo[i].record[j][k] > 25)
                    printf("%d\n", peo[i].record[j][k]);
            }
        }
	}
}

//初始化函数
//把record的东西放到field中去
void init()
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < DimensionNum; j++)
        {
            for(int k = 0; k < CharNum; k++)
            {
                peo[i].field[j * CharNum + k] = peo[i].record[j][k];
            }
        }
    }
    return;
}


//找出所有实际存在的重复记录数
int CountAllTheDup()
{
	int i,j;
	int dupCount=0;
	for(i=0;i<N;i++)
	{
		for(j=i+1;j<N;j++)
		{
			if(peo[i].id ==peo[j].id)
			{
				dupCount++;
			}
		}
	}
	return dupCount;
}


//对记录按照id进行排序
bool cmpDup(people px, people py)
{
    if(px.id != py.id)
	    return px.id < py.id;
    if(px.type != py.type)
	    return px.type < py.type;
    if(px.dupid != py.dupid)
	    return px.dupid < py.dupid;
}


bool cmpDis(peoDistance dx, peoDistance dy)
{
	return dx.dis < dy.dis;
}


int calPeoDistance(people px, people py)
{
	int distance=0;
    for (int i = 0; i < DimensionNum * CharNum; i++)
	{
		if(px.field[i] != -1 && py.field[i] != -1)
		{
			distance += abs(px.field[i] - py.field[i]);
		}
	}
	return distance;
}

peoDistance peoDis[N+10][N+10];

clock_t clockBegin, clockInsertEnd, clockEnd;

int main()
{
    freopen("dataset2000extractALLDimensions.txt","r",stdin);
    freopen("dataset2000ourwork_R8D.txt","w",stdout);
    srand((unsigned)time(NULL));
    
	int i, j;
	input();
    init();
	sort(peo,peo+N,cmpDup);

    //find all existed dups
	int dupCount=CountAllTheDup();
	printf("dupcount=%d\n",dupCount);

    //初始化R树
    RTree<int, int, DimensionNum * CharNum, float> tree;
    
    //将结点插入R树中
    clockBegin = clock();
	for (int i = 0; i < N; i++)
	{
        int a[DimensionNum * CharNum];
        int b[DimensionNum * CharNum];
		for (int j = 0; j < (DimensionNum * CharNum); j++)
		{
			if(peo[i].field[j] == -1)
			{
                a[j] = FIELD_VALUE_MIN;
				b[j] = FIELD_VALUE_MAX;
			}
			else
			{
                //a[j] = peo[i].field[j] + rand()%2;
                a[j] = peo[i].field[j];
                b[j] = a[j];
			}
		}
        //printf("%d %d %d\n", peo[i].id, peo[i].type, peo[i].dupid);
        //for (int j = 0; j < DimensionNum * CharNum; j++)
        //{
        //    printf("%d ", a[j]);
        //}
        //puts("");
		tree.Insert(a, b, (peo[i].id*MULTIPLY_NUMBER + i));
	}
    clockInsertEnd = clock();

	hitOut = 0;
	searchOut = 0;
	memset(hitCnt, 0, sizeof(hitCnt));
	memset(dupCnt, 0, sizeof(dupCnt));
	for (int i = 0; i < N; i++)
	{
		int a[DimensionNum * CharNum];
		int b[DimensionNum * CharNum];
		for (int j = 0; j < (DimensionNum * CharNum); j++)
		{
			a[j] = FIELD_VALUE_MIN;
			b[j] = FIELD_VALUE_MAX;
		}
		nowIndex = i;
		int tmp = tree.Search(a, b, MySearchCallback, NULL);
	//printf("hitOut = %d searchOut = %d\n", hitOut, searchOut);
	//printf("for %8d comparasion , we find %8d dups", hitOut, searchOut);
	//printf(" , the recall is %9.8lf\n",(double)searchOut/dupCount);
	}
    clockEnd = clock();
	for(int i = 0; i <= 900; i++)
	{
		hitCnt[i] += hitCnt[i-1];
		dupCnt[i] += dupCnt[i-1];
		printf("for %8d comparasion , we find %8d dups", hitCnt[i], dupCnt[i]);
		printf(" , the recall is %9.8lf\n",(double)dupCnt[i]/dupCount);
	}
    printf("\nInsert operation spents %lf seconds.\n", (float)(clockInsertEnd - clockBegin)/1000.0);
    printf("\nSearch operation spents %lf seconds.\n", (float)(clockInsertEnd - clockBegin)/1000.0);

    return 0;   
}
