#define Zx (!tx&&29>mx)
#define _x(z) r(_(z),_r(x))
#define R(t,n,z) r(tz(t,n),z)
#define r(b,z) _(typeof(b)r=b;z;r)
#include"_.h"
#if __x86_64
#define S(f,i) AS(f,"mov %rcx,%r10;mov $"#i",%rax;syscall;",Ux,...)
#define o(f) __builtin_ia32_##f##512
AS(ut,"rdtsc;shl $32,%rdx;or %rdx,%rax;")UV(b_,o(cvtb2mask)(a))Vf(sq,o(sqrtps)(a,4))UV(b2,o(cvtd2mask)(a))
#else
#define S(f,i) AS(f,"mov x16,"#i"\nldr x1,[sp]\nldr x2,[sp,8]\nldr x3,[sp,16]\nmov x4,0\nmov x5,x4\nsvc 0\n",Ux,...)
#define o(f) __builtin_neon_v##f##q_v
AS(ut,"mrs x0,cntvct_el0\nmov x1,100\nmul x0,x0,x1\n")D(j4,b0,o(padd)(x,y,48),g4 x,g4 y)UV(b_,g4*y=&a;g4 m=1<<I4%8;x(b0(b0(m&y[0],m&y[1]),b0(m&y[2],m&y[3])),b0(x,x)[0]))
U(b4,g4*y=&a;g6 b;g6 c=I0;i(4,B4=o(qtbl4)(y[0],y[1],y[2],y[3],d*C4,48))b_(b),i0 d,Va)UV(b2,b4(4,a))UV(b3,b4(8,a))Vf(sq,i(4,A4=o(sqrt)(A4,41))a)
//#define V2(g,f,j) VF(g,i(4,A4=o(f)(A4,B4,j))a) V2(a4,qtbl1,48)Vf(ba,a4(a,BA))V2(LG,min,48)V2(MG,max,48)V2(LI,min,50)V2(MI,max,50)
//D(g4,p4,o(qtbl1)(a,b,48),g4 a,g4 b)_f(X9,__builtin_neon_vmull_p64(x,-1L))VF(GG,Vc={};i(4,asm("fcmla.4s %0,%1,%2,0\nfcmla.4s %0,%1,%2,90":"+w"(C4):"w"(A4),"w"(B4)))c)
#endif 


Z0 bt[]={6,0,3,5,5,0,0,6};extern U k(i2,U),K(i2,U,U);extern V _V[];extern i0 _J[];extern U _j[],w2();is(ic,bs(b_((i0)i==Vs)))_u(wc,w2(1,&i))Us(ws,w2(ic(0,s),s))
U(QQ,ws(d);wc(58);ws(s);wc(10);255,sd,ss)
_u(wi,r(i,in=i>>31;i=n?-i:i;Z0 a[21];ss=a+20;*s=10;do*--s=48+i%10;W(i/=10);if(n)*--s=45;w2(a+21-s,s)))
f(wu,Z0 a[17];a[16]=10;i(16,ij=15&x>>60-4*i;a[i]="0W"[9<j]+j)w2(17,a);x)
#define jx  (b(60)&x)
#define tx  (7&x>>60) 
#define bx (15&x>>56)
#define kx (63&x>>50)
#define mx (b(16)&x>>32)
#define nx (b(32)&x)
#define lx (nx/mx)
#define rx _J[1023&x>>50]
#define sx (i0*)(_V+(1+kx<<bx))
#define sr x(r,sx)
#define sa x(a,sx)
#define ox(i) (U)(sx+((int)i<<bt[tx]-3))
_U(tn,n--?m(6,br(n3(n<<bt[t])))-6:0,it,in)g(tz,ij=tn(i,nx);ik=bs(~_j[j]);_j[j]^=1L<<k;t(8+i,64L*j+k<<50|x))_F(mz,a<<32|x)


#define px (32>x) 
#define ax (8>x>>60)
#define N(z) i(nx,U*b=sx;x(b[i],z))
#define Nx n3(nx<<bt[tx])
#define ix (i2)x
#define Gx r(*(g6*)X,X+=64)
#define Ix r(*(i6*)X,X+=64)
#define Ex r(*(e6*)X,X+=64)
#define Ia r(*(i6*)A,A+=64)
#define QZ _(Qz(1)0)
#define Qv(b) P(b,wc(58);wc(c);wc(10);255)
#define Qs(b,s) P(b,QQ(__func__,s))

#if linux
S(_k,60)S(_w,0)S(w_,1)S(d_,2)S(_d,3)S(d7,4)Us(D7,Ua[24];!d7((U)s,a)&1&a[3]>>15?a[6]:0)
#else
S(_k,1)S(_w,3)S(w_,4)S(d_,5)S(_d,6)S(d7,338)Us(D7,Ua[24];!d7((U)s,a)&1&*a>>47?a[12]:0)
#endif
