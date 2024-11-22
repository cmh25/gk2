#include"_.h"
Z0*L=__DATE__"(c)arthur whitney(l)MIT",*P=":+-*%&|<>=~.!@?#_^,$LMSA..ERZ'/\\;()",B=32,s[256];Ze C[]={1,10,1e2,1e3,1e4,1e5,1e6,1e7,1e8,1e9};
#define AS(f,s,x...) ZU __attribute((naked))f(x){asm(s"ret");}
#if __x86_64
#define O(f,i) AS(f,"mov %rcx,%r10;mov $"#i",%rax;syscall;",Ux,...)
AS(ut,"rdtsc;shl $32,%rdx;or %rdx,%rax;")UV(bg,B(ia32_cvtb2mask512)(a))
#else
#define O(f,i) AS(f,"mov x16,"#i"\nldr x1,[sp]\nldr x2,[sp,8]\nldr x3,[sp,16]\nmov x4,0\nmov x5,x4\nsvc 0\n",Ux,...)
AS(ut,"mrs x0,cntvct_el0\nmov x1,100\nmul x0,x0,x1\n")
#endif
#if linux
O(_w,0)O(w_,1)O(_d,3)O(d_,2)O(_n,5)_u(nd,Ua[24];!_n(i,a)&1&a[3]>>15?a[6]:0)
#else
O(_w,3)O(w_,4)O(_d,6)O(d_,5)O(_n,189)_u(nd,Ua[24];!_n(i,a)&1&*a>>47?a[12]:0)
#endif
#define s(g,z) D(U,g,z,ss)
#define is(g,z) D(U,g,z,ii,ss)
#define ins(g,z) D(U,g,z,ii,in,ss)
#define cc i0 c
#define sd i0*d
#define ss i0*s
#define Vs *(V*)s

UV(ib,iu(~bg(a)))is(ic,ib((i0)i!=Vs))is(i$,48>*s?(i2)-i$(i-1,s+1):r(0,i(i,r=10*r+s[i]-48)))is(n$,(8>i?b(8*i):-1)&*(U*)s)Vf(d0,46==a|10>a-48)Vf(d1,1>I0|B==a|101==a)
is(w2,w_(2,s,i))is(w1,w2(i,s);wc(10);0)s(ws,w1(ic(0,s),s))_u(wl,w1(i,s))f(wb,i(64,s[i]=48|1&x>>i)wl(64);x)f(wu,i(16,ij=15&x>>60-4*i;s[i]="0W"[9<j]+j)wl(16);x)
ZU*A,_[32],G[32],E(U),wx(U),ls(ss),es(ii,ss),ps(ii,ss),w(ii,ss),e(ii,ss);_U(y,Vs=*(V*)d;w(ic(0,s),s),sd)
#define Qs(b) P(b,ws(s);0)
#define _X(z) r(_(z),_z(x))
#define _A(z) r(_(z),_z(a))
#define R0(n,z) r(tn(0,n),j(nr,rU[j]=_(z)))
#define R2(n,z) r(tn(t,n),j(nr,r2[j]=_(z)))
#define sx ((i0*)k(0,x,0))
#define Q(z) r(z,P(!r,0))
#define Zx (px|tx?0:_(Ua=*xU;ta?0:x(*aU,2==tx))) //(s..;..)
