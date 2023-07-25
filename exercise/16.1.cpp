#include<iostream>
#include<vector>
using namespace std;

//��ϰ16.4 ��д��Ϊ����find�㷨�ĺ���ģ��
template<typename I, typename T>
I Find(I b, I e, T n){      //��Ӧbegin,end,Ҫ���ҵ�ֵ
    for (; b != e; ++b){
        if(*b == n)
            return b;
    }
    return e;
}

//16.5 ���Դ����κ��������κγ��ȵ�����
template<typename T, size_t N>
void print(const T (&arr)[N]){  // N�Զ���ȡ�����arr�ĳ���
    for(auto elem : arr)
        cout << elem << endl;
}

//16.6 ����begin��end
template <typename T, size_t N>
const T *begin(const T (&arr)[N]) {
    return arr;
}

template <typename T, size_t N>
const T *end(const T (&arr)[N]) {
    return arr + N;
}

//16.7
template <typename T, size_t N>
constexpr int SizeOfArray(const T (&arr)[N]) {
    return N;
}




int main(){
    //16.4
    vector<int> v1{1, 2, 3, 4, 5};
    auto it = Find(v1.begin(), v1.end(), 6);
    if(it == v1.end())
        cout << "failed to find" << endl;
    else
        cout << *it << endl;

    //16.5
    int arr[5] = {1, 2, 3, 4, 5};
    print(arr);

    //
    return 0;
}