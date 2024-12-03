#include "k.h"
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include "x.h"
#include "scope.h"
#include "zv.h"

void* px(U x){return(void*)k(0,x,0);}
void kfree(U x){if(ax)return; k(15,0,x);}
U kref(U x){if(ax)return x; return k(0,0,x);}

void kinit(void) {
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
  float *pxf=(float*)px(x);
  if(!nx) printf("0#0.0%s",c);
  else if(1==nx) { printf(","); pf_(pxf[0],c); }
  else {
    for(i=0;i<nx;i++) {
      sprintf(ds,"%0.*g",7,pxf[i]);
      a0=ffix(ds,a0);
      if(m&&!((i+1)%m)) {
        if(a0) strcat(ds,".0");
        printf("%s%s",ds,i<nx-1?"\n":c);
      }
      else printf("%s ",ds);
    }
  }
}

void kprint(U x, char *c) {
  U *pxu,v;
  switch(tx) {
  case 3: pi(x,c); break;
  case 4: pf(x,c); break;
  case 0xb: pia(x,c); break;
  case 0xc: pfa(x,c); break;
  case 8:
    pxu=(U*)px(x);
    printf("(");
    i(nx,kprint(pxu[i],i<nx-1?";":""))
    printf(")%s",c);
    break;
  default:
    if(zv(x)) {
      v=zvget(x);
      if(0xe==v>>60)  printf("%s%s",(char*)(((U)0xe<<60)^v),c);
      else if(0xd==v>>60)  printf("%c%s",(char)v,c);
    }
    break;
  }
  kfree(x);
}
