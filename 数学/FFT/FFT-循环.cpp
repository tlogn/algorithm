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
int r[MAXN],limit,len;
complex a[MAXN],b[MAXN];
int n,m;
void FFT(complex *t,int type) {
    for(int i=0;i<limit;i++)
        if(i<r[i])  swap(t[i],t[r[i]]);
    for(int j=1;j<limit;j<<=1) {
        complex wn=(complex){cos(pi/j),type*sin(pi/j)};
        for(int i=0;i<limit;i+=(j<<1)) {
            complex w=(complex){1,0};
            for(int k=0;k<j;k++,w=wn*w) {
                complex x=t[i+k],y=w*t[i+j+k];
                t[i+k]=x+y;
                t[i+k+j]=x-y;
            }
        }
    }
}
int main(){
    cin>>n>>m;
    for(int i=0;i<=n;i++)	scanf("%lf",&a[i].x);
    for(int i=0;i<=m;i++)	scanf("%lf",&b[i].x);
    for(limit=1,len=0;limit<=n+m;limit<<=1,len++);
    for(int i=0;i<limit;i++) r[i]=(r[i>>1]>>1) | ((i&1)<<(len-1));
    FFT(a,1);
    FFT(b,1);
    for(int i=0;i<limit;i++)    a[i]=a[i]*b[i];   
    FFT(a,-1);
    for(int i=0;i<=n+m;i++) {
        printf("%d ",(int)(a[i].x/limit+0.5));
    }
    printf("\n");
    return 0;
}

