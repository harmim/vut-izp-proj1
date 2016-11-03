#!/bin/bash

PROJ1=../proj1

echo "Hello, world! Ahoj svete!" | ${PROJ1} >> output.txt
echo "Ahoj" | ${PROJ1} >> output.txt
echo "Hello, world! Ahoj svete!" | ${PROJ1} -s 14 -n 5 >> output.txt
echo "Hello" | ${PROJ1} -x >> output.txt
printf "\xff\x00" | ${PROJ1} -x >> output.txt
printf "Ahoj\0Slovo\nXY\n" | ${PROJ1} -S 3 >> output.txt
echo "48656c6c0a" | ${PROJ1} -r >> output.txt
echo "00ff00ff" | ${PROJ1} -r | ${PROJ1} -x >> output.txt
echo "" >> output.txt
printf "Ahoj\0Slovo\nXY\n" | ${PROJ1} -S 0 2>> output.txt
printf 'Ahoj\0Slovo\nXY\n' | ${PROJ1} -S 43423 2>> output.txt
echo 'Hello, world! Ahoj svete!' | ${PROJ1} -s 14dffd -n 5fdfd 2>> output.txt
echo 'Hello, world! Ahoj svete!' | ${PROJ1} -s 23 -n -323 2>> output.txt
echo 'Příliš žluťoučký kůň úpěl ďábelské ódy.' | ${PROJ1} -x | ${PROJ1} -r >> output.txt
printf 'Lorem ipsum\0dolor\n\0sit\n\0\namet,\n\0 consectetur adipiscing elit.\n\n\n' | ${PROJ1} -S 4 >> output.txt
printf 'Lorem ipsum\0dolor\n\0sit\n\0\namet,\n\0 consectetur adipiscing elit.\n\n\n' | ${PROJ1} -S 4 | ${PROJ1} -x | ${PROJ1} -r >> output.txt
echo 'Příliš žluťoučký kůň úpěl ďábelské ódy.' | ${PROJ1} >> output.txt
echo 'Ahoj, jak se máš?' | ${PROJ1} >> output.txt
echo 'Ahoj, jak se máš?' | ${PROJ1} -s -n 2>> output.txt
echo 'Ahoj, jak se máš?' | ${PROJ1} -s 5 >> output.txt
echo 'Ahoj, jak se máš?' | ${PROJ1} -s 5 -n 5 >> output.txt
echo 'Ahoj, jak se máš?' | ${PROJ1} -n 8 >> output.txt
echo 'Ahoj, jak se máš?' | ${PROJ1} -n 200000 -s 3 >> output.txt
printf 'Hello, world!\0Ahoj svete!\n\0AP\nABCD\n' | ${PROJ1} -S 3 >> output.txt
echo '48 65 6c6c6f a' | ${PROJ1} -r >> output.txt
echo '' | ${PROJ1} >> output.txt
printf '' | ${PROJ1} >> output.txt
echo '' | ${PROJ1} -s 23 -n 2 >> output.txt
printf '' | ${PROJ1} -s 23 -n 2 >> output.txt
echo '' | ${PROJ1} -S 22 >> output.txt
printf '' | ${PROJ1} -S 22 >> output.txt
echo '' | ${PROJ1} -r >> output.txt
printf '' | ${PROJ1} -r >> output.txt
echo '' | ${PROJ1} -x >> output.txt
printf '' | ${PROJ1} -x >> output.txt
printf '\n\n\n\0\n\n\0\n\n\0\n' | ${PROJ1} -S 1 >> output.txt
printf '\n\n\na\0\na\n\0a\n\na\0\n' | ${PROJ1} -S 1 >> output.txt
printf '\n\n\na\0\na\n\0a\n\na\0\n' | ${PROJ1} -S 2 >> output.txt
printf 'Lorem ipsum' | ${PROJ1} -S 3 >> output.txt
