#include <iostream>


using namespace std;


template <class T_Type>
class Set{
    T_Type* lst;
    int length;
public:
    Set();
    Set(T_Type* a, int cnt);
    Set(const Set &set);
    ~Set();
    Set& operator=(const Set &set);
    void add(T_Type elem);
    void add(T_Type* elems, int cnt);
    void del(T_Type elem);
    bool in(T_Type elem) const;
    void print() const;
    Set operator+(const Set& s) const;
    Set operator*(const Set& s) const;
};

template <class T_Type>
Set<T_Type>::Set(){
    lst = NULL;
    length = 0;
}

template <class T_Type>
Set<T_Type>::Set(T_Type* a, int cnt){
    bool flg;
    int k = 0;
    lst = new T_Type[cnt];
    length = cnt;
    for (int i = 0; i < cnt; i++){
        flg = true;
        for (int j = 0; j < i; j++){
            if (a[j] == a[i]) {
                flg = false;
                break;
            }
        }
        if (flg) {
            lst[k] = a[i];
            k++;
        }
    }
    length = k;
}

template <class T_Type>
Set<T_Type>::~Set(){
    delete[] lst;
}

template <class T_Type>
Set<T_Type>::Set(const Set &set){
    length = set.length;
    if (length > 0){
        lst = new T_Type[length];
        for (int i = 0; i < length; i++){
            lst[i] = set.lst[i];
        }
    } else {
        lst = NULL;
    }
}

template <class T_Type>
Set<T_Type>& Set<T_Type>::operator=(const Set &set){
    if (this == &set){
        return *this;
    }
    delete[] lst;
    length = set.length;
    if (length > 0){
        lst = new T_Type[length];
        for (int i = 0; i < length; i++)
            lst[i] = set.lst[i];
    } else {
        lst = NULL;
    }
    return *this;
}

template <class T_Type>
void Set<T_Type>::add(T_Type elem){
    bool f = true;
    for (int i = 0; i < length; i++){
        if (lst[i] == elem){
            f = false;
            break;
        }
    }
    if (f){
        T_Type* buf = new T_Type[length + 1];
        for (int i = 0; i < length; i++)
            buf[i] = lst[i];
        buf[length] = elem;
        delete[] lst;
        length++;
        lst = new T_Type[length];
        for (int i = 0; i < length; i++)
            lst[i] = buf[i];
        delete[] buf;
    }
}

template <class T_Type>
void Set<T_Type>::add(T_Type* elems, int cnt){
    for (int i = 0; i < cnt; i++){
        add(elems[i]);
    }
}

template <class T_Type>
bool Set<T_Type>::in(T_Type elem) const {
    for (int i = 0; i < length; i++) {
        if (lst[i] == elem)
            return true;
    }
    return false;
}

template <class T_Type>
void Set<T_Type>::del(T_Type elem){
    if ( !in(elem) ){
        return;
    }
    T_Type* buf = new T_Type[length - 1];
    int k = 0;
    for (int i = 0; i < length; i++){
        if (lst[i] != elem) {
            buf[k] = lst[i];
            k++;
        }
    }
    delete[] lst;
    length--;
    lst = new T_Type[length];
    for (int i = 0; i < length; i++){
        lst[i] = buf[i];
    }
    delete[] buf;
}

template <class T_Type>
void Set<T_Type>::print() const {
    T_Type tmp;
    for (int i = 0; i < length; i++){
        for (int j=i+1; j<length; j++){
            if (lst[i] > lst[j]){
                tmp = lst[i];
                lst[i] = lst[j];
                lst[j] = tmp;
            }
        }
    }
    for (int i = 0; i < length; i++){
        if (i == length-1){
            cout << lst[i];
        } else {
            cout << lst[i] << " ";
        }
    }
    cout << endl;
}

template <class T_Type>
Set<T_Type> Set<T_Type>::operator+(const Set &s) const {
    Set result = *this;
    for (int i = 0; i < s.length; i++){
        result.add(s.lst[i]);
    }
    return result;
}

template <class T_Type>
Set<T_Type> Set<T_Type>::operator*(const Set &s) const {
    int cnt = 0;
    int k = 0;
    T_Type* buf;
    for (int i = 0; i < s.length; i++){
        if (in(s.lst[i])){
            cnt++;
        }
    }
    buf = new T_Type[cnt];
    for (int i = 0; i < s.length; i++){
        if (in(s.lst[i])){
            buf[k] = s.lst[i];
            k++;
        }
    }
    Set result(buf, cnt);
    delete[] buf;
    return result;
}

