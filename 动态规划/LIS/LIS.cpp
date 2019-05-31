#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
const int MAXN = 1e6+5;
const int INF = 0x7fffffff;
int n,x[MAXN],y[MAXN],lowx[MAXN],lowy[MAXN],dpx[MAXN],dpy[MAXN],lenx=1,leny=1;
// low[i] 代表长度为 i 的最长上升序列的末尾数
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        scanf("%d",&x[i]);
        y[n-i+1]=x[i];
    }
    for(int i=1;i<=n;i++)   lowx[i]=lowy[i]=INF;
    lowx[1]=x[1];
    lowy[1]=y[1];
    dpx[1]=dpy[1]=1;
    for(int i=2;i<=n;i++) {
        int pos=lower_bound(lowx+1,lowx+1+lenx,x[i])-lowx;
        lowx[pos]=min(lowx[pos],x[i]);
        lenx=max(lenx,pos);
        dpx[i]=pos;
        pos=lower_bound(lowy+1,lowy+1+leny,y[i])-lowy;
        lowy[pos]=min(lowy[pos],y[i]);
        leny=max(leny,pos);
        dpy[i]=pos;
    }
    int ans=1;
    for(int i=1;i<=n;i++) {
        int a=dpx[i]-1,b=dpy[n-i+1]-1;
        if(a>b) swap(a,b);
        ans=max(ans,a+a+1);
    }
    printf("%d\n",ans);
    return 0;
}