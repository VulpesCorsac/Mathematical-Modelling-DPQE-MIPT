#ifndef FASTDISCRETEFOURIERTRANSFORM_HPP_INCLUDED
#define FASTDISCRETEFOURIERTRANSFORM_HPP_INCLUDED

#include <vector>
#include <complex>

template < class Type >
class FDFT {
private:
    std::vector < std::complex < Type > > Signal;
    std::vector < std::complex < Type > > Fourier;

    Type PI(void) {
        return 3.14159265358979;
    }

    void fdft_slow(std::vector < std::complex < Type > > &a, bool invert = false) {
        size_t n = (int) a.size();
        if (n == 1)
            return;
        std::vector < std::complex < Type > > a0(n/2);
        std::vector < std::complex < Type > > a1(n/2);
        for (size_t i = 0, j = 0; i < n; i += 2, j++) {
            a0[j] = a[i];
            a1[j] = a[i+1];
        }

        fdft_slow(a0, invert);
        fdft_slow(a1, invert);

        Type ang = 2*PI()/n * (invert ? -1 : 1);
        std::complex < Type > w(1);
        std::complex < Type > wn(cos(ang), sin(ang));
        for (size_t i = 0; i < n/2; i++) {
            a[i] = a0[i] + w*a1[i];
            a[i + n/2] = a0[i] - w*a1[i];
            if (invert) {
                a[i] /= 2;
                a[i + n/2] /= 2;
            }
            w *= wn;
        }

    }

    void fdft(std::vector < std::complex < Type > > &a, bool invert = false) {
        fdft_slow(a, invert);
        return;
    }

public:
    FDFT() {
        Signal.clear();
        Fourier.clear();
    }

    ~FDFT() {
        Signal.clear();
        Fourier.clear();
    }

    void Set_Signal(const std::vector < std::complex < Type > > &_Signal) {
        Signal = _Signal;
        return;
    }

    std::vector < std::complex < Type > > Get_Signal(void) const{
        return std::vector < std::complex < Type > > (Signal);
    }

    void Set_Fourier(const std::vector < std::complex < Type > > &_Fourier) {
        Fourier = _Fourier;
        return;
    }

    std::vector < std::complex < Type > > Get_Fourier(void) const {
        return std::vector < std::complex < Type > > (Fourier);
    }

    bool Run_FDFT(void) {
        if (!Signal.size())
            return false;
        Fourier = Signal;
        fdft(Fourier, false);
        return true;
    }

    bool Run_IFDFT(void) {
        if(!Fourier.size())
            return false;
        Signal = Fourier;
        fdft(Signal, true);
        return true;
    }

    void Fourier_test(void) {
        double twopi = 2*PI();
        std::complex < Type > ci (0, 1);
        int nx;
        std::cout << "Nx = ";
        std::cin >> nx;
        std::complex < Type > w0 = exp(-ci*twopi/std::complex < Type > (nx, 0));
        std::complex < Type > q = 1.01 + ci*0.02;

        std::vector < std::complex < Type > > y, fy, _y, _fy;
        y.resize(nx);
        fy.resize(nx);
        for (int m = 0; m < nx; m++) {
            y[m] = pow(q, m);
            fy[m] = (pow(q, nx) - 1.0) / (q*pow(w0, m) - 1.0) / std::complex < Type > (nx, 0);
        }
        for (int m = 0; m < 4; m++)
            std::cout << "m = " << m << ",  y = " <<  y[m] << ", fy = " << fy[m] << std::endl;

        Set_Signal(y);
        Run_FDFT();
        _fy = Get_Fourier();
        Run_IFDFT();
        _y = Get_Signal();

        std::cout << "Calculated:" << std::endl;
        for (int m = 0; m < 4; m++)
            std::cout << "m = " << m << ",  y = " <<  y[m] << ", fy = " << fy[m] << std::endl;

    }
};

#endif // FASTDISCRETEFOURIERTRANSFORM_HPP_INCLUDED
