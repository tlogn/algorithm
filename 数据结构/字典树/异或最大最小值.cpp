#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
const int MAXN = 5e5+5;
int cnt,p[35],n,tot=0,tree[MAXN*20][2],val[MAXN*20];
bool buff[35];
void break_apart(int v) {
    cnt=0;
    while(v) {
        buff[cnt++]=(v&1);
        v=v>>1;
    }
    for(int i=cnt;i<=30;i++)  buff[i]=0;
}
void pre_process() {
    for(int i=0;i<=30;i++)  p[i]=1<<i;
}
void insert(int v) {
    break_apart(v);
    int now=0;
    for(int i=30;i>=0;i--) {
        if(!tree[now][buff[i]]) {
            tree[now][buff[i]]=++tot;
        }
        now=tree[now][buff[i]];
        val[now]++;    
    }
}
void pop(int v) {
    break_apart(v);
    int now=0;
    for(int i=30;i>=0;i--) {
        now=tree[now][buff[i]];
        val[now]--;
    }
}
int find_max(int v) {
    break_apart(v);
    int now=0,ret=0;
    for(int i=30;i>=0;i--) {
        if(val[tree[now][0]]<=0) {
            if(!buff[i])    ret+=p[i];
            now=tree[now][1];
        }
        else if(val[tree[now][1]]<=0) {
            if(buff[i])     ret+=p[i];
            now=tree[now][0];
        }
        else {
            ret+=p[i];
            if(buff[i]) now=tree[now][0];
            else    now=tree[now][1]; 
        }
    }
    return ret;
}
int find_min(int v) {
    break_apart(v);
    int now=0,ret=0;
    for(int i=30;i>=0;i--) {
        if(val[tree[now][0]]<=0) {
            if(!buff[i])    ret+=p[i];
            now=tree[now][1];
        }
        else if(val[tree[now][1]]<=0) {
            if(buff[i])     ret+=p[i];
            now=tree[now][0];
        }
        else {
            if(buff[i]) now=tree[now][1];
            else    now=tree[now][0];
        }
    }
    return ret;
}
int main() {
    pre_process();
    scanf("%d",&n);
    for(int t1,t2,i=1;i<=n;i++) {
        scanf("%d%d",&t1,&t2);
        if(t1==1) insert(t2);
        else if(t1==2)  pop(t2);
        else    printf("%d %d\n",find_min(t2),find_max(t2));
    }
    return 0;
}