# libBG
A *lightwight* *high-speed* *good-designed* big interger library for C++ with *FFT*

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

  * 7.52425289154s / 10K times addition
  * 7.51592826843s / 10K times subtraction
  * 33.2661168575s / 10K times multiplication
  * 11.1092059612s / 10K times division
  * 12.4199271202s / 10K times modulo

<sub>^: Runs on travisCI. Data from test #99.1 g++ on linux with -O3 & -ffast-math. Not accurate</sub>

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
