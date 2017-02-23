all: build/libDodecahedronBigint.a
prepare:
	-mkdir build
build/libDodecahedronBigint.a: src/bigint.cpp src/bigint.h
	$(CXX) -c src/bigint.cpp -o build/bigint.o
	ar rc build/libDodecahedronBigint.a build/bigint.o
	rm build/bigint.o
clean:
	-rm build/*
testadd: build/libDodecahedronBigint.a test/badd.cpp test/test.h test/test.py src/bigint.h
	$(CXX) test/badd.cpp build/libDodecahedronBigint.a -o test/testprogadd -Isrc -Itest
	cd test;./test.py add
	-rm test/testprogadd
testsub: build/libDodecahedronBigint.a test/bsub.cpp test/test.h test/test.py src/bigint.h
	$(CXX) test/bsub.cpp build/libDodecahedronBigint.a -o test/testprogsub -Isrc -Itest
	cd test;./test.py sub
	-rm test/testprogsub
test: testadd testsub
.PHONY: all clean prepare testadd testsub test
