#include<bits/stdc++.h>
#define random(x) (rand()%x)
const int n = 15;           //初始队列插入元素个数
const int L = 15;          //初始插入外，命令总个数
const int randomMax = 200;  //元素最大值 + 1
int main()
{
    srand((int)time(0));    //随机数种子

    freopen("Sqtest.in","w",stdout);  //输出到文件

    printf("%d\n",L + n + 1);

    printf("0\n");
    //以Insert的形式进行插入
    for(int i = 1;i <= n;++i)
        printf("8 %d %d\n",i,random(randomMax));

    for(int i = 1;i <= L;++i)
    {
        int x = random(10) + 1; //不要Init命令
        switch(x){
            case 0://Init
                printf("0\n");
                break;
            case 1://Clear
                printf("1\n");
                break;
            case 2://Empty
                printf("2\n");
                break;
            case 3://Length
                printf("3\n");
                break;
            case 4://Get
                printf("4 %d\n",random(n));
                break;
            case 5://Locate
                printf("5 %d\n",random(randomMax));
                break;
            case 6://Prior
                printf("6 %d\n",random(randomMax));
                break;
            case 7://Next
                printf("7 %d\n",random(randomMax));
                break;
            case 8://Insert
                printf("8 %d %d\n",random(n),random(randomMax));
            case 9://Delete
                printf("9 %d\n",random(n));
            case 10://Travel
                printf("10\n");
        }

    }
    return 0;
}
