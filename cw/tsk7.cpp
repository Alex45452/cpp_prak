#include <iostream>
#include <cstring>

template <typename T>
T maxn(T *arr,const int len){
    T maxx = arr[0];
    for(int i = 1; i < len; i++){
        if (maxx < arr[i]){
            maxx = arr[i];
        }
    }
    return maxx;
}
template <>
const char* maxn(const char** str,int len){
    int mx_len = strlen(str[0]), cur_len, mx_pos;
    for(int i = 0; i < len;i++){
        cur_len = strlen(str[i]);
        if (mx_len < cur_len){
            mx_len = cur_len;
            mx_pos = i;
        }
    } 
    return str[mx_pos];
}

