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

void load(char *fn, int load) {
  FILE *fp=0; pr *r; char *p;
  size_t zr;
  #ifdef _WIN32
    struct _stat64 t;
    if(-1==_stat64(fn,&t)) { fprintf(stderr,"%s: %s\n",fn,strerror(errno)); return; }
  #else
    struct stat t;
    if(-1==stat(fn,&t)) { fprintf(stderr,"%s: %s\n",fn,strerror(errno)); return; }
  #endif
  fp=fopen(fn,"r");
  if(!fp) { fprintf(stderr,"%s: %s\n",fn,strerror(errno)); return; }
  p=xmalloc(1+t.st_size);
  zr=fread(p,1,t.st_size,fp);
  if((size_t)t.st_size<zr) {
    fprintf(stderr,"%s: error reading file\n",fn);
    xfree(p);
    return;
  }
  p[zr]=0;
  fclose(fp);
  r=pgparse(p,load);
  xfree(p);
  if(r) {
    (void)pgreduce(r,1);
    prfree(r);
  }
}

void repl(void) {
  int c; size_t i,m=2; char *b,*p;
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
    r=pgparse(p,0);
    xfree(p);
    if(r) {
      (void)pgreduce(r,1);
      prfree(r);
    }
    printf("  ");
  }
}
