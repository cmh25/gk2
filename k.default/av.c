#include "av.h"

// ":+-*%&|<>=~.!@?#_^,$LMSA..ERZ'/\\"
U over(U a,U x) {
  U r=0;
  int si,*pxi;
  float sf,*pxf;
  switch((int)a) {
  case 1:
    switch(tx) {
    case 3: r=1; break;
    case 4: r=1; break;
    case 0xb: /* +/iv */
      pxi=(int*)k_(2,x);
      si=0; i(nx,si+=*pxi++);
      r=t(3,(uint)si);
      break;
    case 0xc: /* +/fv */
      pxf=(float*)k_(2,x);
      sf=0; i(nx,sf+=*pxf++);
      r=t(4,*(uint*)&sf);
      break;
    } break;
  }
  return r;
}
