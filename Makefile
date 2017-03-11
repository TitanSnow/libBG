all: build/libbg.a
prepare:
	-mkdir build
build/libbg.a: src/bigint.cpp src/bigint.h src/fft.h src/fft.tcc
	$(CXX) -c src/bigint.cpp -o build/bigint.o -O3
	ar rc build/libbg.a build/bigint.o
	rm build/bigint.o
clean:
	-rm build/*
testadd: build/libbg.a test/badd.cpp test/test.h test/test.py src/bigint.h
	$(CXX) test/badd.cpp build/libbg.a -o test/testprogadd -Isrc -Itest
	cd test;./test.py add
	-rm test/testprogadd
testsub: build/libbg.a test/bsub.cpp test/test.h test/test.py src/bigint.h
	$(CXX) test/bsub.cpp build/libbg.a -o test/testprogsub -Isrc -Itest
	cd test;./test.py sub
	-rm test/testprogsub
testmul: build/libbg.a test/bmul.cpp test/test.h test/test.py src/bigint.h
	$(CXX) test/bmul.cpp build/libbg.a -o test/testprogmul -Isrc -Itest
	cd test;./test.py mul
	-rm test/testprogmul
testdiv: build/libbg.a test/bdiv.cpp test/test.h test/test.py src/bigint.h
	$(CXX) test/bdiv.cpp build/libbg.a -o test/testprogdiv -Isrc -Itest
	cd test;./test.py div
	-rm test/testprogdiv
testmod: build/libbg.a test/bmod.cpp test/test.h test/test.py src/bigint.h
	$(CXX) test/bmod.cpp build/libbg.a -o test/testprogmod -Isrc -Itest
	cd test;./test.py mod
	-rm test/testprogmod
test: testadd testsub testmul testdiv testmod
single: build/bigint-single.cpp
build/bigint-single.cpp: buildtool/node buildtool/include.js src/bigint.h src/bigint.cpp
	cd src;../buildtool/node ../buildtool/include.js bigint.cpp > ../build/bigint-single.cpp;cd ..
.PHONY: all clean prepare testadd testsub testmul testdiv testmod test single
