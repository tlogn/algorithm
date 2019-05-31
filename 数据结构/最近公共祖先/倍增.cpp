#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <iostream>
#include <vector>
using namespace std;
const int MAXN = 1e5+5;
struct node{
    int to;
    long long dis;
};
vector<node>g[MAXN];
int n,m,depth[MAXN],fa[MAXN][40],w[MAXN][40];
bool vis[MAXN];
void dfs(int v,int d) {
    vis[v]=true;
    depth[v]=d;
    for(int i=g[v].size()-1;i>=0;i--) {
        if(!vis[g[v][i].to]) {
            fa[g[v][i].to][0]=v;
            w[g[v][i].to][0]=g[v][i].dis;
            dfs(g[v][i].to,d+1);
        }
    }
}
int lca(int v,int u) {
    int ret=0x7fffffff;
    if(depth[v]>depth[u])   swap(v,u);
    for(int j=30;j>=0;j--) {             // 调整到同一高度
        if(depth[fa[u][j]]>=depth[v]) {
            ret=min(ret,w[u][j]);
            u=fa[u][j];
        }   
    }
    if(u==v)    return ret;
    for(int j=30;j>=0;j--) {
        if(fa[v][j]!=fa[u][j]) {
            ret=min(ret,w[v][j]);
            ret=min(ret,w[u][j]);
            v=fa[v][j];
            u=fa[u][j];
        }
    }
    ret=min(ret,min(w[v][0],w[u][0]));
    return ret;
}
int main(){
    memset(vis,false,sizeof(vis));
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n;i++)
        for(int j=0;j<=30;j++)  
            w[i][j]=0x7fffffff;
    for(int t1,t2,t3,i=1;i<n;i++) {
        scanf("%d%d%d",&t1,&t2,&t3);
        g[t1].push_back((node){t2,t3});
        g[t2].push_back((node){t1,t3});
    }
    dfs(1,1);
    for(int j=1;j<=30;j++) {
        for(int i=1;i<=n;i++) {
            fa[i][j]=fa[fa[i][j-1]][j-1];
            if(fa[i][j])    w[i][j]=min(w[i][j-1],w[fa[i][j-1]][j-1]);
        }
    }
    for(int t1,t2,i=1;i<=m;i++) {
        scanf("%d%d",&t1,&t2);
        printf("%d\n",lca(t1,t2));
    }
    return 0;
}