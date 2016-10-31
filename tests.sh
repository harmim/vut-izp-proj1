#!/bin/bash

echo "Hello, world! Ahoj svete!" | ./proj1 >> output.txt
echo "Ahoj" | ./proj1 >> output.txt
echo "Hello, world! Ahoj svete!" | ./proj1 -s 14 -n 5 >> output.txt
echo "Hello" | ./proj1 -x >> output.txt
printf "\xff\x00" | ./proj1 -x >> output.txt
printf "Ahoj\0Slovo\nXY\n" | ./proj1 -S 3 >> output.txt
echo "48656c6c0a" | ./proj1 -r >> output.txt
echo "00ff00ff" | ./proj1 -r | ./proj1 -x >> output.txt
echo "" >> output.txt
printf "Ahoj\0Slovo\nXY\n" | ./proj1 -S 0 2>> output.txt
printf 'Ahoj\0Slovo\nXY\n' | ./proj1 -S 43423 2>> output.txt
echo 'Hello, world! Ahoj svete!' | ./proj1 -s 14dffd -n 5fdfd 2>> output.txt
echo 'Hello, world! Ahoj svete!' | ./proj1 -s 23 -n -323 2>> output.txt
echo 'Příliš žluťoučký kůň úpěl ďábelské ódy.' | ./proj1 -x | ./proj1 -r >> output.txt
printf 'Lorem ipsum\0dolor\n\0sit\n\0\namet,\n\0 consectetur adipiscing elit.\n\n\n' | ./proj1 -S 4 >> output.txt
printf 'Lorem ipsum\0dolor\n\0sit\n\0\namet,\n\0 consectetur adipiscing elit.\n\n\n' | ./proj1 -S 4 | ./proj1 -x | ./proj1 -r >> output.txt
echo 'Příliš žluťoučký kůň úpěl ďábelské ódy.' | ./proj1 >> output.txt
