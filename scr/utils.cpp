#include "utils.h"
#include <iostream>
int clamp(int var, int min, int max){
    if(var<min){return min;}
    if(var>max){return max;}
    return var;
}
std::string operator*(const std::string& s, int n){
    std::string result;
    result.reserve(s.size()*n);
    for(int i=0; i<n; i++){
        result+=s;
    }
    return result;
}