#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

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

template <class T_type>
class Vec;

template <class T_type>
std::ostream& operator<<(std::ostream& os, const Vec<T_type>& op2);

template <class T_type>
Vec<T_type> operator*(const T_type op1, const Vec<T_type>& op2);

template <class T_type>
class Vec{
    int len;
    T_type *v;

    friend std::ostream& operator<< <T_type> (std::ostream& os, const Vec& op2);
    friend Vec<T_type> operator* <T_type> (const T_type op1, const Vec& op2);
public:
    explicit Vec(const int n);
    Vec(const int n, T_type* const ptr);
    Vec(const Vec<T_type> &nv);
    ~Vec();
    void set(const T_type arg, const int coord);
    T_type get(const int coord) const;
    T_type max_norm() const;
    // void print() const;


    Vec<T_type> operator+(const Vec<T_type>& op2) const;
    Vec<T_type> operator-(const Vec<T_type>& op2) const;
    Vec<T_type> operator*(const T_type op2) const;
    T_type operator^(const Vec<T_type>& op2) const;
    Vec<T_type>& operator=(const Vec<T_type>& op2);
    Vec<T_type>& operator+=(const Vec<T_type>& op2);
    bool operator==(const Vec<T_type>& op2) const;
    T_type& operator[](const int n);
    // friend Vec operator*(const Vec& op1, T_type& op2);

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

template <class T_type>
Vec<T_type>::Vec(const int n, T_type* const ptr){
    if (n < 1){
        throw VecException("length error", 0);
    }
    len = n;
    v = new T_type[n];
    for (int i=0;i<n;i++){
        v[i] = ptr[i];
    } 
}
template <class T_type>
Vec<T_type>::Vec(const int n){
    if (n < 1){
        throw VecException("length error", 0);
    }
    len = n;
    v = new T_type[n];
    for (int i=0;i<n;i++){
        v[i] = 0;
    } 
}
template <class T_type>
Vec<T_type>::Vec(const Vec &nv){
    len = nv.len;
    v = new T_type[len];
    for (int i=0;i<len;i++){
        v[i] = nv.v[i];
    }
}

template <class T_type>
Vec<T_type>::~Vec(){
    delete [] v;
}

template <class T_type>
void Vec<T_type>::set(const T_type arg, const int coord){
    if (coord>=len || coord < 0){
        throw VecException("coordinate error in set()", 0);
    }
    v[coord] = arg;
}

template <class T_type>
T_type Vec<T_type>::get(const int coord) const{
    if (coord>=len || coord < 0){
        throw VecException("coordinate error in get()", 0);
    }
    return v[coord];
}

template <class T_type>
T_type Vec<T_type>::max_norm() const{
    T_type res = v[0];
    for(int i =0;i<len;i++){
        if ((v[i] > 0 && v[i] > res) || (v[i] < 0 && -v[i] > res)){
            res = v[i] > 0 ? v[i] : -v[i];
        }
    }
    return res;
}
 
// template <class T_type>
// void T_type Vec<T_type>::print() const{
//     std::cout << '(';
//     for (int i = 0;i<len-1;i++){
//         std::cout << v[i] << ',';
//     }
//     std::cout << v[len-1] << ')' << std::endl;
// }

template <class T_type>
Vec<T_type> Vec<T_type>::operator+(const Vec& op2) const{
    Vec res(len);
    if (op2.len != len){
        throw VecException("addition of vectors of different lengths:",2,len,op2.len);
    }
    for (int i = 0; i < len; i++){
        res.set(op2.v[i]+v[i],i);
    }
    return res;
}

template <class T_type>
Vec<T_type> Vec<T_type>::operator-(const Vec& op2) const{
    Vec res(len);
    if (op2.len != len){
        throw VecException("subtraction of vectors of different lengths:",2,len,op2.len);
    }
    for (int i = 0; i < len; i++){
        res.set(v[i]-op2.v[i],i);
    }
    return res;
}

template <class T_type>
Vec<T_type> Vec<T_type>::operator*(const T_type op2) const{
    Vec res(len);
    for (int i = 0; i < len; i++){
        res.set(v[i]*op2,i);
    }
    return res;
}

template <class T_type>
T_type Vec<T_type>::operator^(const Vec<T_type>& op2) const{
    if (op2.len != len){
        throw VecException("multiplication of vectors of different lengths:",2,len,op2.len);
    }
    T_type res = v[0]*op2.v[0];    
    for (int i = 1; i < len; i++){
        res += v[i]*op2.v[i];
    }
    return res;
}

template <class T_type>
Vec<T_type>& Vec<T_type>::operator=(const Vec<T_type>& op2){
    if (this == &op2){
        return *this;
    }
    len = op2.len;
    delete [] v;
    v = new T_type[len];
    for (int i = 0; i < len; i++){
        v[i] = op2.v[i];
    }
    return *this;
}

template <class T_type>
Vec<T_type>& Vec<T_type>::operator+=(const Vec<T_type>& op2){
    if (op2.len != len){
        throw VecException("addition of vectors of different lengths:",2,len,op2.len);
    }
    for (int i = 0; i < len; i++){
        this->set(op2.v[i]+v[i],i);
    }
    return *this;

}

template <class T_type>
bool Vec<T_type>::operator==(const Vec& op2) const{
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

template <class T_type>
T_type& Vec<T_type>::operator[](const int n){
    if (n>=len || n < 0){
        throw VecException("incorrect indexing:",1,n);
    }
    return v[n];
}

template <class T_type>
std::ostream& operator<<(std::ostream& os, const Vec<T_type>& op)
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

template <class T_type>
Vec<T_type> operator*(const T_type op1, const Vec<T_type> &op2)
{
    Vec<T_type> res(op2.len);
    for (int i = 0; i < op2.len; i++){
        res.set(op2.v[i]*op1,i);
    }
    return res;
}

void Vector();

int main()
{
    try
    {
        Vector();
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