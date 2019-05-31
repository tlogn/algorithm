#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
const int MAXN = 4e4+5;
int n,m,x[MAXN],chunk,tot,L[MAXN],R[MAXN],id[MAXN],h[MAXN];
int vis[MAXN],num[205][205],num_id[205][205],cnt[MAXN],numm[205][MAXN];
void build() {
    chunk=sqrt(n);
    tot=n/chunk;
    if(n%chunk) tot++;
    for(int i=1;i<=tot;i++) {   // 每个chunk的左右边界
        L[i]=(i-1)*chunk+1;  
        R[i]=i*chunk;
    }
    R[tot]=n;                   // 处理最右边的块的边界
    for(int i=1;i<=n;i++) {
        id[i]=(i-1)/chunk+1;        // 每个数归属的chunk
    }
    for(int i=1;i<=tot;i++) {       // 求块[i,j]之间的众数
        memset(cnt,0,sizeof(cnt));
        int maxn=0,maxn_id=0;
        for(int j=L[i];j<=n;j++) {
            cnt[x[j]]++;
            numm[i][x[j]]++;            // 后缀和
            if(maxn<cnt[x[j]]) {
                maxn=cnt[x[j]];
                maxn_id=x[j];
            }
            num[i][id[j]]=maxn;
            num_id[i][id[j]]=maxn_id;
        }
    }
}
void init() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) {
        scanf("%d",&x[i]);
        h[i]=x[i];
    }
    sort(h+1,h+1+n);                // 离散化
    int temp=unique(h+1,h+1+n)-(h+1);
    for(int i=1;i<=n;i++) {
        x[i]=lower_bound(h+1,h+1+temp,x[i])-h;
    }
}

int sol(int left,int right) {
    int maxn=num[id[left]+1][id[right]-1];
    for(int i=left;i<=R[id[left]];i++) {
        vis[x[i]]=0;
    }
    for(int i=L[id[right]];i<=right;i++) {
        vis[x[i]]=0;
    }
    if(id[left]==id[right]) {
        for(int i=left;i<=right;i++) {
            vis[x[i]]++;
            maxn=max(maxn,vis[x[i]]);
        }
        return maxn;
    }
    for(int i=left;i<=R[id[left]];i++) {
        vis[x[i]]++;
        maxn=max(maxn,vis[x[i]]+numm[id[left]+1][x[i]]-numm[id[right]][x[i]]);
    }
    for(int i=L[id[right]];i<=right;i++) {
        vis[x[i]]++;
        maxn=max(maxn,vis[x[i]]+numm[id[left]+1][x[i]]-numm[id[right]][x[i]]);
    }
    return maxn;
}
void solve() {
    int temp=0;
    for(int t1,t2,i=1;i<=m;i++) {
        scanf("%d%d",&t1,&t2);
        t1=(t1+temp-1)%n+1;
        t2=(t2+temp-1)%n+1;
        if(t1>t2)   swap(t1,t2);
        printf("%d\n",temp=sol(t1,t2));
    }
}
int main() {
    init();
    build();
    solve();
    return 0;
}