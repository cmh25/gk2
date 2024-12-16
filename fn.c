#include "fn.h"
#include <ctype.h>
#include <string.h>
#include "x.h"
#include "sym.h"
#include "p.h"
#include "zv.h"

fn* fnnew(char *s) {
  fn *f=xcalloc(1,sizeof(fn));
  f->d=xstrdup(s);
  return f;
}

void fnfree(fn *f) {
  xfree(f->d);
  if(f->n) prfree(f->n);
  if(f->s) scope_free(f->s);
  xfree(f);
}

U fnd(fn *ff) {
  U r=0;
  char *f=0,b[256],*v[256],*g,*h;
  int i,j,u,s,n,q,vx,vy,vz;
  f=ff->d;
  s=j=n=q=vx=vy=vz=0;
  if(*f!='{') return r;
  for(;*f;++f) {
    if(*f=='"') f=xeqs(f);
    switch(s) {
    case 0:
      if(*f=='{') s=1;
      else return kerror("parse");
      break;
    case 1:
      while(isblank(*f))++f;
      if(*f=='}') s=2;
      else if(*f=='{') { n++; s=9; }
      else if(*f=='[') s=3;
      else if(*f=='.') s=11;
      else if(*f=='`') s=101;
      else if(isalpha(*f)) { s=7; b[j++]=*f; }
      else s=6;
      break;
    case 101:
      if(isalnum(*f)) s=101;
      else s=1;
      break;
    case 2:
      return kerror("parse");
    case 3:
      if(isalpha(*f)) { s=4; b[j++]=*f; ff->q=1; }
      else if(*f==']') s=5;
      else return kerror("parse");
      break;
    case 4:
      if(isalnum(*f)) { s=4; b[j++]=*f; }
      else if(*f==']') { s=5; b[j]=0; j=0; v[q++]=sp(b); }
      else if(*f==';') { s=3; b[j]=0; j=0; v[q++]=sp(b); }
      break;
    case 5:
      if(*f=='}') s=2;
      else if(*f=='.') s=15;
      else if(*f=='`') s=105;
      else if(isalpha(*f)) { s=7; b[j++]=*f; }
      else s=6;
      break;
    case 105:
      if(isalnum(*f)) s=105;
      else s=5;
      break;
    case 6:
      if(*f=='}') s=2;
      else if(*f=='.') s=16;
      else if(*f=='`') s=106;
      else if(isalpha(*f)) { s=7; b[j++]=*f; }
      else if(*f=='{') { n++; s=8; }
      else s=6;
      break;
    case 106:
      if(isalnum(*f)) s=106;
      else if(*f=='`') s=106;
      else s=6;
      break;
    case 7:
      if(*f=='}') {
        s=2; b[j]=0; j=0;
        if(!ff->q) { /* no implicit xyz if there are formal parameters */
          if(!vx && !strcmp(b,"x")) { vx=1; v[q++]=sp(b); }
          if(!vy && !strcmp(b,"y")) { vy=1; v[q++]=sp(b); }
          if(!vz && !strcmp(b,"z")) { vz=1; v[q++]=sp(b); }
        }
      }
      else if(isalnum(*f)) b[j++]=*f;
      else if(*f=='{') {
        s=10; b[j]=0; j=0;
        if(!ff->q) { /* no implicit xyz if there are formal parameters */
          if(!vx && !strcmp(b,"x")) { vx=1; v[q++]=sp(b); }
          if(!vy && !strcmp(b,"y")) { vy=1; v[q++]=sp(b); }
          if(!vz && !strcmp(b,"z")) { vz=1; v[q++]=sp(b); }
        }
      }
      else { /* no implicit xyz if there are formal parameters */
        s=6; b[j]=0; j=0;
        if(!ff->q) { /* no implicit xyz if there are formal parameters */
          if(!vx && !strcmp(b,"x")) { vx=1; v[q++]=sp(b); }
          if(!vy && !strcmp(b,"y")) { vy=1; v[q++]=sp(b); }
          if(!vz && !strcmp(b,"z")) { vz=1; v[q++]=sp(b); }
        }
      }
      break;
    case 8:
      if(*f=='}') { n--; if(!n) s=6; }
      else if(*f=='{') n++; /* nested function */
      break;
    case 9:
      if(*f=='}') { n--; if(!n) s=5; }
      else if(*f=='{') n++; /* nested function */
      break;
    case 10:
      if(*f=='}') { n--; if(!n) s=7; }
      else if(*f=='{') n++; /* nested function */
      break;
    case 11: /* .z.s */
      if(isalnum(*f)) s=11;
      else if(*f=='.') s=11;
      else s=1;
      break;
    case 15: /* .z.s */
      if(isalnum(*f)) s=15;
      else if(*f=='.') s=15;
      else s=5;
      break;
    case 16: /* .z.s */
      if(isalnum(*f)) s=16;
      else if(*f=='.') s=16;
      else s=6;
      break;
    default: return kerror("parse");
    }
  }

  ff->s=scope_new(cs);
  if(vz&&q<3) v[q++]=sp("y");
  if(vz&&q<3) v[q++]=sp("x");
  if(vy&&q<2) v[q++]=sp("x");
  ff->v=q;
  for(i=0;i<q;i++) scope_set(ff->s,v[i],0);

  /* parse */
  u=strlen(ff->d);
  g=h=xstrdup(ff->d);
  ++h;
  h[u-2]='\n';
  while(isblank(*h))++h;
  if(*h=='[') while(*h&&*h++!=']');
  ff->n=pgparse(h,1);
  xfree(g);
  return r;
}

static U vlookup(U v) {
  char *s=(char*)(v^(U)15<<56);
  U r=scope_get(cs,s);
  return r?r:4;
}
U fne(fn *f, U *x, int n) {
  U r=0,a;
  int i=0;
  scope *os;
  if(n!=f->v) return 7; /* valence */
  for(i=0;i<f->v;i++) {
    a=x[i];
    if(zv(a)) { a=zvget(a); if(15==a>>56) a=vlookup(a); else return 4; /* value */ }
    scope_set(f->s,f->s->d->k[i],a);
  }
  os=cs;cs=f->s;
  r=pgreduce(f->n,0); 
  cs=os;
  return r;
}
