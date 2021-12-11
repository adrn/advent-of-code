.PHONY: execs all

all: build run

build:
	cmake . -B build
	make -j4 -C build

run:
	build/bin/day09 build/data/day09-data.txt
