#!/usr/bin/env bash
kill -l |
tr ' ' '\n' |
awk '{printf "{\"%s\", SIG%s},\n", $1, $1}'
