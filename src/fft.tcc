#include <cmath>
#include <complex>
#include <vector>
#include <algorithm>
#include <iterator>
namespace Dodecahedron
{
class __fft
{
    typedef double real;
    typedef std::complex<real> cp;
    typedef std::vector<cp> arr;
    arr a,b,w,tt;
    int n;
    const real pi;
    int cpy(arr &d,Bigint const &s)
    {
        d.clear();
        for(std::vector<int>::const_iterator it(s.number.begin()); it!=s.number.end(); ++it)
        {
            d.push_back(cp(*it%10000,0));
            d.push_back(cp(*it/10000,0));
        }
        return d.size();
    }
    void dft(arr &a,int s,int t)
    {
        if((n>>t)==1) return;
        dft(a,s,t+1);
        dft(a,s+(1<<t),t+1);
        for(int i=0; i<(n>>(t+1)); ++i)
        {
            int p=(i<<(t+1))+s;
            cp wt=w[i<<t]*a[p+(1<<t)];
            tt[i]=a[p]+wt;
            tt[i+(n>>(t+1))]=a[p]-wt;
        }
        for(int i=0; i<(n>>t); ++i)
            a[(i<<t)+s]=tt[i];
    }
    long long round(real x)
    {
        // WARNING: only works with positive number
        return x+0.5;
    }
    void back(Bigint &cc)
    {
        std::vector<long long> c(n+1);
        for(int i=0; i<n; ++i)
        {
            c[i]+=round(a[i].real()/n);
            c[i+1]=c[i]/10000;
            c[i]%=10000;
        }
        if(!c.empty())
        {
            long long incs;
            while((incs=c.back())>=10000)
            {
                c.back()%=10000;
                c.push_back(incs/10000);
            }
        }
        while(!c.empty()&&!c.back())
            c.pop_back();
        cc.number.clear();
        for(std::vector<long long>::const_iterator it(c.begin()); it<c.end(); it+=2)
        {
            int tmp1=*it;
            int tmp2=it+1==c.end()?0:*(it+1);
            cc.number.push_back(tmp1+tmp2*10000);
        }
    }
public:
    __fft():pi(std::acos((real)-1.0)) {}
    void set(Bigint const &a,Bigint const &b)
    {
        n=1;
        int lla=cpy(this->a,a);
        int llb=cpy(this->b,b);
        while((n>>1)<lla)n+=n;
        while((n>>1)<llb)n+=n;
        for(int i=0; i<n; ++i)
            w.push_back(cp(std::cos(pi*2*i/n),std::sin(pi*2*i/n)));
        this->a.resize(n);
        this->b.resize(n);
        tt.resize(n);
    }
    void mul(Bigint &c)
    {
        dft(a,0,0);
        dft(b,0,0);
        for(int i=0; i<n; ++i)
            a[i]=a[i]*b[i];
        for(int i=0; i<n; ++i)
            w[i]=cp(w[i].real(),-w[i].imag());
        dft(a,0,0);
        back(c);
    }
};
void __fft_mul(Bigint const &a,Bigint const &b,Bigint &c)
{
    __fft f;
    f.set(a,b);
    f.mul(c);
}
}
