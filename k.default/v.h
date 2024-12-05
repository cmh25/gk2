#ifndef V_H
#define V_H

#include "k.h"

#define FDSIZE 20
#define FMSIZE 20
extern U (*FD[FDSIZE])(U,U);
extern U (*FM[FMSIZE])(U);

U plus(U a,U x);
U minus(U a,U x);
U times(U a,U x);
U divide(U a,U x);
U minand(U a,U x);
U maxor(U a,U x);
U less(U a,U x);
U more(U a,U x);
U equal(U a,U x);
U match(U a,U x);
U dot(U a,U x);
U mod(U a,U x);
U at(U a,U x);
U find(U a,U x);
U take(U a,U x);
U drop(U a,U x);
U cut(U a,U x);
U join(U a,U x);
U parse(U a,U x);

U abs_(U x);
U negate(U x);
U square(U x);
U sqrt_(U x);
U flip(U x);
U reverse(U x);
U asc(U x);
U desc(U x);
U group(U x);
U not_(U x);
U value(U x);
U bang(U x);
U first(U x);
U unique(U x);
U count(U x);
U floor_(U x);
U rule(U x);
U enlist(U x);
U str(U x);

#endif /* V_H */
