#include <iostream>

using namespace std;

class mstring{
    private:
        char* _string;
        int _length;
    public:
        mstring() {_string = new char[0]; _length = 0;};
        mstring(const char* str);
        mstring(const mstring& o_str);
        ~mstring(){delete [] _string;}
        int length() const{return _length;};
        bool isempty() const{return _length == 0;}
        void add(const char c); // с - символ
        void add(const char* c); // с - строка
        void insert(const char c,const int pos); // с - символ, pos - позиция
        void insert(const char* c,const int pos); // с - строка, pos - позиция
        void del(const int pos);                 // i - позиция
        void del(const int s_pos, const int e_pos); // i, j - позиции задающие диапазон удаления с i по j включительно
        int search(const char* str) const;
        void replace(const char* sub_str, const char *new_str); // замена подстроки sub_str на new_str,
        void print() const {cout << _string << endl;}
        mstring operator+(const mstring op2) const;
        mstring operator*(const unsigned int op2) const;
        mstring& operator=(const mstring op2);
        bool operator>(const mstring op2) const;
        bool operator<(const mstring op2) const;
        bool operator>=(const mstring op2) const;
        bool operator<=(const mstring op2) const;
        bool operator==(const mstring op2) const;
        char& operator[](const int op2){return _string[op2];}

        friend ostream& operator<<(ostream& os,const mstring op2);
        friend ostream& operator>>(ostream& os,const mstring op2);
        friend mstring operator*(const unsigned int& op1,const mstring op2);

};

mstring::mstring(const char* str)
{
    int i = 0;
    while (str[i] != '\0'){
        i += 1;
    }
    _length = i;
    _string = new char[_length+1];
    for (int i = 0; i < _length+1; i++){
        _string[i] = str[i];
    }
}

mstring::mstring(const mstring& o_str)
{
    _length = o_str._length;
    _string = new char[_length+1];
    for (int i = 0; i < _length+1; i++){
        _string[i] = o_str._string[i];
    }
}

void mstring::add(const char c)
{
    char *buf;
    buf = new char[_length+2];
    for(int i = 0;i < _length;i++){
        buf[i] = _string[i];
    }
    buf[_length] = c;
    buf[_length + 1] = '\0';
    _length += 1;
    delete [] _string;
    _string = buf;
} // с - символ
void mstring::add(const char* c)
{
    char *buf;
    int c_len = 0;
    while (c[c_len] != '\0'){
        c_len += 1;
    }
    // _length += i;
    buf = new char[_length+c_len+1];
    for(int i = 0;i < _length;i++){
        buf[i] = _string[i];
    }
    for (int i = _length; i < _length+c_len+1; i++){
        buf[i] = c[i];
    }
    _length += c_len;
    delete [] _string;
    _string = buf;
} // с - строка
void mstring::insert(const char c,const int pos)
{
    char *buf;
    buf = new char[_length+2];
    for(int i = 0;i < pos;i++){
        buf[i] = _string[i];
    }
    buf[pos] = c;
    for(int i = pos+1;i < _length+2;i++){
        buf[i] = _string[i-1];
    }
    _length += 1;
    delete [] _string;
    _string = buf;
} // с - символ, i - позиция
void mstring::insert(const char* c,const int pos)
{
    char *buf;
    int c_len = 0;
    while (c[c_len] != '\0'){
        c_len += 1;
    }
    buf = new char[_length+c_len+1];
    for(int i = 0;i < pos;i++){
        buf[i] = _string[i];
    }
    for (int i = pos; i < pos+c_len; i++){
        buf[i] = c[i-pos];
    }
    for(int i = pos+c_len;i < _length+c_len+2;i++){
        buf[i] = _string[i-c_len];
    }
    _length += c_len;
    delete [] _string;
    _string = buf;
} // с - строка, i - позиция
void mstring::del(const int pos)
{
    for(int i = pos; i < _length; i++){
        _string[i] = _string[i+1];
    }
    _length -= 1;
}              // i - позиция
void mstring::del(const int s_pos,const int e_pos)
{
    for(int i = e_pos; i < _length; i++){
        _string[s_pos+i-e_pos] = _string[i+1];
    }
    _length -= _length-(e_pos-s_pos+1);
} // i, j - позиции задающие диапазон удаления с i по j включительно
int mstring::search(const char* str) const
{
    int str_len = 0;
    bool fl;
    while (str[str_len] != '\0'){
        str_len++;
    }
    // cout << "SEARCH: str_len " << str_len << endl;
    for (int i = 0; i < _length - str_len + 1; i++){
        fl = true;
        for (int j = 0; j < str_len; j++){
            // cout << "SEARCH: _string[i+j] " << _string[i+j] << " str[j] "<< str[j] << endl;
            if (_string[i+j] != str[j]){
                fl = false;
                break;
            }
        }
        if (fl){
            return i;
        }
    }
    return -1;
}
void mstring::replace(const char* sub_str, const char *new_str)
{
    int pos = search(sub_str),sub_len = 0, new_len = 0;
    char *buf;
    if (pos == -1)
    {
        return;
    }
    while (sub_str[sub_len] != '\0'){
        sub_len++; 
    }
    while (new_str[new_len] != '\0'){
        new_len++; 
    }
    buf = new char[_length+new_len-sub_len+1];
    for(int i = 0;i < pos;i++){
        buf[i] = _string[i];
        // cout << buf[i] << endl;
    }
    for (int i = pos; i < pos+new_len; i++){
        buf[i] = new_str[i-pos];
        // cout << buf[i] << endl;

    }
    for(int i = pos+sub_len;i < _length+1;i++){
        buf[i-sub_len+new_len] = _string[i];
        // cout << _string[i] << endl;
    }
    _length += new_len-sub_len;
    delete [] _string;
    _string = buf;
    

} // замена подстроки sub_str на new_str,

mstring mstring::operator+(const mstring op2) const
{
    mstring res(*this);
    res.add(op2._string);
    return res;
}
mstring mstring::operator*(const unsigned int op2) const
{
    mstring res;
    for (int i = 0; i < op2; i++){
        res.add(_string);
    }
    return res;
}
mstring& mstring::operator=(const mstring op2)
{
    delete [] _string;
    _length = op2._length;
    _string = new char[op2._length+1];
    for (int i = 0; i < _length+1; i++){
        _string[i] = op2._string[i];
    }
    return *this;
}
bool mstring::operator>(const mstring op2) const
{
    bool res;
    
}
bool mstring::operator<(const mstring op2) const
{

}
bool mstring::operator>=(const mstring op2) const
{

}
bool mstring::operator<=(const mstring op2) const
{

}
bool mstring::operator==(const mstring op2) const
{

}
// char& operator[](const int op2){return _string[op2];}

ostream& operator<<(ostream& os,const mstring op2)
{

}
ostream& operator>>(ostream& os,const mstring op2)
{

}
mstring operator*(const double& op1,const mstring op2)
{

}