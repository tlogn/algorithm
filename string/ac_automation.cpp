#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <cstdlib>

#define MAXN ((int)1e6+5)

using namespace std;
class Trie_Tree {       // 构建字典树
public:
    Trie_Tree() {memset(end,0,sizeof(end));memset(tree,0,sizeof(tree));tot=0;}
    void insert(char *st);
    bool find(char *st);
protected:
    int tot,tree[MAXN][26];
    int end[MAXN];
};
bool Trie_Tree::find(char *st) {        // 字典树的查找功能
    int p=0;
    for(int i=0;st[i];i++) {
        int k=st[i]-'a';
        if(!tree[p][k]) return false;
        p=tree[p][k];
    }
    if(end[p])  return true;
    return false;
}
void Trie_Tree::insert(char *st) {      // 插入字符串
    int p=0;
    for(int i=0;st[i];i++) {
        int temp=st[i]-'a';
        if(!tree[p][temp]) tree[p][temp]=++tot;
        p=tree[p][temp];
    }
    end[p]++;                           // 记录子串出现的次数
}
class AC : public Trie_Tree {           // AC自动机，继承字典树
public:
    AC() {memset(fail,0,sizeof(fail));}
    void build_fail();
    int query(char *st);
private:
    int fail[MAXN];
};
void AC::build_fail() {
    queue<int>q;
    for(int i=0;i<26;i++)   if(tree[0][i])  q.push(tree[0][i]); // 若直接将根结点入队，则tree
    while(!q.empty()) {
        int now=q.front();      // 当前结点
        q.pop();
        for(int i=0;i<26;i++) {
            if(tree[now][i]) {          // 如果当前结点连向当前字符，则跳转到当前的fail结点连接到的当前字符
                int to=tree[now][i];
                fail[to]=tree[fail[now]][i];
                q.push(to);
            }
            else tree[now][i]=tree[fail[now]][i];
            // 若为空字符，则路径压缩，将不存在的tree[now][i]指向fail结点
        }
    }
}
int AC::query(char *st) {           // 查询所有子串出现的次数之和
    int ret=0,p=0;
    for(int i=0;st[i];i++) {
        p=tree[p][st[i]-'a'];
        for(int j=p;j && end[j];j=fail[j]) {
            ret+=end[j];
            end[j]=0;
        }
    }
    return ret;
}
AC ac;
int n;
char s[MAXN];
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        scanf("%s",s);
        ac.insert(s);
    }
    ac.build_fail();
    scanf("%s",s);
    printf("%d\n",ac.query(s));
    return 0;
}
