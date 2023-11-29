COMPILER := clang++

.PHONY: all build clean

all: build

build: gcd

gcd: main.o
	$(COMPILER) --std=c++20 -Wall -O3 main.o -o gcd

main.o: main.cpp
	$(COMPILER) --std=c++20 -Wall -O3 -c main.cpp -o main.o

clean:
	git clean -fdx -e *.swp
