#include <iostream>
using namespace std;

class Analyze{
    string s;
    int pos;
public:
    Analyze(string str){s = str + '\n'; pos = 0;}
    void S();
    void A();
};

void Analyze::S(){
    if (s[pos] == 'a'){
        pos++;
        cout << '2';
        A();
        cout << 'a';
    }
    else if (s[pos] == 'b'){
        pos++;
        A();
        cout << 'b';
    }
    else{
        throw s[pos];
    }
}

void Analyze::A(){
    if (s[pos] == 'a'){
        pos++;
        cout << '2';
        A();
        cout << 'a';
    }else if (s[pos] == 'b'){
        pos++;
        A();
        cout << 'b';
    }else if (s[pos] == '\n'){
        return;
    }else{
        throw s[pos];
    }
}

int main(){
    string str;
    cin >> str;
    try 
    {
        Analyze Analizator(str);
        Analizator.S();
    }
    catch (char c)
    {
        cerr << "Error in: " << c;
    }
    return 0;
}