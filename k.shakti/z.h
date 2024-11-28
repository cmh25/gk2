#define U(z) r(z,P(!r,0))
#include"_.h"
#define AS(f,s,x...) ZU __attribute((naked))f(x){asm(s"ret");}
#if __x86_64
Vf(s0,B(ia32_vpermi2varqi512)(z0,63+I0,a))
#define O(f,i) AS(f,"mov %rcx,%r10;mov $"#i",%rax;syscall;",Ux,...)
AS(ut,"rdtsc;shl $32,%rdx;or %rdx,%rax;")
#else
#define O(f,i) AS(f,"mov x16,"#i"\nldr x1,[sp]\nldr x2,[sp,8]\nldr x3,[sp,16]\nmov x4,0\nmov x5,x4\nsvc 0\n",Ux,...)
AS(ut,"mrs x0,cntvct_el0\nmov x1,100\nmul x0,x0,x1\n")
#endif
#if linux
Z2 O;O(_k,60)O(_w,0)O(w_,1)O(_n,4)O(_d,3)O(d_,2)O(m_,9)O(_m,11)
#else
Z2 O=1;O(_k,1)O(_w,3)O(w_,4)O(_n,188)O(_d,6)O(d_,5)O(m_,197)O(_m,73)
#endif
#define E(g,z) _U(g,ss=*_;z;*_=s;x,i0**_)
#define mn (ma?:na)
#define cb char b
#define sd i0*d
#define ss i0*s
#define Vs *(V*)s
#define _s(g,z) D(U,g,z,ss)
#define is(g,z) D(U,g,z,ii,ss) //m_(a?:A,x,3,i?0x12:O?0x1042:0x4022,i,0)
U_(w2,w_(2,(U)s,i);0,ii,ss)is(w0,w2(i,s);wc(10))f(wb,cb[64];i(64,b[i]=48|1&x>>i)w0(64,b);x)f(wu,cb[16];i(16,ij=15&x>>60-4*i;b[i]="0W"[9<j]+j)w0(16,b);x)
//Uu=0x8080808080808080;exp(0x102040810204080*(x&0x7f)|u&x<<56)>>7 cmp i(8,u|=0x2040810204081*(u&a[i])>>56<<8*i)
UV(bg,B(ia32_cvtb2mask512)(a))
is(i$,48>*s?(i2)-i$(i-1,s+1):r(0,i(i,r=10*r+s[i]-48)))is(ic,sd=s;W(i!=*s)++s;s-d)
_s(ws,w0(ic(0,s),s))
_s(fs,Ua[24];!_n((U)s,a)&&1&a[O?0:3]>>(O?47:15)?a[O?12:6]:0)is(ms,ij=d_((U)s,0);Ux=m_(0,i,1,2,j,0);_d(j);x)
extern U k(ii,U,U);f(r_,ax?x:k(0,0,x))f(_r,ax?x:k(15,0,x))g(a_,k(13,r_(x),ti(i)))
Z0*L=__DATE__"(c)arthur whitney(l)MIT",*P=":+-*%&|<>=~.!@?#_^,$LMSA..ERZ'/\\;()",B=32,b[256];_i(wl,w0(i,b))
#define sx ((i0*)k(0,x,0))
#define ins(g,z) D(U,g,z,ii,in,ss)
is(ns,R(2,i,*rV=Vs))f(_v,k(13,0,x))ins(nc,nu(b(i)&bg((i0)n==Vs)))
Z2 I[]={1,10,1e2,1e3,1e4,1e5,1e6,1e7,1e8,1e9};_i(li,r(0,W(i>=I[++r])))
UV(ib,iu(~bg(a)))is(id,ib((i0)i!=Vs))ZU ls(ss),qs(ii,ss),p(ii,ss),w(ii,ss),wx(U),q(ii),e(i0**);_s(y,Vb=Vs;w(ic(0,s),&b))
_i(o,3>i-61)_i(v,33>i-B)
Z0*t,_[2][64];ZU*A,h,C[2][8],G[32];_i(vf,P(!i--,k(0,0,0))ss=b;j(26,Ux=G[j+1];*s=97+j;s+=x&&!i^px)ns(s-b,b))_f(_p,j(8,_r(C[0][j]))*(V*)C=z0;x)
Vf(d0,46==a|10>a-48)Vf(d1,1>I0|32==a|101==a)
