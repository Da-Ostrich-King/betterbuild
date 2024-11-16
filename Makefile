# makefile is temporary as a bootstrap

all:
	g++ --std=c++20 src/* -o build/bin/default/fuck\ everything

debug:
	g++ --std=c++20 src/* -o build/bin/debug/fuck\ everything -D debug -g
