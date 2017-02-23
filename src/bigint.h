#ifndef DODECAHEDRON_BIGINT_H_
#define DODECAHEDRON_BIGINT_H_

#include <vector>
#include <iostream>
#include <map>

namespace Dodecahedron
{
class Bigint
{
private:
    std::vector<int> number;
    // don't modify this directly through const. use flip_positive
    mutable bool positive;
    int base;
    unsigned int skip;
    static const int default_base=10000;
    static const int default_digits_per_element=4;

public:
    //Constructors
    Bigint();
    Bigint(long long);
    Bigint(std::string);
    Bigint(const Bigint& b);

    //Adding
    Bigint operator+(Bigint const &) const;
    Bigint &operator+=(Bigint const &);

    //Subtraction
    Bigint operator-(Bigint const &) const;
    Bigint &operator-=(Bigint const &);

    //Multiplication
    Bigint operator*(Bigint const &) const;
    Bigint &operator*=(Bigint const &);

    //Compare
    bool operator<(const Bigint &) const;
    bool operator>(const Bigint &) const;
    bool operator<=(const Bigint &) const;
    bool operator>=(const Bigint &) const;
    bool operator==(const Bigint &) const;
    bool operator!=(const Bigint &) const;

    //Allocation
    Bigint operator=(const long long &);

    //Input&Output
    friend std::istream &operator>>(std::istream &, Bigint &);
    friend std::ostream &operator<<(std::ostream &, Bigint const &);

    //Helpers
    void clear();
    Bigint &abs();

    //Trivia
    int digits() const;
    int trailing_zeros() const;
private:
    int segment_length(int) const;
    int compare(Bigint const &) const; //0 a == b, -1 a < b, 1 a > b
    void flip_positive() const;
};

Bigint abs(Bigint);
std::string to_string(Bigint const &);
}

#endif
