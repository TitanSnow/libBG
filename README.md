# libBG
A *lightwight* *high-speed* *good-designed* big interger library for C++ with *FFT*

[![Build Status](https://travis-ci.org/TitanSnow/libBG.svg?branch=master)](https://travis-ci.org/TitanSnow/libBG)
[![Build status](https://ci.appveyor.com/api/projects/status/sn4qgh654fs6u2nm?svg=true)](https://ci.appveyor.com/project/TitanSnow/libbg)
[![codecov](https://codecov.io/gh/TitanSnow/libBG/branch/master/graph/badge.svg)](https://codecov.io/gh/TitanSnow/libBG)

[More details](ORIGIN.md)

## Lightwight
### Total about 20KB
20KB source code with complete biginteger implement. About 40KB<sup>^</sup> compiled. Be able to plug in every project running everywhere.

<sub>^: g++ on linux with -Os</sub>

### No dependence
Pure *C++98* code. No dependence. Can be compiled with any standard-supported compiler as static or shared library within one step.

### Pack as single
<code>make single</code> generate single file output and can be embedded into any code. Just copy it then enjoy it.

## High Speed
### Faster than Python<sup>^</sup>
For random numbers with 10K digits:

  * 0.06s / 10K times addition
  * 0.196s / 10K times subtraction
  * 33.5s / 10K times multiplication
  * 0.116s / 10K times division
  * 0.256s / 10K times modulo

<sub>^: Runs on travisCI. Data from test #132.1 g++ on linux with -Ofast. Not accurate</sub>

### FFT inside<sup>^</sup>
Fascinating *Fast Fourier Transformation* (FFT) used in multiplication. Deal with huge numbers with *O(nlgn)*

<sub>^: smart enable</sub>

### Great Algorithm
Division uses *Double Division Algorithm*. Power uses map to speed. Everything is for speed.

## Good Designed
### It is a Class
Nothing else, just a C++ class with beautiful interface.

### It feels like *Native*
Addition is just <code>a+b</code>. Nothing is against natural thinking.

### It is Simple
Wanna to see [detail](ORIGIN.md)?
