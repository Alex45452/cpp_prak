#include <iostream>
#include <cmath>

class Vec{
    int len;
    double *v;
public:
    Vec(int n);
    Vec(int n, double* ptr);
    Vec(const Vec &nv);
    ~Vec(){
        delete [] v;
    }
    void set(double arg, int coord);

    double get(int coord) const{
        if (coord>=len || coord < 0){
            return 0.0;
        }
        return v[coord];
    }
    double euc_norm() const;
    double max_norm() const;
    void print() const;

};

Vec::Vec(int n, double* ptr){
    len = n;
    v = new double[n];
    for (int i=0;i<n;i++){
        v[i] = ptr[i];
    } 
}
Vec::Vec(int n){
    len = n;
    v = new double[n];
    for (int i=0;i<n;i++){
        v[i] = 0;
    } 
}
Vec::Vec(const Vec &nv){
    len = nv.len;
    v = new double[len];
    for (int i=0;i<len;i++){
        v[i] = nv.v[i];
    }
}

void Vec::set(double arg, int coord){
    if (coord>=len || coord < 0){
        return ;
    }
    v[coord] = arg;
}

double Vec::euc_norm() const{
    double res;
    for(int i =0;i<len;i++){
        res += v[i]*v[i];
    }
    return sqrt(res);
}
double Vec::max_norm() const{
    double res = v[0];
    for(int i =0;i<len;i++){
        if ((v[i] > 0 && v[i] > res) || (v[i] < 0 && -v[i] > res)){
            res = v[i] > 0 ? v[i] : -v[i];
        }
    }
    return res;
}
void Vec::print() const{
    std::cout << '(';
    for (int i = 0;i<len-1;i++){
        std::cout << v[i] << ',';
    }
    std::cout << v[len-1] << ')' << std::endl;
}