#!/bin/bash
for i in p000 p001 p002 p003; do
  echo "$i ========================="
  ../gk $i
  echo
done
exit 0
