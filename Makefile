all: build/libDodecahedronBigint.a
prepare:
	-mkdir build
build/libDodecahedronBigint.a: src/bigint.cpp src/bigint.h
	$(CXX) -c src/bigint.cpp -o build/bigint.o -O3
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
testmul: build/libDodecahedronBigint.a test/bmul.cpp test/test.h test/test.py src/bigint.h
	$(CXX) test/bmul.cpp build/libDodecahedronBigint.a -o test/testprogmul -Isrc -Itest
	cd test;./test.py mul
	-rm test/testprogmul
test: testadd testsub testmul
.PHONY: all clean prepare testadd testsub testmul test
