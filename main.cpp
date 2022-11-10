//
// Created by brc on 2022/11/9.
//

#include "LMatrix2.h"
#include<iostream>
#include<string>
using namespace std;


int main(){
    int a[6] = {3,4,5,6, 77, 88};
    LMatrix2<int> m1(2, 3, a);
    LMatrix2<int> m2(m1);
    std::cout<<m2<<std::endl;
    std::cout<<m1<<std::endl;
    m1.transpose();
    std::cout<<m1<<'T'<<std::endl;
    LMatrix2<int> m3 = 4 * m2;
    std::cout<<m3<<std::endl;
    return 0;
}