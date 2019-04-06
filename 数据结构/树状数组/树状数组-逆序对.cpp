#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

#define MAXN 500005

struct node {
	int value,pos;
	bool operator < (const node &w) const {
		return value < w.value;
	}
}g[MAXN];

int n,x[MAXN];
long long ans=0,tree[MAXN];

int lowbit(int id) {	
	return id&(-id);
}

void update(int id,int value) {	// 更新单点
	for(int i=id;i<=n;i+=lowbit(i)) {
		tree[i]+=value;
	}
}

long long sum(int id) {		// 查询1~id的前缀和
	long long ret=0;
	for(int i=id;i;i-=lowbit(i)) {
		ret=ret+tree[i];
	}
	return ret;
}

long long query(int id1,int id2) {	// 通过前缀和相减得到id1~id2的区间和
	return sum(id2)-sum(id1-1);
}

void readin() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		scanf("%d",&g[i].value);
		g[i].pos=i;
	}
}
int main() {
	readin();

	// 离散化
	std::sort(g+1,g+1+n);
	x[g[1].pos]=1;
	for(int j=1,i=2;i<=n;i++)	{
		if(g[i].value > g[i-1].value)	j++;
		x[g[i].pos]=j;
	}
	
	// 求逆序对数，因为按顺序加入到树状数组，所以在后面的数的数量就是与这个元素相关的逆序对数
	for(int i=1;i<=n;i++) {
		update(x[i],1);
		ans=ans+query(x[i]+1,n);
	}

	printf("%lld\n",ans);
	return 0;
}