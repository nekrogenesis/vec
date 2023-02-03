#!/bin/bash

RED='\033[1;31m'
GREEN='\033[1;32m'
RESET='\033[0m'
BOLD='\033[1m'

CFLAGS="-ggdb -g3 -std=c99 -Wall -Wextra -Wpedantic"
INCL="src/vec.c"

for FILE in tests/*.c
do
    gcc $CFLAGS $FILE $INCL -o ${FILE/.c/.out}
done

TEST=0; PASS=0; FAIL=0
for FILE in tests/*.out
do
    let "TEST++"
    ./$FILE
    if [[ $? -ne 0 ]]
    then
        printf "${RED}FAILED:${RESET} $FILE\n"
        let "FAIL++"
    else
        printf "${GREEN}PASSED:${RESET} $FILE\n"
        let "PASS++"
    fi
done
printf "\n$TEST ${BOLD}TESTED - $PASS ${GREEN}PASSED${RESET} - $FAIL ${RED}FAILED${RESET}\n"