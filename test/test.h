#include"bigint.h"
#include<iostream>
#ifndef BIGINT_TEST_H
#define BIGINT_TEST_H
#define TWO_BIGINT_TEST_ONE(expr) \
int main(){ \
std::ios::sync_with_stdio(false); \
Dodecahedron::Bigint a,b; \
std::cin>>a>>b; \
std::cout<<(expr); \
return 0; \
}
#endif
