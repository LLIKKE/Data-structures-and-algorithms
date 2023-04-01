#include<iostream>
#include<cstring>
#define YES 1
#define NO 0
using namespace std;
int d,N;
int visited[100];
struct Point{
    int x;
    int y;
}Point[100];
int FirstJump(int i){
    int x=Point[i].x;
    int y=Point[i].y;
    if((d+7.5)*(d+7.5)>=(x*x+y*y))
        return YES;
    else return NO;
}
int Jump(int i,int j){
    int x1=Point[i].x;
    int y1=Point[i].y;
    int x2=Point[j].x;
    int y2=Point[j].y;
    if(d*d>=(x2-x1)*(x2-x1)+(y2-y1)*(y2-y1))
        return YES;
    else return NO;
}
int IsSafe(int i){
    int x=Point[i].x;
    int y=Point[i].y;
    if(x<0)
        x=-x;
    if(y<0)
        y=-y;
    if(d>=50-x||d>=50-y)
        return YES;
    else return NO;
}
int DFS(int i){
    int answer;
    visited[i]=1;
    if(IsSafe(i)) return answer=YES;
    else{
        for(int j=0;j<N;j++)
        {
            if(!visited[j]&&Jump(i,j)){
                answer=DFS(j);
                if(answer==YES) break;
            }
        }
    }
    return answer;
}
void Save007(){
    int answer=0;
    memset(visited,0,sizeof(visited));
    for(int i=0;i<N;i++) {
        if(!visited[i]&&FirstJump(i)){
            answer=DFS(i);
            if(answer==YES) break;
        }
    }
    if(answer==YES)
        cout<<"Yes";
    else
        cout<<"No";
}
int main(){
    cin>>N;
    cin>>d;
    for(int i=0;i<N;i++){
        cin>>Point[i].x;
        cin>>Point[i].y;
    }
    Save007();
    return 0;
}