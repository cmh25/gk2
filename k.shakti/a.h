#define H(z)      _x(r(tn(0,mn),       U*R=sr;       j(mn,R_=_(z))))
#define H2(z)     _x(r(tn(2,nx),      i0*R=sr;       j(nx,R_=_(z))))
#define H3(z)     _x(r(tn(3,nx),      i2*R=sr;       j(nx,R_=_(z))))
#define I(z)       r(uz(x),            U*R=sr;U*X=sx;J(nx,R_=_(z)))
#define V(z)       r(uz(x),            V*R=sr;V*X=sx;J(Nx,R_=_(z)))
#define _V(t,b,z) _x(r(mtn(mx,t   ,nx),b*R=sr;V*X=sx;J(Nx,R_=_(z))))
#define V_(  b,z) _x(r(mtn(mx,1+tx,nx),V*R=sr;b*X=sx;J(Nr,R_=_(z))))
#define mn (mx?:nx)
#define C(t,z) B(convertvector)(z,t)
#define h(b,z) {i2 $=b;ih=0;W(h<$){z;++h;}}
#define sx ((i0*)(0x7fffffffffc0&rx))
#include"_.h"//to[mn] 4/12/48 //xV[Nx>>6]|=(i0)(Nx%64)<=I0 
#define o(f) B(ia32_##f##512) //_U(c2,B(ia32_compressstoresi512_mask)(s,a,n);nu(n),ss,in,Va)UV(bj,o(cvtq2mask)(a))Vf(pc,o(vpopcntq_)(a))
#define V2(g,f) VF(g,o(f)(a,b))
VE(_q,o(sqrtps)(x,4))UV(bg,o(cvtb2mask)(a))UV(bi,o(cvtd2mask)(a))V2(a4,pshufb)V2(A0,permvarqi)V2(A2,permvarsi)
Vg(S6,2>i?o(vpermi2varqi)(z0,i?62+I0:63+I0,a):$4(i-2,o(alignd)(a,z0,15),o(alignd)(a,z0,14),o(alignd)(a,z0,12),o(alignd)(a,z0,8)))
_F(X9,-a^B(ia32_pclmulqdq128)((j4){x},~(j4){},0)[0])
#if 14>__clang_major__
V2(LG,pminub)V2(LI,pminud)V2(MG,pmaxub)V2(MI,pmaxud)
#else
VF(LG,B(elementwise_min)(a,b))VF(LI,B(elementwise_min)((i6)a,(i6)b))VF(MG,B(elementwise_max)(a,b))VF(MI,B(elementwise_max)((i6)a,(i6)b))
#endif
g(mz,(U)i<<32|~(b(16)<<32)&x)inx(mtn,mz(i,tn(n,x)))_i(tb,t(1,i))_U(te,t(4,*(i2*)&e),ee)
#define J(n,z) j(n6(n),z)
#define X_ *X++
#define R_ *R++
VF(SG,a+b)VF(SI,(i6)a+b)VF(SE,(e6)a+b)j6 P,Q={0xc6a4a7935bd1e995};_D(j6,PQ,Q^=P;P=(P<<55|P>>9)^Q^Q<<14;Q=Q<<37|Q>>27;P+Q)F(Q0,0)f(q0,0)_U(ds,J(n,R_=X_)n,in,VR,VX)
#define ra O[4095&a>>48]
#define rx O[4095&x>>48]
#define Nx n3(nx<<bx) 
#define bx B[tx]
#define X_ *X++
#define R_ *R++
#define Nx n3(nx<<bx) 
#define AZ *A++
#define Ix ((i6)X_)
#define Ex ((e6)X_)
#define ex (4>tx?(int)ix:ei(ix))
#define jx (b(60)&x)
#define ER e6*R
#define EA e6*A
#define EX e6*X
#define Eb e6 b
#define Ez e6 z
#define eX e2*X
#define eA e2*A
#define eR e2*R
#define QR Qr(ax)
#define Qz(b) P(b,0)
#define Qr(b) P(b,1)
#define Qn(b) P(b,2)
#define Qt(b) P(b,3)
