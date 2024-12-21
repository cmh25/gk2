#include "k.h"
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "x.h"
#include "scope.h"
#include "zv.h"
#include "fn.h"
#include "sym.h"

void kfree(U x){
  if(zv(x))zvfree(x);
  else if(ax) return;
  else k_(0,x);
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

static void pc_(char c) {
  if((c<32||c>126)) {
    if(c==8) printf("\\b");
    else if(c==9) printf("\\t");
    else if(c==10) printf("\\n");
    else if(c==13) printf("\\r");
    else printf("\\%03o",c);
  }
  else {
    if(c==34) printf("\\\"");
    else if(c==92) printf("\\\\");
    else printf("%c",c);
  }
}
static void pc(U x, char *s, char *e) {
  printf("%s\"",s); pc_((char)x); printf("\"%s",e);
}
static void pca(U x, char *s, char *e) {
  char *pxc=(char*)px(x);
  if(nx==1) printf("%s,\"",s);
  else printf("%s\"",s);
  i(nx,pc_(pxc[i]))
  printf("\"%s",e);
}
static void pi_(int i) {
  if(i==INT_MAX) printf("0I");
  else if(i==INT_MIN) printf("0N");
  else if(i==INT_MIN+1) printf("-0I");
  else printf("%d",i);
}
static void pi(U x, char *s, char *e) {
  printf("%s",s); pi_((int)x); printf("%s",e);
}
static void pia(U x, char *s, char *e) {
  int *pxi=(int*)px(x);
  if(!nx) printf("%s!0%s",s,e);
  else if(1==nx) { printf("%s,",s); pi_(pxi[0]); printf("%s",e); }
  else i(nx,pi(pxi[i],i?"":s,i<nx-1?" ":e))
}

static void pf_(float f) {
  char ds[256];
  if(isinf(f)&&f>0.0) printf("0i");
  else if(isnan(f)) printf("0n");
  else if(isinf(f)&&f<0.0) printf("-0i");
  else {
    sprintf(ds,"%0.*g",7,f);
    if(!strchr(ds,'.')&&!strchr(ds,'e')) strcat(ds, ".0");
    printf("%s",ds);
  }
}
static void pf(U x, char *s, char *e) {
  int i=(int)x;
  printf("%s",s); pf_(*(float*)&i); printf("%s",e);
}
static void pfm(U x, char *s, char *e, char *s0) {
  int i,a0=1,m=mx?nx/mx:nx;
  char ds[256];
  float f,*pxf=(float*)px(x);
  char s2[256];
  sprintf(s2,"%s ",s0);
  if(!nx) printf("%s[0#0.0]%s",s,e);
  else if(1==nx) { printf("%s[,",s); pf_(pxf[0]); printf("]%s",e); }
  else {
    printf("%s[",s);
    for(i=0;i<nx;i++) {
      f=pxf[i];
      if(isinf(f)&&f>0.0) { sprintf(ds,"0i"); a0=0; }
      else if(isnan(f)) { sprintf(ds,"0n"); a0=0; }
      else if(isinf(f)&&f<0.0) { sprintf(ds,"-0i"); a0=0; }
      else { sprintf(ds,"%0.*g",7,f); a0=ffix(ds,a0); }
      if(!((i+1)%m)) {
        if(a0) strcat(ds,".0");
        printf("%s%s%s%s",i&&!(i%m)?s2:"",ds,i?"":s,i<nx-1?"\n":"");
      }
      else if(i&&!(i%m)) printf("%s%s ",s2,ds);
      else printf("%s ",ds);
    }
    printf("]%s",e);
  }
}
static void pfa(U x, char *s, char *e) {
  int i,a0=1;
  char ds[256];
  float f,*pxf=(float*)px(x);
  if(!nx) printf("%s0#0.0%s",s,e);
  else if(1==nx) { printf("%s,",s); pf_(pxf[0]); printf("%s",e); }
  else {
    for(i=0;i<nx;i++) {
      f=pxf[i];
      if(isinf(f)&&f>0.0) { sprintf(ds,"0i"); a0=0; }
      else if(isnan(f)) { sprintf(ds,"0n"); a0=0; }
      else if(isinf(f)&&f<0.0) { sprintf(ds,"-0i"); a0=0; }
      else { sprintf(ds,"%0.*g",7,f); a0=ffix(ds,a0); }
      if(i==nx-1) {
        if(a0) strcat(ds,".0");
        printf("%s%s%s",ds,i?"":s,e);
      }
      else printf("%s%s ",i?"":s,ds);
    }
  }
}

static void ps_(char *s) {
  char *e;
  int v=vname(s,strlen(s));
  e=xesc(s);
  if(!v) printf("`\"%s\"",e);
  else printf("`%s",e);
  xfree(e);
}
static void ps(U x, char *s, char *e) {
  printf("%s",s); ps_((char*)(b(48)&x)); printf("%s",e);
}
static void psa(U x, char *s, char *e) {
  char **pxs=(char**)px(x);
  if(nx==1) printf("%s,",s);
  else printf("%s",s);
  i(nx,ps_(pxs[i]);if(i<nx-1)printf(" "))
  printf("%s",e);
}

void kprint(U x, char *s, char *e, char *s0) {
  U *pxu,v;
  fn *f;
  char s2[256];
  int aa=1,ncv=0;
  switch(tx) {
  case 2: pc(x,s,e); break;
  case 3: pi(x,s,e); break;
  case 4: pf(x,s,e); break;
  case 7: ps(x,s,e); break;
  case 0xa: pca(x,s,e); break;
  case 0xb: pia(x,s,e); break;
  case 0xc: mx?pfm(x,s,e,s0):pfa(x,s,e); break;
  case 0xf: psa(x,s,e); break;
  case 8:
    pxu=(U*)px(x);
    if(nx==1) { printf("%s,",s); kprint(pxu[0],"",e,s0); break; }
    printf("%s(",s);
    sprintf(s2,"%s ",s0);
    i(nx,if(pxu[i]>>63&&0xa!=pxu[i]>>60){aa=0;break;}) /* (1;2.0;"asdf") */
    i(nx,if(0xa==pxu[i]>>60)++ncv); if(nx==ncv) aa=0; /* ("asdf";"asdf") */
    if(aa) i(nx,kprint(pxu[i],"",i<nx-1?";":"",s0))
    else i(nx,kprint(pxu[i],i?s2:"",i<nx-1?"\n":"",s2))
    printf(")%s",e);
    break;
  default:
    if(zv(x)) {
      v=zvget(x);
      if(0xe==zx(v)) fprintf(stderr,"%s%s",(char*)(b(56)&v),e);
      else if(0xd==zx(v)) printf("%c%s",(char)v,e);
      else if(0xc==zx(v)) { f=(fn*)(b(56)&v); printf("%s\n",f->d); }
    }
    break;
  }
}

U kerror(char *e) {
  return zvset((U)sp(e),0xe);
}

U knorm(U x) {
  U r=x,*pxu;
  int t,*pri;
  float *prf;
  char *prc,**prs;
  if(tx==8&&nx) {
    pxu=(U*)px(x);
    t=pxu[0]>>60;
    i(nx,if(t!=pxu[i]>>60) return r)
    switch(t) {
    case 2: r=tn(2,nx); prc=(char*)px(r); i(nx,prc[i]=(char)pxu[i]); kfree(x); break;
    case 3: r=tn(3,nx); pri=(int*)px(r); i(nx,pri[i]=(int)pxu[i]); kfree(x); break;
    case 4: r=tn(4,nx); prf=(float*)px(r); i(nx,prf[i]=fu(pxu[i])) ; kfree(x);break;
    case 7: r=tn(7,nx); prs=(char**)px(r); i(nx,prs[i]=(char*)(b(48)&pxu[i])) ; kfree(x);break;
    }
  }
  return r;
}

int vname(char *s, int n) {
  int i,a=1,v=1;
  if(s[0]=='.'&&n>1) a=0;
  for(i=0;i<n;i++) {
    if(a && !isalpha(s[i])) v=0;
    else if(!isalnum(s[i]) && s[i]!='.') v=0;
    if(s[i]=='.') a=1;
    else a=0;
  }
  return v;
}
