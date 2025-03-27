#include <iostream>
#include <cstring>

using namespace std;

class mstring{
    private:
        char* _string;
        int _length;
    public:
        mstring() {_string = new char[1]; _string[0] = '\0'; _length = 0;};
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
};

mstring::mstring(const char* str)
{
    
    _length = strlen(str);
    _string = new char[_length+1];
    strcpy(_string,str);
}

mstring::mstring(const mstring& o_str)
{
    _length = o_str._length;
    _string = new char[_length+1];
    strcpy(_string,o_str._string);
}

void mstring::add(const char c)
{
    char *buf;
    buf = new char[_length+2];
    strcpy(buf,_string);
    buf[_length] = c;
    buf[_length + 1] = '\0';
    _length += 1;
    delete [] _string;
    _string = buf;
} // с - символ
void mstring::add(const char* c)
{
    char *buf;
    if (c == nullptr) return;
    int c_len = strlen(c);
    // _length += i;
    buf = new char[_length+c_len+1];
    strcpy(buf,_string);
    strcat(buf,c);
    _length += c_len;
    delete [] _string;
    _string = buf;
} // с - строка
void mstring::insert(const char c,const int pos)
{
    char *buf;
    if (pos > _length){
        return;
    }
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
    if (c == nullptr) return;
    int c_len = strlen(c);
    if (pos > _length){
        return;
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
    char *buf;
    if (pos > _length) return;
    buf = new char[_length];
    strncat(buf,_string,pos);
    strcat(buf,&_string[pos+1]);
    _length -= 1;
    delete [] _string;
    _string = buf;
}              // i - позиция
void mstring::del(const int s_pos,const int e_pos)
{
    char *buf;
    if (s_pos > _length) {return;}
    if (e_pos >= _length-1)
    {
        buf = new char[s_pos+1];
        buf[0] = '\0';
        strncat(buf,_string,s_pos);
        buf[s_pos] = '\0';
        _length = s_pos;
    } else {
        buf = new char[_length-(e_pos-s_pos)-1];
        strncpy(buf,_string,s_pos);
        buf[s_pos] = '\0';
        strcat(buf,&_string[e_pos+1]);
        _length = _length-e_pos+s_pos-1;
    }
    delete [] _string;
    _string = buf;
} // i, j - позиции задающие диапазон удаления с i по j включительно
int mstring::search(const char* str) const
{
    char * a = strstr(_string,str);
    if (str == nullptr || a == nullptr) return -1;
    return a -_string;
}
void mstring::replace(const char* sub_str, const char *new_str)
{
    int pos = search(sub_str),sub_len = 0, new_len = 0;
    char *buf;
    if (pos == -1)
    {
        return;
    }
    if (sub_str == nullptr) return;
    if (new_str == nullptr) return;
    
    sub_len = strlen(sub_str);
    new_len = strlen(new_str);

    buf = new char[_length+new_len-sub_len+1];
    for(int i = 0;i < pos;i++){
        buf[i] = _string[i];
    }
    for (int i = pos; i < pos+new_len; i++){
        buf[i] = new_str[i-pos];
    }
    for(int i = pos+sub_len;i < _length+1;i++){
        buf[i-sub_len+new_len] = _string[i];
    }
    _length += new_len-sub_len;
    delete [] _string;
    _string = buf;
    

} // замена подстроки sub_str на new_str,

