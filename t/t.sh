#!/bin/bash

ec=0
for t in `cat tests`; do
  echo -n "t$t: "
  ../gk t$t > $t 2>/dev/null
  diff -u r$t $t &> d$t
  if [ $? -ne 0 ]; then
    ec=$((ec+1))
    echo -e "fail *****"
  else
    echo -e "pass"
    rm -f $t d$t
  fi
done
echo failed: $ec
exit 0
