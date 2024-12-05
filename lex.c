#include "lex.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "x.h"
#include "sym.h"
#include "zv.h"
#include "fn.h"

static char *P=":+-*%&|<>=~.!@?#_^,$LMSA..ERZ'/\\";

static void help(void) {
  printf(""
  "Verb    (monad)\n"
  "+ +            \n"
  "- -            \n"
  "* *      sqr   \n"
  "%% div    sqrt  \n"
  "& and    flip  \n"
  "| or     flop  \n"
  "< <      asc   \n"
  "> >      desc  \n"
  "= =      group \n"
  "~ ~      match \n"
  ". .      value \n"
  "! mod    index \n"
  "@ @      first \n"
  "? find   unique\n"
  "# take   count \n"
  "_ drop   floor \n"
  "^ cut    rule  \n"
  ", join   enlist\n");
}

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
  int r0,r,*iv=0,i;
  int ic=0,fc=0,imm=1,fm=1;
  float *fv=0;
  char *q;
  r0=gn_();
  if(isblank(*p)) {
    q=p;
    while(isblank(*p))++p;
    if(isdigit(*p)||((*p=='.'||*p=='-')&&isdigit(p[1]))) { /* convert to vector */
      if(r0==1) { imm<<=1; iv=xrealloc(iv,imm*sizeof(int)); iv[ic++]=iii; }
      else if(r0==2) { fm<<=1; fv=xrealloc(fv,fm*sizeof(float)); fv[fc++]=fff; }
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
          for(i=0;i<ic;i++) fv[fc++]=FI(iv[i]);
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
          fff=FI(iii);
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
    U x=tn(3,ic);
    int *pi=(int*)px(x);
    i(ic,pi[i]=iv[i])
    push(pgs,T012,x);
  }
  else if(fc) {
    U x=tn(4,fc);
    float *pf=(float*)px(x);
    i(fc,pf[i]=fv[i])
    push(pgs,T012,x);
  }
  else if(r0==1) push(pgs,T012,(iii&0xffffffff)|(U)3<<60);
  else if(r0==2) push(pgs,T012,(*((int*)&fff)&0xffffffff)|(U)4<<60);
  if(iv) xfree(iv);
  if(fv) xfree(fv);
  return r0;
}

static int gname(pgs *pgs) {
  char c,*q=p;
  int s=*p=='.';
  while(1) {
    if(!s) { if(isalpha(*p)) { ++p; s=1; } else break; }
    else { if(isalnum(*p)) ++p; else if(*p=='.') { ++p; s=0; } else break; }
  }
  c=*p; *p=0;
  push(pgs,T012,zvset((U)sp(q),0xf));
  *p=c;
  return 1;
}

//static char *ss;
//static int gc(pgs *pgs) {
//  char s=0;
//  int j=0,n;
//  unsigned char o;
//  U u;
//  char *puc;
//  n=32;
//  ss=xmalloc(n);
//  ++p;
//  while(1) {
//    if(j>=n-1) { n<<=1; ss=xrealloc(ss,n); }
//    switch(s) {
//    case 0:
//      if(*p=='"') s=10;
//      else if(*p=='\\') s=1;
//      else ss[j++]=*p;
//      break;
//    case 1: /* escape */
//      if(*p=='b') { ss[j++]='\b'; s=0; }
//      else if(*p=='t') { ss[j++]='\t'; s=0; }
//      else if(*p=='n') { ss[j++]='\n'; s=0; }
//      else if(*p=='r') { ss[j++]='\r'; s=0; }
//      else if(*p=='"') { ss[j++]='\"'; s=0; }
//      else if(*p=='\\') { ss[j++]='\\'; s=0; }
//      else if(isdigit(*p)&&*p<='7') { o=*p-48; s=2; } /* octal */
//      else { ss[j++]=*p; s=0; }
//      break;
//    case 2: /* octal */
//      if(isdigit(*p)&&*p<='7') { o*=8; o+=*p-48; s=3; }
//      else if(*p=='\\') { ss[j++]=o; s=1; }
//      else if(*p=='"') { ss[j++]=o; s=10; }
//      else { ss[j++]=o; ss[j++]=*p; s=0; }
//      break;
//    case 3: /* octal */
//      if(isdigit(*p)&&*p<='7') { o*=8; o+=*p-48; ss[j++]=o; s=0; }
//      else if(*p=='\\') { ss[j++]=o; s=1; }
//      else if(*p=='"') { ss[j++]=o; s=10; }
//      else { ss[j++]=o; ss[j++]=*p; s=0; }
//      break;
//    case 10: /* accept */
//      if(j==0) push(pgs,T012,(U)0xa<<60);
//      else if(j==1) push(pgs,T012,ss[0]|(U)2<<60);
//      else {
//        u=tn(2,j);
//        puc=(char*)k_(2,u);
//        i((int)u,*puc++=ss[i])
//        push(pgs,T012,u);
//      }
//      xfree(ss);
//      return 1;
//    default: return 0; /* error */
//    }
//    if(!*++p) return 0;
//  }
//  return 1;
//}

static int gf(pgs *pgs) {
  char *q,c,s=0;
  fn *f;
  int fc=0;
  q=p;
  while(1) {
    if(*p=='"') p=xeqs(p);
    switch(s) {
    case 0:
      if(!*p) return 0;
      else if(*p=='}'&&fc==1) s=1;
      else if(*p=='}') fc--;
      else if(*p=='{') fc++;
      break;
    case 1: /* accept */
      c=*p; *p=0;
      f=fnnew(q);
      push(pgs,T013,(U)f|(U)0xe<<60);
      *p=c;
      return 1;
    }
    ++p;
  }
  return 1;
}

static int gback(pgs *pgs, int load) {
  char c,*q,*puc;
  int t;
  U u;
  if(p[1]=='\\') {
    if(load==2) { /* \l file */
      push(pgs,T010,0);
      *p=0;
    }
    else {
      p+=2;
      push(pgs,T013,96);
      push(pgs,T012,(U)3<<60); /* zero */
      push(pgs,T011,0);
      *p=0;
    }
  }
  else if(p[1]=='\n') {
    if(load) {
      push(pgs,T010,0);
      ++p;
      p[1]=0;
    }
    else { help(); return 0; }
  }
  else if(p[1]=='t') {
    p+=2;
    push(pgs,T013,97);
    if(isblank(*p)) { t=1; push(pgs,T012,(U)t|(U)3<<60); }
    else if((t=atoi(p))) { while(isdigit(*p))++p; push(pgs,T012,(U)t|(U)3<<60); }
    else if(isalpha(*p)) gname(pgs);
    if(isblank(*p)) while(isblank(*p)) ++p;
    else { printf("lex\n"); return 0; }
    push(pgs,T010,0);
  }
  else if(p[1]=='l'&&p[2]&&strchr(" \n\t",p[2])) {
    push(pgs,T013,98);
    p+=2;
    while(isblank(*p))++p;
    q=p;
    while(*p&&*p!='\n')++p;
    c=*p; *p=0;
    if(strlen(q)) {
      u=tn(2,strlen(q));
      puc=(char*)k_(2,u);
      i((int)u,*puc++=q[i])
      push(pgs,T012,u);
    }
    else push(pgs,T012,0);
    *p=c;
  }
  return 1;
}

int lex(pgs *pgs, int load) {
  int f=1,s;
  p=pgs->p;
  while(1) {
    s=isblank(*p);
    while(isblank(*p)) ++p;
    if((s||f)&&*p=='/') { while(*++p!='\n'){}; }
    else if(*p=='-') {
      if(!(s|f)&&(pgs->lt==T012||pgs->lt==T015)) { ++p; push(pgs,T013,'-'); }
      else if(isdigit(p[1])||(p[1]=='.'&&isdigit(p[2]))) { if(!gn(pgs)) { printf("lex\n"); return 0; } }
      else { ++p; push(pgs,T013,'-'); }
    }
    else if(f&&*p=='\\') { if(!gback(pgs,load)) return 0; }
    else if(isdigit(*p)||(*p=='.'&&isdigit(p[1]))) { if(!gn(pgs)) { printf("lex\n"); return 0; } }
    else if(*p&&strchr(P,*p)) {
      if(p[1]&&p[1]=='/') { push(pgs,T012,*p); ++p; push(pgs,T013,*p); ++p; }
      else { push(pgs,T013,*p); ++p; }
    }
    else if(*p=='(') { ++p; push(pgs,T014,0); }
    else if(*p==')') { ++p; push(pgs,T015,0); }
    else if(*p=='[') { ++p; push(pgs,T016,0); }
    else if(*p==']') { ++p; push(pgs,T017,0); }
    else if(*p=='{') { if(!gf(pgs)) { printf("lex\n"); return 0; } }
    else if(*p==';') { ++p; push(pgs,T010,0); }
    else if(*p=='\n') { ++p; push(pgs,T011,0); while(*p=='\n')++p; f=1; continue; }
    else if(isalpha(*p)) gname(pgs);
    else if(!*p) { push(pgs,T018,0); break; }
    else { printf("lex\n"); return 0; }
    f=0;
  }
  return 1;
}
