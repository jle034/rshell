all: 
	rm -rf bin
	mkdir bin
	g++ -Wall -Werror -ansi -pedantic src/main.cpp -o bin/rshell
	g++ -Wall -Werror -ansi -pedantic src/ls.cpp -o bin/ls

rshell:
	rm -rf bin
	mkdir bin
	g++ -Wall -Werror -ansi -pedantic src/main.cpp -o bin/rshell

ls:
	rm -rf bin
	mkdir bin
	g++ -Wall -Werror -ansi -pedantic src/ls.cpp -o bin/ls
