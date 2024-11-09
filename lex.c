#include "lex.h"
#include <math.h>
#include "x.h"
#include "sym.h"
#include "zv.h"

static void push(pgs *s, int tt, U tv) {
  s->t[s->tc]=tt;
  s->v[s->tc++]=tv;
  s->lt=tt;
}

static char *p;
static int iii;
static float fff;
static int gn_(void) {
  char c,*q=p;
  int s=0;
  while(1) {
    switch(s) {
    case 0:
      if(*p=='0') s=1;
      else if(isdigit(*p)) s=4;
      else if(*p=='-') s=5;
      else if(*p=='.') s=7;
      else s=10;
      break;
    case 1:
      if(*p=='n'||*p=='i') s=2;
      else if(*p=='N'||*p=='I') s=3;
      else if(*p=='e'||*p=='E') s=8;
      else if(*p=='.') s=6;
      else if(isdigit(*p)) s=4;
      else s=11;
      break;
    case 2: s=12; break;
    case 3: s=11; break;
    case 4:
      if(isdigit(*p)) s=4;
      else if(*p=='e'||*p=='E') s=8;
      else if(*p=='.') s=6;
      else s=11;
      break;
    case 5:
      if(*p=='0') s=1;
      else if(isdigit(*p)) s=4;
      else if(*p=='.') s=7;
      else s=10;
      break;
    case 6:
      if(isdigit(*p)) s=9;
      else if(*p=='e'||*p=='E') s=8;
      else s=12;
      break;
    case 7: if(isdigit(*p)) s=9; else s=10; break;
    case 8: if(isdigit(*p)||*p=='-'||*p=='+') s=9; else s=10; break;
    case 9:
      if(isdigit(*p)) s=9;
      else if(*p=='e'||*p=='E') s=8;
      else s=12;
      break;
    case 10: return 0; /* error */
    case 11: /* int */
      c=*--p; *p=0;
      iii=xatoi(q);
      *p=c;
      return 1;
    case 12: /* float */
      c=*--p; *p=0;
      fff=xstrtof(q);
      *p=c;
      return 2;
    }
    ++p;
  }
  return 0;
}

static int gn(pgs *pgs) {
  int r,*iv=0,i;
  int ic=0,fc=0,imm=1,fm=1;
  float *fv=0;
  char *q;
  r=gn_();
  if(isblank(*p)) {
    q=p;
    while(isblank(*p))++p;
    if(isdigit(*p)||((*p=='.'||*p=='-')&&isdigit(p[1]))) { /* convert to vector */
      if(r==1) { imm<<=1; iv=xrealloc(iv,imm*sizeof(int)); iv[ic++]=iii; }
      else if(r==2) { fm<<=1; fv=xrealloc(fv,fm*sizeof(float)); fv[fc++]=fff; }
    }
    p=q;
    if(iv) {
      while(isblank(*p)) {
        q=p;
        while(isblank(*p))++p;
        r=gn_();
        if(r==1) {
          if(ic==imm) { imm<<=1; iv=xrealloc(iv,imm*sizeof(int)); }
          iv[ic++]=iii;
        }
        else if(r==2) {
          fm=imm;
          fv=xrealloc(fv,fm*sizeof(float));
          for(i=0;i<ic;i++) fv[fc++]=I2F(iv[i]);
          xfree(iv); iv=0; ic=0;
          if(fc==fm) { fm<<=1; fv=xrealloc(fv,fm*sizeof(float)); }
          fv[fc++]=fff;
          break;
        }
        else { p=q; break; }
      }
    }
    if(fv) {
      while(isblank(*p)) {
        q=p;
        while(isblank(*p))++p;
        r=gn_();
        if(r==1) {
          fff=I2F(iii);
          if(fc==fm) { fm<<=1; fv=xrealloc(fv,fm*sizeof(float)); }
          fv[fc++]=fff;
        }
        else if(r==2) {
          if(fc==fm) { fm<<=1; fv=xrealloc(fv,fm*sizeof(float)); }
          fv[fc++]=fff;
        }
        else { p=q; break; }
      }
    }
  }
  if(ic) {
    U x=K(3,ic);
    int *pi=sx;
    i(ic,pi[i]=iv[i])
    push(pgs,T012,x);
  }
  else if(fc) {
    U x=K(4,fc);
    float *pf=sx;
    i(fc,pf[i]=fv[i])
    push(pgs,T012,x);
  }
  else if(r==1) push(pgs,T012,iii&0xffffffff|3L<<60);
  else if(r==2) push(pgs,T012,*((int*)&fff)&0xffffffff|4L<<60);
  if(iv) xfree(iv);
  if(fv) xfree(fv);
  return r;
}

static int gname(pgs *pgs) {
  char c,*q=p;
  int s=*p=='.';
  char *z;
  while(1) {
    if(!s) { if(isalpha(*p)) { ++p; s=1; } else break; }
    else { if(isalnum(*p)) ++p; else if(*p=='.') { ++p; s=0; } else break; }
  }
  c=*p; *p=0;
  z=sp(q);
  zv[zvi++]=(U)z|0xfL<<60;
  push(pgs,T012,(U)zvi<<32); /* into mx */
  *p=c;
  return 1;
}

static void help() {
  printf(""
  "Verb    (monad)\n"
  "+ +            \n"
  "- -            \n"
  "* *      sqr   \n"
  "! mod    index \n"
  "@ @      first \n"
  "? find   unique\n"
  "# take   count \n");
}

unsigned int TIMES;
int lex(pgs *pgs) {
  int f=1,s;
  TIMES=0;
  p=pgs->p;
  while(1) {
    s=isblank(*p);
    while(isblank(*p)) ++p;
    if((s||f)&&*p=='/') { while(*++p!='\n'){}; while(*++p=='\n'){}; continue; }
    if(*p=='-') {
      if(!(s|f)&&(pgs->lt==T012||pgs->lt==T015)) { ++p; push(pgs,T013,'-'); }
      else if(isdigit(p[1])||(p[1]=='.'&&isdigit(p[2]))) gn(pgs);
      else { ++p; push(pgs,T013,'-'); }
    }
    else if(isdigit(*p)||(*p=='.'&&isdigit(p[1]))) gn(pgs);
    else if(*p&&strchr(":+-*%&|<>=~.!@?#_^,$",*p)) { push(pgs,T013,*p); ++p; }
    else if(*p=='(') { ++p; push(pgs,T014,0); }
    else if(*p==')') { ++p; push(pgs,T015,0); }
    else if(*p=='[') { ++p; push(pgs,T016,0); }
    else if(*p==']') { ++p; push(pgs,T017,0); }
    else if(*p==';') { ++p; push(pgs,T010,0); }
    else if(*p=='\n') { ++p; push(pgs,T011,0); while(*p=='\n')++p; f=1; continue; }
    else if(isalpha(*p)) gname(pgs);
    else if(*p=='\\'&&*(p+1)=='\\') {
      p+=2;
      push(pgs,T013,96);
      push(pgs,T012,3L<<60); /* zero */
    }
    else if(*p=='\\'&&*(p+1)=='\n') { help(); return 0; }
    else if(*p=='\\'&&*(p+1)=='t') { p+=2; if(!(TIMES=atoi(p)))TIMES=1; while(isdigit(*p))++p; }
    else if(!*p) { push(pgs,T018,0); break; }
    else { printf("lex\n"); return 0; }
    f=0;
  }
  return 1;
}
