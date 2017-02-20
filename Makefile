all: build/libDodecahedronBigint.a
prepare:
	-mkdir build
build/libDodecahedronBigint.a: src/bigint.cpp src/bigint.h
	$(CXX) -c src/bigint.cpp -o build/bigint.o
	ar rc build/libDodecahedronBigint.a build/bigint.o
	rm build/bigint.o
clean:
	-rm build/*
.PHONY: all clean prepare
