#include<stdio.h>
#include <cstdlib>
#include "string.h"

int main()
{
    int n;
    scanf("%d",&n);
    char v[n][4];
    int dist[n][n];
    char v1[4],v2[4];
    int index[2];
    for (int i = 0; i < n; ++i) {
        scanf("%s",v[i]);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &dist[i][j]);
        }
    }

    for (int k = 0; k < n; ++k)// 以k为中转
        for (int i = 0; i < n; ++i)// 从i
            for (int j = 0; j < n; ++j)// 到达j的距离
            {
                if(dist[i][j]>dist[i][k]+dist[k][j])//若中转距离小于原距离
                    dist[i][j]=dist[i][k]+dist[k][j];
            }

    scanf("%s",v1);
    for (int i = 0; i < n; ++i) {
        if(strcmp(v[i],v1)==0)
        {index[0]=i;
        break;}
    }
    scanf("%s",v2);
    for (int i = 0; i < n; ++i) {
        if(strcmp(v[i],v2)==0)
        {index[1]=i;
        break;}
    }

    printf("%d",dist[index[0]][index[1]]);
}