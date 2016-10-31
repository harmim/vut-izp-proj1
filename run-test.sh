#!/bin/bash

make main
	
if [ ! -f proj1 ]; then 
	echo "Chyba pri prekladu!"
	exit 1
fi

if [ -f output.txt ]; then
	rm output.txt
fi

chmod +x tests.sh
./tests.sh

if [ ! -f output.txt ]; then
	echo "Nastala chyba pri spusteni testu!"
	exit 1
fi

diff -u output.txt pattern.txt
