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
  pgs *s;
  U x;
  fp=fopen(fn,"r");
  if(!fp) { fprintf(stderr,"%s: %s\n",fn,strerror(errno)); return; }
  while(1) {
    s=pgnew();
    f=1; i=0;
    s->p=xmalloc(m+2);
    while((c=fgetc(fp))!=EOF) {
      s->p[i++]=c;
      if(i==m) { m<<=1; s->p=xrealloc(s->p,m+2); }
      if(f==1&&c=='\\') { j=i-1; ++f; }
      else if(f==2&&c=='\\') f=0;
      else if(f==2&&c=='\n') { s->p[j]=0; break; }
      if(!isblank(c)&&c!='\\') f=0;
      if(!f&&c=='\n') { break; }
    }
    if(s->p[i-1]!='\n') s->p[i++]='\n';
    s->p[i]=0;
    pgparse(s);
    x=pgreduce(s);
    kprint(x);
    kfree(x);
    pgfree(s);
    if(f==2) break;
  }
  fclose(fp);
}

void repl() {
  int c,j; size_t i,m=2; pgs *s; char *b; U x;
  printf("  ");
  for(i=0;;i=0) {
    s=pgnew();
    b=s->p=xmalloc(m+2);
    while((c=fgetc(stdin))&&c!='\n') {
      b[i++]=c;
      if(i==m) { m<<=1; b=s->p=xrealloc(b,m+2); }
    }
    if(!i) { pgfree(s); printf("  "); continue; }
    b[i++]='\n'; b[i]=0;
    pgparse(s);
    if(TIMES) {
      timer_start();
      for(j=0;j<TIMES;j++) x=pgreduce(s);
      printf("%.3f\n",timer_stop());
    }
    else {
      x=pgreduce(s);
      kprint(x);
      kfree(x);
    }
    pgfree(s);
    printf("  ");
  }
}
