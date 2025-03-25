#include <cmath>
#include <cstdint>
#include <iostream>

using namespace std;

class BitString{
    private:
        unsigned int _hi;
        unsigned int _lo;
    public:
        BitString(const unsigned int hi,const unsigned int lo){_hi = hi; _lo = lo;}
        BitString(const unsigned int lo = 0){_lo = lo;_hi = 0;}
        // BitString(){_lo = 0;_hi = 0;}
        void Print() const;
        void ShiftLeft(const unsigned offset); //- сдвиг влево битового представления числа на offset бит
        void ShiftRight(const unsigned offset); //- сдвиг вправо битового представления числа на offset бит
        void NOT();                      //- операция битовой инверсии
        void AND(const BitString& b);  //- операция побитового И с числом b
        void OR(const BitString& b);  // - операция побитового ИЛИ с числом b
        void XOR(const BitString& b);  //- операция побитового исключающего ИЛИ с числом b
};

void BitString::Print() const{
    uint64_t ans;
    ans = _hi * pow(2,32);
    // ans <<= 32;
    ans += _lo;
    cout << ans << endl;

}
void BitString::ShiftLeft(const unsigned offset){
    unsigned int tmp;
    tmp = _lo;
    offset > 32 ? tmp <<= offset-32: tmp >>= 32-offset;
    _hi <<= offset;
    _hi += tmp;
    _lo <<= offset;
}

void BitString::ShiftRight(const unsigned offset){
    unsigned int tmp;
    tmp = _hi;
    // tmp <<= 32-offset;
    offset > 32 ? tmp >>= offset-32: tmp <<= 32-offset;
    _lo >>= offset;
    _lo += tmp;
    _hi >>= offset;
}
void BitString::NOT(){
    _lo = ~_lo;
    _hi = ~_hi;
}
void BitString::AND(const BitString& b){
    _lo &= b._lo;
    _hi &= b._hi;
    
}
void BitString::OR(const BitString& b){
    _lo |= b._lo;
    _hi |= b._hi;
}
void BitString::XOR(const BitString& b){
    _lo ^= b._lo;
    _hi ^= b._hi;
}