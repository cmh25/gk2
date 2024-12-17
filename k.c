#include "k.h"
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include "x.h"
#include "scope.h"
#include "zv.h"
#include "fn.h"
#include "sym.h"

void kfree(U x){
  if(zv(x))zvfree(x);
  else if(ax) return;
  k_(0,x);
}
U kref(U x){
  if(zv(x)) return zvref(x);
  else if(ax) return x;
  return k_(1,x);
}
void* px(U x){return(void*)k_(2,x);}

void kinit(void) {
  k_(0,0);
  scope_init();
}

static int ffix(char *ds, int a0) {
  if(strchr(ds,'.')||strchr(ds,'e')) return 0;
  if(!strcmp(ds,"inf")) { sprintf(ds,"0i"); return 0; }
  if(!strcmp(ds,"nan")) { sprintf(ds,"0n"); return 0; }
  if(!strcmp(ds,"-inf")) { sprintf(ds,"-0i"); return 0; }
  return a0;
}

static void pi_(int i, char *c) {
  if(i==INT_MAX) printf("0I%s",c);
  else if(i==INT_MIN) printf("0N%s",c);
  else if(i==INT_MIN+1) printf("-0I%s",c);
  else printf("%d%s",i,c);
}
static void pi(U x, char *c) {
  pi_((int)x,c);
}
static void pia(U x, char *c) {
  int *pxi=(int*)px(x);
  if(!nx) printf("!0\n");
  else if(1==nx) { printf(","); pi_(pxi[0],c); }
  else i(nx,pi_(pxi[i],i<nx-1?" ":c))
}

static void pf_(float f, char *c) {
  char ds[256];
  if(isinf(f)&&f>0.0) printf("0i%s",c);
  else if(isnan(f)) printf("0n%s",c);
  else if(isinf(f)&&f<0.0) printf("-0i%s",c);
  else {
    sprintf(ds,"%0.*g",7,f);
    if(!strchr(ds,'.')&&!strchr(ds,'e')) strcat(ds, ".0");
    printf("%s%s",ds,c);
  }
}
static void pf(U x, char *c) {
  int i=(int)x;
  pf_(*(float*)&i,c);
}
static void pfa(U x, char *c) {
  int i,a0=1,m=mx?nx/mx:nx;
  char ds[256];
  float f,*pxf=(float*)px(x);
  if(!nx) printf("0#0.0%s",c);
  else if(1==nx) { printf(","); pf_(pxf[0],c); }
  else {
    for(i=0;i<nx;i++) {
      f=pxf[i];
      if(isinf(f)&&f>0.0) { sprintf(ds,"0i"); a0=0; }
      else if(isnan(f)) { sprintf(ds,"0n"); a0=0; }
      else if(isinf(f)&&f<0.0) { sprintf(ds,"-0i"); a0=0; }
      else { sprintf(ds,"%0.*g",7,f); a0=ffix(ds,a0); }
      if(m&&!((i+1)%m)) {
        if(a0) strcat(ds,".0");
        printf("%s%s",ds,i<nx-1?"\n":c);
      }
      else printf("%s ",ds);
    }
  }
}

void kprint(U x, char *s, char *e) {
  U *pxu,v;
  fn *f;
  switch(tx) {
  case 3: pi(x,e); break;
  case 4: pf(x,e); break;
  case 0xb: pia(x,e); break;
  case 0xc: pfa(x,e); break;
  case 8:
    pxu=(U*)px(x);
    printf("(");
    i(nx,kprint(pxu[i],s,i<nx-1?";":""))
    printf(")%s",e);
    break;
  default:
    if(zv(x)) {
      v=zvget(x);
      if(0xe==zx(v))  fprintf(stderr,"%s%s",(char*)(b(56)&v),e);
      else if(0xd==zx(v))  printf("%c%s",(char)v,e);
      else if(0xc==zx(v)) { f=(fn*)(b(56)&v); printf("%s\n",f->d); }
    }
    break;
  }
  kfree(x);
}

U kerror(char *e) {
  return zvset((U)sp(e),0xe);
}

U knorm(U x) {
  U r=x,*pxu;
  int t,*pri;
  float *prf;
  if(tx==8&&nx) {
    pxu=(U*)px(x);
    t=pxu[0]>>60;
    i(nx,if(t!=pxu[i]>>60) return r)
    switch(t) {
    case 3: r=tn(3,nx); pri=(int*)px(r); i(nx,pri[i]=(int)pxu[i]); kfree(x); break;
    case 4: r=tn(4,nx); prf=(float*)px(r); i(nx,prf[i]=fu(pxu[i])) ; kfree(x);break;
    }
  }
  return r;
}
