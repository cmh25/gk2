#include "p.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "timer.h"
#include "k.h"
#include "x.h"
#include "repl.h"

void load(char *fn) {
  FILE *fp=0;
  int i,j=0,c,f,m=256;
  U x;
  char *p=xmalloc(m+2);
  pr *r;
  fp=fopen(fn,"r");
  if(!fp) { fprintf(stderr,"%s: %s\n",fn,strerror(errno)); return; }
  while(1) {
    f=1; i=0;
    p=xmalloc(m+2);
    while((c=fgetc(fp))!=EOF) {
      p[i++]=c;
      if(i==m) { m<<=1; p=xrealloc(p,m+2); }
      if(f==1&&c=='\\') { j=i-1; ++f; }
      else if(f==2&&c=='\\') f=0;
      else if(f==2&&c=='\n') { p[j]=0; break; }
      if(!isblank(c)&&c!='\\') f=0;
      if(!f&&c=='\n') { break; }
    }
    if(p[i-1]!='\n') p[i++]='\n';
    p[i]=0;
    r=pgparse(p);
    xfree(p);
    x=pgreduce(r);
    xfree(r);
    kprint(x);
    kfree(x);
    if(f==2) break;
  }
  fclose(fp);
}

void repl() {
  int c,j; size_t i,m=2; pgs *s; char *b,*p; U x;
  pr *r;
  printf("  ");
  for(i=0;;i=0) {
    b=p=xmalloc(m+2);
    while((c=fgetc(stdin))&&c!='\n') {
      b[i++]=c;
      if(i==m) { m<<=1; b=p=xrealloc(b,m+2); }
    }
    if(!i) { xfree(p); printf("  "); continue; }
    b[i++]='\n'; b[i]=0;
    r=pgparse(p);
    if(TIMES) {
      timer_start();
      for(j=0;j<TIMES;j++) x=pgreduce(r);
      printf("%.3f\n",timer_stop());
    }
    else {
      x=pgreduce(r);
      xfree(r);
      kprint(x);
      kfree(x);
    }
    xfree(p);
    printf("  ");
  }
}
