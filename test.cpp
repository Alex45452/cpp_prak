#include <cmath>
#include <iostream>


// using namespace std;


class complex
{
    private:
        double re, im;
    public:
        complex() {re = im = 0.0;};
        complex(double _re, double _im) {
            re = _re;
            im = _im;
        }
        double abs()
        {
            return std::sqrt(re*re+im*im);
        };

};

// double complex::abs()
// {
//     return std::sqrt(this->re*this->re+this->im*this->im);
// };
int main(){
    complex c1(1.0,0.0);
    complex c2 = complex(1.0,0.0);
    complex c3;
    std::printf("%f %f %f",c1.abs(),c2.abs(),c3.abs());
}