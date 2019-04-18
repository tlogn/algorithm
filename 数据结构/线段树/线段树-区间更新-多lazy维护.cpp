/*
线段树——区间更新
维护多个lazy
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <iostream>
using namespace std;

const long long MAXN = 1e6+5;

class SegmentTree {
public:
	SegmentTree() {
        for(long long i=0;i<MAXN*4;i++)   lazy[1][i]=1;
    }
	~SegmentTree() {};
	void readin();
private:
	void build_tree(long long v,long long left,long long right);
	void update(long long v,long long left,long long right,long long goal_left,long long goal_right,long long value,long long type);
	long long query(long long v,long long left,long long right,long long goal_left,long long goal_right);
	void pushdown(long long v,long long left,long long right);

	long long n,m;
	long long x[MAXN];
	long long tree[MAXN*4],lazy[2][MAXN*4],mod;
};

void SegmentTree::pushdown(long long v,long long left,long long right) {
	if(lazy[0][v] || lazy[1][v]!=1) {
        long long mid=(left+right)>>1;
	    tree[v<<1]=((tree[v<<1]*lazy[1][v])%mod+(lazy[0][v]*(mid-left+1)%mod))%mod;	// 此处必须将左右儿子更新，因为pushup会用到左右儿子的值
	    tree[v<<1|1]=((tree[v<<1|1]*lazy[1][v])%mod+(lazy[0][v]*(right-mid))%mod)%mod;
        // 乘会影响加，所以代表加的lazy[0]会乘以lazy[1]
	    lazy[0][v<<1]=((lazy[0][v<<1]*lazy[1][v])%mod+lazy[0][v])%mod;
	    lazy[0][v<<1|1]=((lazy[0][v<<1|1]*lazy[1][v])%mod+lazy[0][v])%mod;
        
        lazy[1][v<<1]=(lazy[1][v<<1]*lazy[1][v])%mod;
        lazy[1][v<<1|1]=(lazy[1][v<<1|1]*lazy[1][v])%mod;
        lazy[1][v]=1;
	    lazy[0][v]=0;
    }
}

// [left,right]区间和
long long SegmentTree::query(long long v,long long left,long long right,long long goal_left,long long goal_right) {
	long long mid=(left+right)>>1;
	long long ret=0;
	pushdown(v,left,right);
	if(goal_left<=left && right<=goal_right)	return tree[v]%mod;
	if(mid>=goal_left)	ret=(ret+query(v<<1,left,mid,goal_left,goal_right))%mod;
	if(mid<goal_right)	ret=(ret+query(v<<1|1,mid+1,right,goal_left,goal_right))%mod;
	return ret%mod;
}

// [left,right]每个值加value
void SegmentTree::update(long long v,long long left,long long right,long long goal_left,long long goal_right,long long value,long long type) {
	pushdown(v,left,right);	
    if(goal_left<=left && right<=goal_right) {
        if(type==0) {
            tree[v]=(tree[v]+((long long)(right-left+1)*value)%mod)%mod;
            lazy[0][v]=(lazy[0][v]+value)%mod;
        }
        else {
            tree[v]=(tree[v]*value)%mod;
            lazy[0][v]=(lazy[0][v]*value)%mod;
            lazy[1][v]=(lazy[1][v]*value)%mod;
        }
        return;
    }
	long long mid=(left+right)>>1;
	if(mid>=goal_left)	update(v<<1,left,mid,goal_left,goal_right,value,type);    
	if(mid<goal_right)	update(v<<1|1,mid+1,right,goal_left,goal_right,value,type);
	tree[v]=(tree[v<<1]+tree[v<<1|1])%mod;
}

void SegmentTree::build_tree(long long v,long long left,long long right) {
	if(left==right)	{tree[v]=x[left]%mod;return;}
	long long mid=(left+right)>>1;
	build_tree(v<<1,left,mid);
	build_tree(v<<1|1,mid+1,right);
	tree[v]=(tree[v<<1]+tree[v<<1|1])%mod;
}

void SegmentTree::readin() {
	scanf("%lld%lld%lld",&n,&m,&mod);
	for(long long i=1;i<=n;i++) scanf("%lld",&x[i]);
	build_tree(1,1,n);
	for(long long t1,t2,t3,i=1;i<=m;i++) {
		long long t4;
        scanf("%lld",&t1);
		if(t1==2) {
			scanf("%lld%lld%lld",&t2,&t3,&t4);
			update(1,1,n,t2,t3,t4%mod,0);
		}
        else if(t1==1) {
            scanf("%lld%lld%lld",&t2,&t3,&t4);
			update(1,1,n,t2,t3,t4%mod,1);
        }
		else {
			scanf("%lld%lld",&t2,&t3);
			printf("%lld\n",query(1,1,n,t2,t3));
		}
	}
}

SegmentTree s;

int main(){
	s.readin();
    return 0;
}