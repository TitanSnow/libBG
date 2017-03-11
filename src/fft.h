#include "bigint.h"
#ifndef DODECAHEDRON_FFT_H_
#define DODECAHEDRON_FFT_H_
namespace Dodecahedron
{
void __fft_mul(Bigint const &a,Bigint const &b,Bigint &c);
}
#include "fft.tcc"
#endif
