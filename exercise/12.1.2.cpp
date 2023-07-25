#include<iostream>
#include<vector>
#include<memory>

using std::cin;
using std::cout;
using std::endl;
using std::shared_ptr;
using std::vector;

vector<int> *crtptr(){
    return new (std::nothrow) vector<int>();
}

shared_ptr<vector<int>> crtptr_sp(){
    return std::make_shared<vector<int>>();     //ע��()��ʾ��Ĭ�ϳ�ʼ��
}

void input(vector<int> *vec){
    int a;
    while(cin>>a)
        vec->push_back(a);
}

void input(shared_ptr<vector<int>> &vec){
    int a;
    while(cin>>a)
        vec->push_back(a);
}

void output(vector<int> *vec){
    for(const auto &a : *vec)
        cout << a << " ";
    cout << endl;
}

void output(const shared_ptr<vector<int>> &vec){
    for(const auto &a : *vec)
        cout << a << " ";
    cout << endl;
}

void func_6(){
    vector<int> *p = crtptr();
    input(p);
    output(p);
    delete p;           //�ͷ�p��ָ��Ŀռ�Ķ���
    p = nullptr;        //�������delete��ʹ�ã�ָ���䲻ָ���κζ���
}

void func_7(){
    auto p = crtptr_sp();
    input(p);
    output(p);
}


int main(){
    // func_6();
    func_7();
    return 0;
}