#include <iostream>
#include <cmath>
#include <limits>
#include <cstdlib>


char* right(char* str,int n){
    int i, len;
    while (str[i] != '\0'){
        i++;
    }
    len = i;
    if (len < n){
        return str;
    } else {
        return &str[len-n];
    }
    
}

unsigned long right(unsigned long num,int n){
    int i=0;
    unsigned long ans = 0;
    while (num != 0 && i < n){
        ans += (num%10)*std::pow(10,i);
        i++;
        num /= 10;
    }
    return ans;
}


int main(){
    char name[10];
    char astr[101];
    unsigned long anum;
    int n,f_n=1,f_s=1;
    std::cin >> name;

    for (int i = 0;i<8;i++){
        if (name[i] == '\0'){
            // std::cout << "break" << std::endl;
            break;
        }
        if ((f_s == 0 && f_n == 0) || i == 7){
            f_s = 0;
            f_n =0;
            // std::cout << "break" << std::endl;
            break;
        }
        if (name[i] != "string"[i]){
            f_s = 0;
            // std::cout << "not_s " << i << ' ' << name[i] << "string"[i] << std::endl; 
        }
        if (name[i] != "number"[i]){
            
            // std::cout << "not_n " << i << ' ' << name[i] << "string"[i] << std::endl;
            f_n = 0;
            // std::cout << "wtf: " << name[i] << std::endl;
        }
    }
    if (f_n){
        // std::cout << "print anum: ";
        std::cin >> anum;
        // std::cout << "anum: " << anum << std::endl;
        if (!(std::cin >> n)) {
            std::cout << "" << std::endl;
        }
        std::cout << right(anum,n);

    } else if (f_s){
        std::cin >> astr;
        if (!(std::cin >> n)) {
            std::cout << "" << std::endl;
        }
        std::cout << right(astr,n) << std::endl;
    } else{
        std::cin >> astr;
        std::cin >> n;
        std::cout << 0 << std::endl;
    }
}