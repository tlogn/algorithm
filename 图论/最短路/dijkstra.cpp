#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <queue>

#define MAXN (100000+5)                     // 点数
#define MAXM (200000+5)                     // 边数

class Edge{                                 //  链式前向星
public:
    Edge()  {tot=0;}
    int tot,head[MAXM];
    struct edge{
        int pos,dis,next;
        edge() {next=0;}
    }E[MAXM];
    void add_edge(int v,int u,int w) {      // 添加一条从v到u，权重为w的边
        tot++;
        E[tot].dis=w;
        E[tot].pos=u;
        E[tot].next=head[v];
        head[v]=tot;
    }
};

class Dijkstra : Edge {                     // 以前向星为基础建图
public:
    
    void readin();
    void work();
    void print_dis();
    void clear();
    
private:
    
    int n,m,start,d[MAXN];
    bool vis[MAXN];
    
    struct node{
        int pos,dis;
        bool operator < (const node &w) const {
            return dis > w.dis;
        }
    };
    std::priority_queue<node>q;
    void init();
};

void Dijkstra::print_dis() {
    for(int i=1;i<=n;i++) printf("%d ",d[i]);
}

void Dijkstra::clear() {
    tot=0;
    for(int i=1;i<=m;i++) E[i].next=0;
    while(!q.empty())   q.pop();
}

void Dijkstra::init() {
    for(int i=1;i<=n;i++)   d[i]=(0x7fffffff>>1);
    memset(vis,false,sizeof(vis));
}

void Dijkstra::readin() {
    scanf("%d%d%d",&n,&m,&start);
    for(int t1,t2,t3,i=1;i<=m;i++) {
        scanf("%d%d%d",&t1,&t2,&t3);
        add_edge(t1,t2,t3);
    }
    init();
}

void Dijkstra::work() {
    d[start]=0;                         // 初始化起始点
    q.push((node){start,0});
    while(!q.empty()) {
        int pos=q.top().pos;
        q.pop();
        if(vis[pos])   continue;
        vis[pos]=true;
        for(int i=head[pos];i;i=E[i].next) {        // 遍历点pos所连接的所有边
            if(d[E[i].pos] > d[pos]+E[i].dis) {     // 松弛
                d[E[i].pos] = d[pos]+E[i].dis;
                if(!vis[E[i].pos])  q.push((node){E[i].pos,d[E[i].pos]});   // 成功松弛后，若该点未确定，加入队列
            }
        }
    }
}

Dijkstra s;

int main() {
    s.readin();
    s.work();
    s.print_dis();
    return 0;
}

