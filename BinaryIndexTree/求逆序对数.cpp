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

void update(int id,int value) {	// ���µ���
	for(int i=id;i<=n;i+=lowbit(i)) {
		tree[i]+=value;
	}
}

long long sum(int id) {		// ��ѯ1~id��ǰ׺��
	long long ret=0;
	for(int i=id;i;i-=lowbit(i)) {
		ret=ret+tree[i];
	}
	return ret;
}

long long query(int id1,int id2) {	// ͨ��ǰ׺������õ�id1~id2�������
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

	// ��ɢ��
	std::sort(g+1,g+1+n);
	x[g[1].pos]=1;
	for(int j=1,i=2;i<=n;i++)	{
		if(g[i].value > g[i-1].value)	j++;
		x[g[i].pos]=j;
	}
	
	// �������������Ϊ��˳����뵽��״���飬�����ں���������������������Ԫ����ص��������
	for(int i=1;i<=n;i++) {
		update(x[i],1);
		ans=ans+query(x[i]+1,n);
	}

	printf("%lld\n",ans);
	return 0;
}