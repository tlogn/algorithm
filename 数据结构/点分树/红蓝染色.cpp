#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;
const int MAXN = 1e5+5;
const int INF = 0x7ffffff;
int n,m,root,sz[MAXN],nowsz,rootsz=INF,fa[MAXN],minn[MAXN];
bool vis[MAXN],isred[MAXN];

int head[MAXN*2],edtot=0;
inline int read() {
    int X=0; char c=getchar();
    while (c<'0'||c>'9') { c=getchar(); }
    while (c>='0'&&c<='9') X=(X<<3)+(X<<1)+c-'0',c=getchar();
    return X;
}
struct edge{
    int pos,nxt;
}e[MAXN*2];
void add_edge(int v,int u) {      // 添加一条从v到u，权重为w的边
    e[++edtot].pos=u;
    e[edtot].nxt=head[v];
    head[v]=edtot;
}
// 欧拉序列 ＲＭＱ求ＬＣＡ
int depth[MAXN*2],fir[MAXN*2],ver[MAXN*2],cnt=0;
int st[MAXN*2][25];
void dfs_lca(int v,int d) {
    ver[++cnt]=v;
    depth[cnt]=d;
    fir[v]=cnt;
    for(int i=head[v];i;i=e[i].nxt) {
        if(!fir[e[i].pos]) {
            dfs_lca(e[i].pos,d+1);
            ver[++cnt]=v;
            depth[cnt]=d;
        }
    }
}
void init_lca() {
    dfs_lca(1,1);
    for(int i=1;i<=cnt;i++) {   // 处理ＳＴ表
        st[i][0]=depth[i];
    }
    for(int j=1;j<=20;j++) {
        for(int i=1;i+(1<<j)-1<=cnt;i++) {
            st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
        }
    }
}
int dis(int v,int u) {
    v=fir[v];
    u=fir[u];
    if(v>u) swap(v,u);
    int temp=log2(u-v+1);
    int ret=min(st[v][temp],st[u-(1<<temp)+1][temp]);
    return depth[v]+depth[u]-2*ret;
}

// 点分树
void GetRoot(int v,int father) {
    sz[v]=1;
    int maxn=0;
    for(int i=head[v];i;i=e[i].nxt) {
        if(vis[e[i].pos] || e[i].pos==father) continue;
        GetRoot(e[i].pos,v);
        sz[v]+=sz[e[i].pos];
        maxn=max(maxn,sz[e[i].pos]);
    }
    maxn=max(maxn,nowsz-sz[v]);
    if(rootsz>maxn) {
        root=v;
        rootsz=maxn;
    }
}
void build(int v,int father) {
    fa[v]=father;
    vis[v]=true;
    int temp=nowsz;           // 下面for的时候nowsz会变，先保存
    for(int i=head[v];i;i=e[i].nxt) {
        if(vis[e[i].pos] || father==e[i].pos)    continue;
        // 正确地找到子树的大小，之前遍历的sz和子树的sz可能不同
        if(sz[e[i].pos]>sz[v])   nowsz=temp-sz[v]; 
        else    nowsz=sz[e[i].pos];
        rootsz=INF;              // 求子树重心前初始化
        GetRoot(e[i].pos,v);         // 求子树的重心
        build(root,v);              // 连接重心构成点分树
    }
}
void init() {
    n=read();
    m=read();
    for(int i=1;i<=n;i++)   minn[i]=INF;
    for(int t1,t2,i=1;i<n;i++) {
        t1=read();
        t2=read();
        add_edge(t1,t2);
        add_edge(t2,t1);
    }
    nowsz=n;
    GetRoot(1,0);
    build(root,0);

}
void update(int v) {
    int temp=v;
    while(temp) {
        minn[temp]=min(minn[temp],dis(temp,v));
        temp=fa[temp];
    }
}
int query(int v) {
    int ret=minn[v],temp=v;
    while(temp) {
        ret=min(minn[temp]+dis(temp,v),ret);
        temp=fa[temp];
    }
    return ret;
}

int main() {
    init();
    init_lca();
    update(1);
    isred[1]=true;
    for(int t1,t2,i=1;i<=m;i++) {
        t1=read();
        t2=read();
        if(t1==1) {
            if(isred[t2])    continue;
            else    isred[t2]=true,update(t2);
        }
        else {
            printf("%d\n",query(t2));
        }
    }
    return 0;

}