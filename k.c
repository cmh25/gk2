#include "k.h"
#include <stdio.h>
#include <limits.h>
#include "x.h"

 _f(_r,P(ax,x)P(7&Ox,--Ox;x)if(!tx)i(nx,_r(xU[i]))_o(x))
_f(r_,P(ax,x)++Ox;x)
void kfree(U x){_r(x);}
U kref(U x){return r_(x);}

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
  int *a,h,j,a0=1;
  char ds[256];
  if(ax) {
    if(tx==3) pi((int)x,"\n");
    else if(tx==4) { h=(int)x; pf(*(float*)&h,"\n"); }
  }
  else { /* vector */
    a=sx;
    if(tx==3) {
      if(!nx) printf("!0\n");
      else if(1==nx) { printf(","); pi(a[0],"\n"); }
      else {
        for(j=0;j<nx-1;j++) pi(a[j]," ");
        pi(a[j],"\n");
      }
    }
    else if(tx==4) {
      if(!nx) printf("0#0.0\n");
      else if(1==nx) { printf(","); pf(*(float*)&a[0],"\n"); }
      else {
        sprintf(ds,"%0.*g",7,*(float*)&a[0]);
        a0=ffix(ds,a0);
        printf("%s ",ds);
        for(j=1;j<nx-1;j++) {
          sprintf(ds,"%0.*g",7,*(float*)&a[j]);
          a0=ffix(ds,a0);
          printf("%s ",ds);
        }
        sprintf(ds,"%0.*g",7,*(float*)&a[j]);
        a0=ffix(ds,a0);
        if(a0) strcat(ds,".0");
        printf("%s\n",ds);
      }
    }
  }
}


