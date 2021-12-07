.PHONY: execs all

all: build run

build:
	cmake . -B build; make -j4 -C build

run:
	build/bin/day07 build/data/day07-data.txt
