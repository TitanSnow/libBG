#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <cstdio>
#include <cctype>
// included bigint.h
#include "fft.h"

namespace Dodecahedron
{

//Constructor
Bigint::Bigint()
        : positive(true),
          force_fft(false)
          {}
Bigint::Bigint(const Bigint &b)
        : number(b.number),
          positive(b.positive),
          force_fft(false)
          {}
Bigint::Bigint(long long value)
:force_fft(false){
    if (value < 0) {
        positive = false;
        value *= -1;
    } else {
        positive = true;
    }

    while (value) {
        number.push_back((int) (value % Bigint::default_base));
        value /= Bigint::default_base;
    }
}

Bigint::Bigint(const std::string &stringInteger)
:force_fft(false){
    int size = stringInteger.length();

    positive = (stringInteger[0] != '-');

    while (true) {
        if (size <= 0) break;
        if (!positive && size <= 1) break;

        int length = 0;
        int num = 0;
        int prefix = 1;
        for (int i(size - 1); i >= 0 && i >= size - Bigint::default_digits_per_element; --i) {
            if (stringInteger[i] < '0' || stringInteger[i] > '9') break;
            num += (stringInteger[i] - '0') * prefix;
            prefix *= 10;
            ++length;
        }
        number.push_back(num);
        size -= length;
    }
    delete_precode_zero();
}

//Adding
Bigint Bigint::operator+(Bigint const &b) const
{
    Bigint c = *this;
    c += b;

    return c;
}

Bigint &Bigint::operator+=(Bigint const &b)
{
    if (positive && !b.positive) {
        b.flip_positive();
        *this -= b;
        b.flip_positive();
        return *this;
    }
    if (!positive && b.positive) {
        flip_positive();
        *this -= b;
        flip_positive();
        return *this;
    }
    if (!positive && !b.positive) {
        flip_positive();
        b.flip_positive();
        *this += b;
        flip_positive();
        b.flip_positive();
        return *this;
    }
    std::vector<int>::iterator
        it1 = number.begin();
    std::vector<int>::const_iterator
        it2 = b.number.begin();
    int sum = 0;
    while (it1 != number.end() || it2 != b.number.end()) {
        if (it1 != number.end()) {
            sum += *it1;
        } else {
            number.push_back(0);
            it1 = number.end()-1;
        }
        if (it2 != b.number.end()) {
            sum += *it2;
            ++it2;
        }
        *it1 = sum % Bigint::default_base;
        ++it1;
        sum /= Bigint::default_base;
    }
    if (sum) number.push_back(1);

    return *this;
}

//Subtraction
Bigint Bigint::operator-(Bigint const &b) const
{
    Bigint c = *this;
    c -= b;

    return c;
}

Bigint &Bigint::operator-=(Bigint const &b)
{
    if (!positive || !b.positive){
        b.flip_positive();
        *this += b;
        b.flip_positive();
        return *this;
    }
    std::vector<int>::iterator
        it1 = number.begin();
    std::vector<int>::const_iterator
        it2 = b.number.begin();
    int dif = 0;
    while (it1 != number.end() || it2 != b.number.end()) {
        if (it1 != number.end()) {
            dif += *it1;
            ++it1;
        } else {
            number.push_back(0);
            it1 = number.end();
        }
        if (it2 != b.number.end()) {
            dif -= *it2;
            ++it2;
        }
        if (dif < 0) {
            *(it1 - 1) = (dif + Bigint::default_base) % Bigint::default_base;
            dif = -1;
        } else {
            *(it1 - 1) = dif % Bigint::default_base;
            dif /= Bigint::default_base;
        }
    }
    if (dif < 0) {
        std::string newstr("1");
        int c_seg = number.size();
        while(c_seg--)
            for(int i=1; i<Bigint::default_base; i*=10)
                newstr += "0";
        *this = Bigint(newstr) - *this;
        positive = false;
    }
    delete_precode_zero();

    return *this;
}

//Multiplication
static bool is_fft_needed(unsigned long long a, unsigned long long b)
{
#   ifdef BIGINT_DISABLE_FFT
    return false;
#   endif
    return a * b >
#   ifdef BIGINT_FFT_TRIGGER
        BIGINT_FFT_TRIGGER
#   else
        1024 * 1024
#   endif
    ;
}
Bigint Bigint::operator*(Bigint const &b) const
{
    if (force_fft || b.force_fft || is_fft_needed(this->number.size(), b.number.size()))
    {
        Bigint c;
        bool result_positive = !(positive ^ b.positive);
        __fft_mul(*this, b, c);
        c.positive = result_positive;
        return c;
    }

    const long long max_longlong =
        static_cast<long long>(
            static_cast<unsigned long long>(
                static_cast<long long>(-1)
            ) >> 1
        );
    const long long update_limit =
        max_longlong - static_cast<long long>(Bigint::default_base - 1) * (Bigint::default_base - 1);
    bool update_flag = false;

    Bigint const &a = *this;
    Bigint c;
    std::vector<long long> number(a.number.size()+b.number.size());
    for(std::vector<int>::const_iterator
        it1(a.number.begin()); it1!=a.number.end(); ++it1){
        update_flag = false;
        for(std::vector<int>::const_iterator
            it2(b.number.begin()); it2!=b.number.end(); ++it2)
            update_flag = ((
                number[
                    (it1 - a.number.begin()) +
                    (it2 - b.number.begin()) ]
                += static_cast<long long>(*it1) * *it2
            ) > update_limit || update_flag);
        if(update_flag)
            for(std::vector<long long>::iterator it(number.begin() + 1);
                it < number.end(); ++it){
                *it += *(it - 1) / Bigint::default_base;
                *(it - 1) %= Bigint::default_base;
            }
    }
    if(!update_flag)
        for(std::vector<long long>::iterator it(number.begin() + 1);
            it < number.end(); ++it){
            *it += *(it - 1) / Bigint::default_base;
            *(it - 1) %= Bigint::default_base;
        }
    c.positive = !(a.positive ^ b.positive);
    std::copy(number.begin(), number.end(), std::back_inserter(c.number));
    c.delete_precode_zero();
    return c;
}

Bigint &Bigint::operator*=(Bigint const &b)
{
    return *this = *this * b;
}

//Division
static std::string to_string(const int value)
{
    char str[16];
    std::sprintf(str, "%d", value);
    return str;
}

void sub_number(Bigint const &p, Bigint const &q, Bigint &c){

      std::string tmpx0, tmpx1, tmpx3;
      int window_size = std::min(p.digits(), q.digits());
      int last_i_iterator;
      std::vector<int>::const_reverse_iterator i(p.number.rbegin());

      while(i!=p.number.rend() && window_size>0){

          tmpx0 = to_string(*i);
          int ssss = tmpx0.size();
          if(i!=p.number.rbegin() && ssss<Bigint::default_digits_per_element){
              tmpx0 = std::string(Bigint::default_digits_per_element-ssss,'0') + tmpx0;
          }

          if(window_size - ssss < 0){
              tmpx3=tmpx0;
              tmpx0="";
              for(int i=0;i<window_size;i++){
                  tmpx0+=tmpx3[i];
                  last_i_iterator=i;
              }
              window_size = window_size - tmpx0.size();
              tmpx1 += tmpx0;
          }
          else{
              window_size = window_size - tmpx0.size();
              tmpx1 += tmpx0;
              ++i;
          }
      }

      c = tmpx1;

      if(i!=p.number.rend() && c<q){
          if(tmpx3.size()!=0){
              window_size++;
              tmpx0 = tmpx3[last_i_iterator+1];
              tmpx1 += tmpx0;
              c=tmpx1;
          }
          else{
              window_size++;
              tmpx0 = to_string(*i);
              if(i!=p.number.rbegin() && tmpx0.size()<Bigint::default_digits_per_element){
                  tmpx0 = std::string(Bigint::default_digits_per_element-tmpx0.size(),'0') + tmpx0;
              }
              tmpx0 = tmpx0[0];
              tmpx1 += tmpx0;
              c=tmpx1;
          }

      }
}

void divide(Bigint p, Bigint const &q, Bigint &sum_quotient, Bigint &sub_p){

    /*Algorithm used is "Double division algorithm"*/

    const int look_up_table_size=4;
    Bigint look_up[look_up_table_size]={
        q,
        q*2,
        q*4,
        q*8
    };
    bool done_flag=false;
    int tmp_quotient; Bigint *ptmpx1, tmpx2;
    int qdigits = q.digits();

    while(true){

        sub_number(p, q, sub_p);  // cut a portion from the dividened equal in size with the divisor

        for(int i=0;i<look_up_table_size;i++){ // looking in the look_up table

            if (sub_p < look_up[i]){
                if (i){
                    ptmpx1 = look_up+i-1;
                    tmp_quotient = 1<<(i-1);
                    break;
                } else {

                    if(qdigits >= p.digits()){
                        done_flag=true;
                        break;
                    }

                }
            } else if((i==look_up_table_size-1 && sub_p>look_up[i]) || sub_p==look_up[i]){
                ptmpx1 = look_up+i;
                tmp_quotient= 1<<i;
                break;
            }
        }

        if (done_flag)
            break;

        std::string temppp(p.digits()-(sub_p.digits()),'0');
        temppp="1"+temppp;
        tmpx2=temppp;

        if(sum_quotient.digits()==0)
            sum_quotient=tmpx2*tmp_quotient;
        else
            sum_quotient+=tmpx2*tmp_quotient;

        p-=*ptmpx1*tmpx2;

    }

}

static void check_divisor(Bigint const &b)
{
    if (b == 0)
        throw Bigint::arithmetic_error("Divide by zero");
}

Bigint Bigint::operator/(Bigint const &b) const
{
    check_divisor(b);
    if (*this == 0) return 0;
    bool result_positive = !(positive ^ b.positive);
    bool origin_positive_this = positive;
    bool origin_positive_b    = b.positive;
    positive = true;
    b.positive = true;
    Bigint a1, a2;
    divide(*this, b, a1, a2);
    Bigint &ans = a1;
    positive = origin_positive_this;
    b.positive = origin_positive_b;
    ans.positive = result_positive;
    return ans;
}

Bigint &Bigint::operator/=(Bigint const &b)
{
    return *this = *this / b;
}

Bigint Bigint::operator%(Bigint const &b) const
{
    check_divisor(b);
    if (*this == 0) return 0;
    bool result_positive = positive;
    bool origin_positive_this = positive;
    bool origin_positive_b    = b.positive;
    positive = true;
    b.positive = true;
    Bigint a1, a2;
    divide(*this, b, a1, a2);
    Bigint &ans = a2;
    positive = origin_positive_this;
    b.positive = origin_positive_b;
    ans.positive = ans==0 ? true : result_positive;
    return ans;
}

Bigint &Bigint::operator%=(Bigint const &b)
{
    return *this = *this % b;
}

//Power

Bigint Bigint::pow(int const power, std::map<int, Bigint> &lookup)
{
    if (power == 1) return *this;
    if (lookup.count(power)) return lookup[power];

    int closestPower = 1;
    while (closestPower < power) closestPower <<= 1;
    closestPower >>= 1;

    if (power == closestPower) lookup[power] = pow(power / 2, lookup) * pow(power / 2, lookup);
    else lookup[power] = pow(closestPower, lookup) * pow(power - closestPower, lookup);

    return lookup[power];
}

Bigint &Bigint::pow(int const power)
{
    if (!power) return *this = Bigint(1);
    std::map<int, Bigint> lookup;
    if (power % 2 == 0 && !positive) {
        positive = true;
    }
    *this = pow(power, lookup);

    return *this;
}

//Compare
int Bigint::compare(const Bigint &a) const //0 this == a || -1 this < a || 1 this > a
{
    if (positive && !a.positive) return 1;
    if (!positive && a.positive) return -1;

    int check = 1;
    if (!positive && !a.positive) check = -1;

    if (number.size() < a.number.size()) return -1 * check;
    if (number.size() > a.number.size()) return check;
    for (size_t i(number.size()); i > 0; --i) {
        if (number[i-1] < a.number[i-1]) return -1 * check;
        if (number[i-1] > a.number[i-1]) return check;
    }

    return 0; // ==
}

bool Bigint::operator<(Bigint const &b) const
{
    return compare(b) == -1;
}

bool Bigint::operator<=(const Bigint &b) const
{
    int compared = compare(b);

    return compared == 0 || compared == -1;
}

bool Bigint::operator>(const Bigint &b) const
{
    return compare(b) == 1;
}

bool Bigint::operator>=(const Bigint &b) const
{
    int compared = compare(b);

    return compared == 0 || compared == 1;
}

bool Bigint::operator==(Bigint const &b) const
{
    return compare(b) == 0;
}

bool Bigint::operator!=(Bigint const &b) const
{
    return ! (*this == b);
}

//Allocation
Bigint &Bigint::operator=(const long long a)
{
    return *this = Bigint(a);
}

//Trivia
int Bigint::digits() const
{
    int segments = number.size();

    if (segments == 0) return 0;

    int digits = Bigint::default_digits_per_element * (segments - 1);
    digits += segment_length(number.back());

    return digits;
}

int Bigint::trailing_zeros() const
{
    if (number.empty() || (number.size() == 1 && number[0] == 0)) return 1;

    int zeros = 0;
    std::vector<int>::const_iterator it = number.begin();
    if (number.size() > 1) {
        for (; it != number.end() - 1 && *it == 0; ++it) {
            zeros += Bigint::default_digits_per_element;
        }
    }
    int a = *it;
    while (a % 10 == 0 && a) {
        ++zeros;
        a /= 10;
    }

    return zeros;
}

//Helpers
void Bigint::clear()
{
    number.clear();
    positive = true;
}

Bigint &Bigint::abs()
{
    positive = true;

    return *this;
}

void Bigint::flip_positive() const
{
    // WARN: private use, must call as pair!!!
    positive = !positive;
}

void Bigint::delete_precode_zero()
{
    while (!number.empty() && !number.back())
        number.pop_back();
}

//Input&Output
std::ostream &operator<<(std::ostream &out, Bigint const &a)
{
    if (!a.number.size()) return out << 0;
    int i = a.number.size() - 1;
    for (; i>=0 && a.number[i] == 0; --i);

    if (i == -1) return out << 0;
    if (!a.positive) out << '-';

    std::vector<int>::const_reverse_iterator it = a.number.rbegin() + (a.number.size() - i - 1);

    out << *it++;
    for (; it != a.number.rend(); ++it) {
        for (int i(0), len = a.segment_length(*it); i < Bigint::default_digits_per_element - len; ++i) out << '0';
        if (*it) out << *it;
    }

    return out;
}


std::istream &operator>>(std::istream &in, Bigint &a)
{
    std::string str;
    int ch;
    if (!in)
    {
        a = 0;
        return in;
    }
    while (std::isspace(ch = in.get()));
    if (!in)
    {
        a = 0;
        return in;
    }
    if (ch == '-')
        str += (char) ch;
    else
        in.unget();
    while (std::isdigit(ch = in.get()))
        str += (char) ch;
    if (in) in.unget();
    if (str == "-")
    {
        a = 0;
        return in;
    }

    a = str;

    return in;
}

int Bigint::segment_length(int segment) const
{
    int length = 0;
    while (segment) {
        segment /= 10;
        ++length;
    }

    return length;
}

Bigint abs(Bigint value)
{
    return value.abs();
}

std::string to_string(Bigint const &value)
{
    std::ostringstream stream;
    stream << value;

    return stream.str();
}

Bigint factorial(int n)
{
    Bigint result = 1;
    if (n % 2) {
        result = n;
        --n;
    }
    int last = 0;
    for (; n >= 2; n -= 2) {
        result *= n + last;
        last += n;
    }

    return result;
}

Bigint pow(Bigint a, int const b)
{
    return a.pow(b);
}

}
