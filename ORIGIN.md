# Build

```bash
make prepare
make
```
If you have [xmake](https://github.com/tboox/xmake), or you're not using UNIX-like OS, or you wanna dynamic library, you could
```bash
xmake
```
Any compiler that supports C++98 is fine. But I suggest use VS201x instead of VS200x.

## Linking to your project

libBG supports both static and dynamic linking. Default is to be compiled as static library. If you wanna dynamic library, configure xmake as this:
```bash
xmake f -k shared # set build kind
xmake             # this is build step
```
After compiling, you may get static library named <code>libbg.a</code> on Linux or <code>bg.lib</code> on Windows, or shared library named <code>libbg.so</code> on Linux or <code>bg.dll</code> on Windows.

Get <code>src/bigint.h</code> into your include dir, then
```C++
#include "bigint.h"
// ... Your code ..
```
Link your program with libBG while compiling. This step might be vary between different platform and compiler. You might be interested in <code>xmake package</code> and use xmake in your project so that everything would be same crossing platforms.

[![Build Status](https://travis-ci.org/TitanSnow/libBG.svg?branch=master)](https://travis-ci.org/TitanSnow/libBG)
[![Build status](https://ci.appveyor.com/api/projects/status/sn4qgh654fs6u2nm?svg=true)](https://ci.appveyor.com/project/TitanSnow/libbg)

# [Contributing](CONTRIBUTING.md)

# APIs
*Note: APIs list below may be out of date. Check header file to know details*

* [Description](#description)   
* [Operators](#operators)
  * [Addition](#addition)
  * [Subtraction](#subtraction)
  * [Multiplication](#multiplication)
  * [Division](#division)
  * [Allocation](#allocation)
  * [Comparison](#comparison)
  * [Streaming operators](#streaming-operators)
* [Methods](#methods)
  * [clear](#clear)
  * [abs](#abs)
  * [digits](#digits)
  * [trailing_zeros](#trailing_zeros)
* [Functions](#functions)
  * [abs](#absbigint)
  * [to_string](#to_stringbigint)

# Description
libBG provides math operations for arbitrarily large numbers. You know the limit is reached when your computer freezes.

# Operators
## Addition
```C++
Dodecahedron::Bigint a,b,c;
c = a + b;
c += a;
c = a + 6;
c += 6;
```
## Subtraction
```C++
Dodecahedron::Bigint a,b,c;
c = a - b;
c -= a;
```
## Multiplication
```C++
Dodecahedron::Bigint a,b,c;
c = a * b;
c *= a;
c = a * 6;
c *= 6;
```
## Division
```C++
Dodecahedron::Bigint a,b,c;
c = a / b;
c /= a;
c = a / 6;
c /= 6;
```
## Modulo
```C++
Dodecahedron::Bigint a,b,c;
c = a % b;
c %= a;
c = a % 6;
c %= 6;
```
## Allocation
```C++
Dodecahedron::Bigint a = 12345;
Dodecahedron::Bigint b;
b = 159753;
```
## Comparison
```C++
Dodecahedron::Bigint a = 159753;
Dodecahedron::Bigint b = 1634687496;

if(a == b) cout << "A is the same as B";
if(a < b) cout << "A is less than B";
if(a > b) cout << "A is larger than B";
if(a >= b) cout << "A is larger than B or equal to it";
if(a <= b) cout << "A is smaller than B or equal to it";
```
## Stream operators
```C++
Dodecahedron::Bigint a,b;
cin >> a >> b;
cout << a*b;
```
# Methods
## clear()
Clears the Dodecahedron::Bigint, essentially making it equal to 0.
```C++
Dodecahedron::Bigint a = 4558;
cout << a.pow(486);;  // ~1.46 * 10^1778
a.clear();
cout << a; //0
```
## abs()
Absolute value.
```C++
Dodecahedron::Bigint a = -4558;
cout << a.abs() // 4558
```
## digits()
Returns the number of digits.
```C++
Dodecahedron::Bigint a = 4558;
cout << a.pow(486).digits(); // 4558^486 = 1779 digit number
```
## trailing_zeros()
Returns the number of trailing zeros.
```C++
Dodecahedron::Bigint a = 4558;
a.pow(486);
cout << a.trailing_zeros(); //972
```
# Functions
## abs(Bigint)
Same as [abs](#abs), but returns a new instance;
```C++
Dodecahedron::Bigint a = -455897864531248;
cout << abs(a) // 455897864531248
```
## to_string(Bigint)
Converts the big integer to a string.
```C++
string str;
Dodecahedron::Bigint a = 455897864531248;
str = to_string(a);
```
