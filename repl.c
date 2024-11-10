#include "p.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <sys/stat.h>
#include "timer.h"
#include "k.h"
#include "x.h"
#include "repl.h"

void load(char *fn) {
  FILE *fp=0; U x; pr *r; struct stat t; char *p;
  if(-1==stat(fn,&t)) { fprintf(stderr,"%s: %s\n",fn,strerror(errno)); return; }
  fp=fopen(fn,"r");
  if(!fp) { fprintf(stderr,"%s: %s\n",fn,strerror(errno)); return; }
  p=xmalloc(1+t.st_size);
  if(t.st_size!=fread(p,1,t.st_size,fp)) {
    fprintf(stderr,"%s: error reading file\n",fn);
    xfree(p);
    return;
  }
  p[t.st_size]=0;
  fclose(fp);
  r=pgparse(p);
  x=pgreduce(r,1);
  xfree(p);
  prfree(r);
  kfree(x);
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
    if(r) {
      if(TIMES) {
        timer_start();
        for(j=0;j<TIMES;j++) x=pgreduce(r,0);
        printf("%.3f\n",timer_stop());
      }
      else {
        x=pgreduce(r,1);
        xfree(r);
        kfree(x);
      }
    }
    xfree(p);
    printf("  ");
  }
}
