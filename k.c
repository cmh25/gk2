#include "k.h"
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include "x.h"
#include "scope.h"

void* px(U x){return(void*)k(0,x,0);}
void kfree(U x){if(ax)return; k(15,0,x);}
U kref(U x){if(ax)return x; return k(0,0,x);}

void kinit(void) {
  scope_init();
}

static void pi(int i, char *c) {
  if(i==INT_MAX) printf("0I%s",c);
  else if(i==INT_MIN) printf("0N%s",c);
  else if(i==INT_MIN+1) printf("-0I%s",c);
  else printf("%d%s",i,c);
}

static void pf(float f, char *c) {
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

static int ffix(char *ds, int a0) {
  if(strchr(ds,'.')||strchr(ds,'e')) return 0;
  if(!strcmp(ds,"inf")) { sprintf(ds,"0i"); return 0; }
  if(!strcmp(ds,"nan")) { sprintf(ds,"0n"); return 0; }
  if(!strcmp(ds,"-inf")) { sprintf(ds,"-0i"); return 0; }
  return a0;
}

void kprint(U x) {
  int h,j,a0=1;
  char ds[256];
  int *pxi;
  float *pxf;
  switch(tx) {
  case 3: pi((int)x,"\n"); break;
  case 4: h=(int)x; pf(*(float*)&h,"\n"); break;
  case 0xb: 
    pxi=(int*)px(x);
    if(!nx) printf("!0\n");
    else if(1==nx) { printf(","); pi(pxi[0],"\n"); }
    else {
      for(j=0;j<nx-1;j++) pi(pxi[j]," ");
      pi(pxi[j],"\n");
    }
    break;
  case 0xc:
    pxf=(float*)px(x);
    if(!nx) printf("0#0.0\n");
    else if(1==nx) { printf(","); pf(pxf[0],"\n"); }
    else {
      sprintf(ds,"%0.*g",7,pxf[0]);
      a0=ffix(ds,a0);
      printf("%s ",ds);
      for(j=1;j<nx-1;j++) {
        sprintf(ds,"%0.*g",7,pxf[j]);
        a0=ffix(ds,a0);
        printf("%s ",ds);
      }
      sprintf(ds,"%0.*g",7,pxf[j]);
      a0=ffix(ds,a0);
      if(a0) strcat(ds,".0");
      printf("%s\n",ds);
    }
    break; 
  case 0xe: printf("%s\n",(char*)((0xeL<<60)^x)); break;
  }
}
