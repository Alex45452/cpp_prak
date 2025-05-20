#include <iostream>
#include <cstring>
#include <cmath>

class VecException{
    char* comment;
    int fstlen;
    int sndlen;
    int type; // тип 0 - 0 операторов, тип 1 - 1 оператор, тип 2 - 2 оператора;
public:
    VecException(const char* cmt,const int t, const int ft, const int sd);
    VecException(const VecException &ex);
    ~VecException(){delete [] comment;}
    const char* getcomm() const {return comment;}
    const int getfst() const {return fstlen;}
    const int getsnd() const {return sndlen;}
    const int gettype() const {return type;}
};

class Vec{
    int len;
    double *v;
public:
    explicit Vec(const int n);
    Vec(const int n, double* const ptr);
    Vec(const Vec &nv);
    ~Vec();
    void set(const double arg, const int coord);
    double get(const int coord) const;
    double euc_norm() const;
    double max_norm() const;
    void print() const;


    Vec operator+(Vec op2) const;
    Vec operator-(Vec op2) const;
    Vec operator*(const double op2) const;
    Vec& operator=(const Vec& op2);
    bool operator==(Vec op2) const;
    double& operator[](const int n);

    
    friend std::ostream& operator<<(std::ostream& os, const Vec& op2);
    friend Vec operator*(const double op1, const Vec& op2);
    // friend Vec operator*(const Vec& op1, double& op2);

};

VecException::VecException(const char* cmt, const int t, const int ft = 0, const int sd = 0){
    comment = new char [strlen(cmt)];
    strcpy(comment,cmt);
    fstlen = ft;
    sndlen = sd;
    type = t;
}
VecException::VecException(const VecException &ex){
    comment = new char [strlen(ex.comment)];
    strcpy(comment,ex.comment);
    type = ex.type;
    fstlen = ex.fstlen;
    sndlen = ex.fstlen;
}

Vec::Vec(const int n,double* const ptr){
    if (n < 1){
        throw VecException("length error", 0);
    }
    len = n;
    v = new double[n];
    for (int i=0;i<n;i++){
        v[i] = ptr[i];
    } 
}
Vec::Vec(const int n){
    if (n < 1){
        throw VecException("length error", 0);
    }
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
        throw VecException("coordinate error in set()", 0);
    }
    v[coord] = arg;
}

double Vec::get(const int coord) const{
    if (coord>=len || coord < 0){
        throw VecException("coordinate error in get()", 0);
    }
    return v[coord];
}

double Vec::euc_norm() const{
    double res = 0;
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
    if (op2.len != len){
        throw VecException("addition of vectors of different lengths:",2,len,op2.len);
    }
    for (int i = 0; i < len; i++){
        res.set(op2.v[i]+v[i],i);
    }
    return res;
}

Vec Vec::operator-(const Vec op2) const{
    Vec res(len);
    if (op2.len != len){
        throw VecException("subtraction of vectors of different lengths:",2,len,op2.len);
    }
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

Vec& Vec::operator=(const Vec& op2){
    if (this == &op2){
        return *this;
    }
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
    if (n>=len || n < 0){
        throw VecException("incorrect indexing:",1,n);
    }
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

void error();

int main()
{
    try
    {
        error();
    }
    catch(const VecException &ex)
    {
        fprintf(stderr,"Exception: %s",ex.getcomm());
        if (ex.gettype() == 1){
            fprintf(stderr," %d", ex.getfst());
        } else if (ex.gettype() == 2){
            fprintf(stderr," %d %d", ex.getfst(), ex.getsnd());
        }
        // fprintf(stderr,"\n");
    }
    catch (...)
    {
        fprintf(stderr,"Exception: unknown error");
    }
    return 0;
} 