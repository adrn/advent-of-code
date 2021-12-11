.PHONY: execs all

all: build run

build:
	cmake . -B build
	make -j4 -C build

run:
	build/bin/day10 build/data/day10-data.txt
