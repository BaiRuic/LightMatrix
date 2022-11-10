//
// Created by brc on 2022/11/9.
//

#include "src/LMatrix2.h"
#include<iostream>
using namespace std;

void construct_test(){
    // 初始化构造
    int a[6] = {3,-4,5,6666666, 77, 88};
    LMatrix2<int> m1(2, 3, a);
    std::cout<<m1<<std::endl;
    // 拷贝构造
    LMatrix2<int> m2(m1);
    std::cout<<m2<<std::endl;
}

int main(){
    construct_test();
    return 0;
}