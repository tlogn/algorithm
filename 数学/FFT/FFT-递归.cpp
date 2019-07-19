#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <iostream>
using namespace std;
const int MAXN = 4e6+5;
const double pi = acos(-1.0);
struct complex {
    double x,y;
    complex operator * (const complex &w) {return (complex){x*w.x-y*w.y,x*w.y+y*w.x};}
    complex operator + (const complex &w) {return (complex){x+w.x,y+w.y};}
    complex operator - (const complex &w) {return (complex){x-w.x,y-w.y};}
    friend ostream & operator << (ostream &os,complex &w) {
        os<<w.x<<' '<<w.y<<' ';
        return os;
    }
};
complex a[MAXN],b[MAXN];
int n,m;
void FFT(complex *t,int limit,int type) {
    if(limit==1)	return;
    static complex tmp[MAXN];
    for(int i=0;i<limit;i+=2)	tmp[i>>1]=t[i],tmp[(i>>1)+(limit>>1)]=t[i+1];
    memcpy(t,tmp,sizeof(complex)*limit);
    FFT(t,limit>>1,type);
    FFT(t+(limit>>1),limit>>1,type);
    complex wn=(complex){cos(2.0*pi/limit),type*sin(2.0*pi/limit)},w=(complex){1,0};
    for(int i=0;i<(limit>>1);i++,w=wn*w) {
        tmp[i]=t[i]+w*t[i+(limit>>1)];
        tmp[i+(limit>>1)]=t[i]-w*t[i+(limit>>1)];
    }
    memcpy(t,tmp,sizeof(complex)*limit);
}
int main(){
    cin>>n>>m;
    for(int i=0;i<=n;i++)	scanf("%lf",&a[i].x);
    for(int i=0;i<=m;i++)	scanf("%lf",&b[i].x);
    int limit;
    for(limit=1;limit<=n+m;limit<<=1);
    FFT(a,limit,1);
    FFT(b,limit,1);
    for(int i=0;i<=limit;i++)	a[i]=a[i]*b[i];
    FFT(a,limit,-1);
    for(int i=0;i<=n+m;i++) {
        printf("%d ",(int)(a[i].x/limit+0.5));
    }
    printf("\n");
    return 0;
}

