#include <iostream>
#include <cmath>

class Vec{
        int len;
        double *v;
    public:
        Vec(const int n);
        Vec(const int n, double* const ptr);
        Vec(const Vec &nv);
        ~Vec();
        void set(const double arg, const int coord);
        double get(const int coord) const;
        double euc_norm() const;
        double max_norm() const;
        void print() const;


        Vec operator+(const Vec op2) const;
        Vec operator-(const Vec op2) const;
        Vec operator*(const double op2) const;
        Vec operator=(const Vec op2);
        bool operator==(const Vec op2) const;
        double& operator[](const int n);

        
        friend std::ostream& operator<<(std::ostream& os, const Vec& op2);
        friend Vec operator*(const double op1, const Vec& op2);
        // friend Vec operator*(const Vec& op1, double& op2);

};

Vec::Vec(const int n,double* const ptr){
    len = n;
    v = new double[n];
    for (int i=0;i<n;i++){
        v[i] = ptr[i];
    } 
}
Vec::Vec(const int n){
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

Vec::~Vec(){
    delete [] v;
}

void Vec::set(const double arg, const int coord){
    if (coord>=len || coord < 0){
        return ;
    }
    v[coord] = arg;
}

double Vec::get(const int coord) const{
    if (coord>=len || coord < 0){
        return 0.0;
    }
    return v[coord];
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

Vec Vec::operator+(const Vec op2) const{
    Vec res(len);
    for (int i = 0; i < len; i++){
        res.set(op2.v[i]+v[i],i);
    }
    return res;
}

Vec Vec::operator-(const Vec op2) const{
    Vec res(len);
    for (int i = 0; i < len; i++){
        res.set(v[i]-op2.v[i],i);
    }
    return res;
}

Vec Vec::operator*(const double op2) const{
    Vec res(len);
    for (int i = 0; i < len; i++){
        res.set(v[i]*op2,i);
    }
    return res;
}

Vec Vec::operator=(const Vec op2){
    len = op2.len;
    delete [] v;
    v = new double[len];
    for (int i = 0; i < len; i++){
        v[i] = op2.v[i];
    }
    return *this;
}

bool Vec::operator==(const Vec op2) const{
    if (len!=op2.len){
        return false;
    }
    for (int i = 0;i<len;i++){
        if (v[i] != op2.v[i]){
            return false;
        }
    }
    return true;
}

double& Vec::operator[](const int n){
    return v[n];
}

std::ostream& operator<<(std::ostream& os, const Vec& op)
{
    if (op.len > 0){
        os << '(' << op.v[0];
    } else {
        return os;
    }
    for (int i = 1; i < op.len; i++){
        os << ',' << op.v[i];
    }
    os << ')';
    return os;
}

Vec operator*(const double op1, const Vec &op2)
{
    Vec res(op2.len);
    for (int i = 0; i < op2.len; i++){
        res.set(op2.v[i]*op1,i);
    }
    return res;
}