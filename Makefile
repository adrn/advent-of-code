.PHONY: execs all

all: build run

build:
	cmake . -B build
	make -j4 -C build

run:
	build/bin/day08 build/data/day08-data.txt
