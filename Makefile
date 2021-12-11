.PHONY: execs all

all: build run

build:
	cmake . -B build
	make -j4 -C build

run:
	build/bin/day11 build/data/day11-data.txt
