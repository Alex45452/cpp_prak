#include <iostream>
using namespace std;

class Parser{
private:
    string s;
    int pos;
    char c;
public:
    Parser(string str): s(str){pos = 0; c = '\0';}
    void gc();
    bool result();
    bool resA();
    bool resB();
    bool resS();
};

void Parser::gc(){
    if (pos < s.length()) {
            c = s[pos++];
        } else {
            c = '\0';
        }
}
bool Parser::resS(){
    if (c == 'a'){
        gc();
        if (!resA()) {
            return false;
        }
        return resB();
    }
    else if (c == 'b'){
        gc();
        return resB();
    } else {
        return false;
    }

}

bool Parser::resA(){
    if (c == 'a'){
        gc();
        return resA();
    } else if (c == 'b'){
        gc();
        return true;
    }
    return false;
}

bool Parser::resB(){
    if (c == 'b'){
        gc();
        return resB();
    }
    return true;
}

bool Parser::result(){
    gc();
    if (!resS()){
        return false;
    }
    return c == '\0';
}
int main(){
    string str;
    cin >> str;
    Parser p(str);
    if (p.result()){
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}