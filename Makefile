# makefile is temporary as a bootstrap

debug:
	g++ --std=c++20 src/* -o build/bin/debug/fuck\ everything -D debug

all:
	g++ --std=c++20 src/* -o build/bin/default/fuck\ everything -D debug