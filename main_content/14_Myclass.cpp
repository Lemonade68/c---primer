#include <iostream>
#include "14_StrBlob_blog.h"

using namespace std;

/*
 * MyClass �ඨ����һ��ָ�� StrBlobPtr ��ָ��
 */
class MyClass {
public:
    MyClass() = default;
    MyClass(StrBlobPtr *p) : pointer(p) {}

    StrBlobPtr &operator*() { return *this->pointer; };
    StrBlobPtr *operator->() { return &this->operator*(); };

private:
    StrBlobPtr *pointer = nullptr;
};

int main() {
    StrBlob a1 = {"hi", "bye", "now"};
    StrBlobPtr p1(a1);               // p1 ָ�� a1 �е� vector
    MyClass p(&p1);

    //��߾���StrBlobPtr��->
    cout << (*p)->front() << endl;
    cout << (*p)->back() << endl;
    
    //��������ú÷�������һ��->��myclass��ģ��ڶ���->��Strblobptr���
    //һ��ʼp->operator->()���*(p.pointer).operator->()������ֵ��һ��string*����->front()
    cout << p->operator->()->front();
    cout << p->operator->()->back() << endl;

    return 0;
}
