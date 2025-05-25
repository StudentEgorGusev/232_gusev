#!/usr/bin/env bash
sum() {
  local total=0 res rc
  for x in "$@"; do
    expr "$x" + 0 >/dev/null 2>&1
    rc=$?
    [ $rc -eq 2 ] && printf 0 && return 0 

    res=$(expr "$total" + "$x" 2>/dev/null)
    rc=$?
    [ $rc -eq 2 ] && printf 0 && return 0 
    total=$res
  done
  printf '%s' "$total"
}

IFS= read -r line1
IFS= read -r line2

s1=$(sum $line1 2>/dev/null)
s2=$(sum $line2 2>/dev/null)

if [ "$s1" = "$s2" ]; then
  echo "Equal"
else
  echo "Not equal"
fi
