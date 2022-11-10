#ifndef __LMATRIX2_H__
#define __LMATRIX2_H__

#include <string>

template<typename T>

class LMatrix2{
public:
    // 构造函数
    //LMatrix2();
    LMatrix2(int nRows=1, int nCols=1, const T num=0);
    LMatrix2(int nRows, int nCols, const T *inputData);
    LMatrix2(const LMatrix2<T>& inputMatrix);

    // 析构函数
    ~LMatrix2();

    // 功能函数
    bool reshape(int numRows, int numCols);
    void transpose();

    // 矩阵元素获取
    T getElement(int row, int col) const;
    bool SetElement(int row, int col, T elementValue);
    int GetNumRows() const;
    int GetNumCols() const;
    std::string GetDtype();


    // 重载 == 运算符
    bool operator == (const LMatrix2<T>& rhs);

    // 重载 + - * /
    template<typename U> friend LMatrix2<U> operator + (const LMatrix2<U>& lhs, const LMatrix2<U>& rhs);
    template<typename U> friend LMatrix2<U> operator + (const U& lhs, const LMatrix2<U>& rhs);
    template<typename U> friend LMatrix2<U> operator + (const LMatrix2<U>& lhs, const U& rhs);

    template<typename U> friend LMatrix2<U> operator - (const LMatrix2<U>& lhs, const LMatrix2<U>& rhs);
    template<typename U> friend LMatrix2<U> operator - (const LMatrix2<U>& lhs, const U& rhs);

    template<typename U> friend LMatrix2<U> operator * (const LMatrix2<U>& lhs, const LMatrix2<U>& rhs);
    template<typename U> friend LMatrix2<U> operator * (const U& lhs, const LMatrix2<U>& rhs);
    template<typename U> friend LMatrix2<U> operator * (const LMatrix2<U>& lhs, const U& rhs);

private:
    int Sub2Ind(int row, int col) const;
    T *m_matrixData;
    int m_nCols;
    int m_nRows;
    int m_nElements;
    std::string dtype;
};


// 重载 << 运算符

#include<iostream>
#include<iomanip>
#include<sstream>

//计算 输出字符的长度
template<typename T>
size_t number_of_digits(T n) {
    std::ostringstream strs;
    strs << n;
    return strs.str().size();
}


template<typename T>
std::ostream& operator << (std::ostream& out, const LMatrix2<T>& rhs){
    // 先求解每列 最长字符
    size_t max_len_per_column[rhs.GetNumCols()] = {0};
    for (int i=0; i<rhs.GetNumRows(); i++)
        for (int j=0; j< rhs.GetNumCols(); j++){
            size_t temp_len = number_of_digits(rhs.getElement(i,j));
            if (temp_len > max_len_per_column[j])
                max_len_per_column[j] = temp_len;
        }

    // 格式化输出
    for(int i=0; i < rhs.GetNumRows(); i++){
        // 行头 [ or [[
        out<<(i==0?"[[":" [");
        // 每行 元素
        for (int j=0; j < rhs.GetNumCols(); j++){
            out<<std::setw(max_len_per_column[j])<<rhs.getElement(i,j);
            if (j < rhs.GetNumCols()-1)
                out<<", ";
        }
        // 行尾 ] or ]]
        out<<(i==rhs.GetNumRows()-1?"]]":"] ");
        // 换行
        if (i < rhs.GetNumRows() - 1)
            out<<std::endl;
    }
    return out;
}


/*
//构造 1*1 矩阵
template<typename T>
LMatrix2<T>::LMatrix2(){
    m_nRows = 1;
    m_nCols = 1;
    m_nElements = 1;

    m_matrixData = new T[m_nElements];
    m_matrixData[0] = 0.0;
}
*/

//构造空矩阵
template<typename T>
LMatrix2<T>::LMatrix2(int nRows, int nCols, const T num){
    m_nRows = nRows;
    m_nCols = nCols;
    m_nElements = m_nCols * m_nRows;
    m_matrixData = new T[m_nElements];
    for (int i=0; i<m_nElements; i++){
        m_matrixData[i] = 0.0;
    }
}

//拷贝构造函数
template<typename T>
LMatrix2<T>::LMatrix2(const LMatrix2<T>& inputMatrix) {
    m_nRows = inputMatrix.m_nRows;
    m_nCols = inputMatrix.m_nCols;
    m_nElements = inputMatrix.m_nElements;
    m_matrixData = new T[m_nElements];
    for(int i=0; i<m_nElements; i++){
        m_matrixData[i] = inputMatrix.m_matrixData[i];
    }
}

template<typename T>
LMatrix2<T>::LMatrix2(int nRows, int nCols, const T *inputData) {
    m_nCols = nCols;
    m_nRows = nRows;
    m_nElements = m_nCols * m_nRows;
    m_matrixData = new T[m_nElements];
    for (int i=0; i<m_nElements; i++){
        m_matrixData[i] = inputData[i];
    }
}



//析构函数
template<typename T>
LMatrix2<T>::~LMatrix2(){
    if (this->m_matrixData != nullptr){
        delete [] this->m_matrixData;
    }
}

template<typename T>
bool LMatrix2<T>::reshape(int numRows, int numCols){
    if (numRows * numCols != this->m_nElements)
        return false;
    else{
        this->m_nRows = numRows;
        this->m_nCols = numCols;
    }
}

template<typename T>
void LMatrix2<T>::transpose() {
    LMatrix2<T> temp(*this);
    this->reshape(this->GetNumCols(), this->GetNumRows());
    for(int i=0; i<GetNumRows();i++)
        for (int j=0; j<GetNumCols(); j++)
            this->SetElement(i, j, temp.getElement(j, i));

}

template<typename T>
int LMatrix2<T>::Sub2Ind(int row, int col) const{
    return row * this->m_nCols + col;
}

template<typename T>
T LMatrix2<T>::getElement(int row, int col) const{
    int linearIndex = Sub2Ind(row, col);
    return m_matrixData[linearIndex];
}

template<typename T>
bool LMatrix2<T>::SetElement(int row, int col, T elementValue) {
    int linearIndex = Sub2Ind(row, col);
    if (linearIndex < 0 || linearIndex >= m_nElements){
        return false;
    }
    m_matrixData[linearIndex] = elementValue;
    return true;
}

template<typename T>
int LMatrix2<T>::GetNumRows() const {
    return this->m_nRows;
}

template<typename T>
int LMatrix2<T>::GetNumCols() const{
    return this->m_nCols;
}

template<typename T>
std::string LMatrix2<T>::GetDtype(){
    this->dtype = typeid(m_matrixData[0]).name();
    return this->dtype;
}

template<typename T>
bool LMatrix2<T>::operator==(const LMatrix2<T> &rhs) {
    if (this->m_nElements != rhs.m_nElements){
        return false;
    }
    for(int i=0; i<this->m_nElements; i++){
        if(this->m_matrixData[i] != rhs.m_matrixData[i])
            return false;
    }
    return true;
}


template<typename T>
LMatrix2<T> operator+(const LMatrix2<T> &lhs, const LMatrix2<T>& rhs) {
    int numRows = lhs.m_nRows;
    int numCols = lhs.m_nCols;
    int numElements = numCols * numRows;
    // 创建新矩阵
    LMatrix2<T> result(numRows, numCols);
    for(int i=0; i<numElements; i++){
        result.m_matrixData[i] = lhs.m_matrixData[i] + rhs.m_matrixData[i];
    }
    return result;
}

template<typename T>
LMatrix2<T> operator+(const T& lhs, const LMatrix2<T>& rhs){
    LMatrix2<T> result(rhs);
    int numElements = rhs.m_nElements;
    for(int i=0; i<numElements; i++){
        result.m_matrixData[i] += lhs;
    }
    return result;
}

template<typename T>
LMatrix2<T> operator+(const LMatrix2<T>& lhs, const T& rhs){
    LMatrix2<T> result(lhs);
    int numElements = lhs.m_nElements;
    for(int i=0; i<numElements; i++){
        result.m_matrixData[i] += lhs;
    }
    return result;
}

template<typename T>
LMatrix2<T> operator-(const LMatrix2<T> &lhs, const LMatrix2<T>& rhs) {
    int numRows = lhs.m_nRows;
    int numCols = lhs.m_nCols;
    int numElements = numCols * numRows;
    // 创建新矩阵
    LMatrix2<T> result(numRows, numCols);
    for(int i=0; i<numElements; i++){
        result.m_matrixData[i] = lhs.m_matrixData[i] - rhs.m_matrixData[i];
    }
    return result;
}


template<typename T>
LMatrix2<T> operator-(const LMatrix2<T>& lhs, const T& rhs){
    LMatrix2<T> result(lhs);
    int numElements = lhs.m_nElements;
    for(int i=0; i<numElements; i++){
        result.m_matrixData[i] -= lhs;
    }
    return result;
}

template<typename T>
LMatrix2<T> operator * (const LMatrix2<T>& lhs, const LMatrix2<T>& rhs){
    int numRows = lhs.m_nRows;
    int numCols = rhs.m_nCols;
    int temp = lhs.m_nCols;
    int numElements = numRows * numCols;
    LMatrix2<T> result(numRows, numCols);

    for(int i=0; i<numRows; i++){
        for(int j=0; j<numCols; j++){
            for(int k=0; k<temp; k++){
                int linearIndex = result.Sub2Ind(i, j);
                result.m_matrixData[linearIndex] += lhs.m_matrixData[lhs.Sub2Ind(i, k)] * rhs.m_matrixData[rhs.Sub2Ind(k, j)];
            }
        }
    }
    return result;
}

template<typename T>
LMatrix2<T> operator * (const LMatrix2<T>& lhs, const T& rhs){
    int numElements = lhs.m_nElements;
    LMatrix2<T> result(lhs);
    for(int i=0; i<numElements; i++){
        result.m_matrixData[i] *= rhs;
    }
    return result;
}

template<typename T>
LMatrix2<T> operator * (const T& lhs, const LMatrix2<T>& rhs){
    int numElements = rhs.m_nElements;
    LMatrix2<T> result(rhs);
    for(int i=0; i<numElements; i++){
        result.m_matrixData[i] *= lhs;
    }
    return result;
}


#endif //__LMATRIX2_H__
