#include <cstring>
#include <iostream>

using namespace std;


class Analyze{
private:
    string str;
public:
    Analyze(string s);
    bool result();
};

Analyze::Analyze(string s){
    str = s;
}

bool Analyze::result(){
    int i = 0;
    char cur = 'S';
    str.push_back('\n');
    for (int i = 0; i < str.length();i++){
        if (cur == 'S'){
            if (str[i] != 'a') {
                throw str[i];
            } else {
                cur = 'A';
            }
        }
        else if (cur == 'A') {
            if (str[i] == 'a') {
                cur = 'B';
            } else if (str[i] == 'd') {
                cur = 'A';
            } else {
                throw str[i];
            }
        }
        else if (cur == 'B') {
            if (str[i] == 'a') {
                cur = 'A';
            } else if (str[i] == '\n') {
                return true;
            } else {
                throw str[i];
            }
        }
    }
    return false;
}

int main(){
    string s;
    cin >> s;
    Analyze Analizator(s);
    try{
        Analizator.result();
        cout << s;
    }
    catch(char c){
        cerr << "Error in Lexcem: " << c;
    }
    return 0;
}