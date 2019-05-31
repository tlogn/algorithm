#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
const int MAXN = 2e5+5;
int n,m,h[MAXN],x[MAXN],id[MAXN],ans[MAXN],chunk,tot,cnt[MAXN],num[MAXN];
int L=1,R=0,now=0;
struct node {       // 莫队 
    int L,R,id;     // 左边界，右边界，编号
}Q[MAXN];
bool cmp(node &v,node &u) { // 一个块看右边界，不是一个块看左边界
    if(id[v.L]==id[u.L])    return v.R<u.R;
    return v.L<u.L;
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
    for(int i=1;i<=m;i++) {
        scanf("%d%d",&Q[i].L,&Q[i].R);
        Q[i].id=i;
    }
}
void build() {
    // 分块
    chunk=sqrt(n);
    tot=n/chunk;
    if(n%chunk) tot++;
    for(int i=1;i<=n;i++) {
        id[i]=(i-1)/chunk+1;
    }

    // 莫队 排序
    sort(Q+1,Q+1+m,cmp);
}
void update(int v,int type) {
    if(type==1) {
        num[cnt[x[v]]]--;
        cnt[x[v]]++;
        num[cnt[x[v]]]++;
        if(now < cnt[x[v]])  now=cnt[x[v]];
    }
    else {
        num[cnt[x[v]]]--;
        if(cnt[x[v]]==now && !num[cnt[x[v]]])   now--;  
        // 最高的出现次数的次数归0，最高出现次数变为cnt[x[v]]-1，因为至少有现在这个最高次数减一存在
        cnt[x[v]]--;
        num[cnt[x[v]]]++;
    }
}
void solve() {
    for(int i=1;i<=m;i++) {
        while(L<Q[i].L) update(L++,-1);
        while(L>Q[i].L) update(--L,1);
        while(R<Q[i].R) update(++R,1);
        while(R>Q[i].R) update(R--,-1);
        ans[Q[i].id]=now;
    }
    for(int i=1;i<=m;i++) {
        printf("%d\n",ans[i]);
    }
}
int main() {
    init();
    build();
    solve();
    return 0;
}