#ifndef hpvl
#define hpvl

// ���ֵ���һ��ֵ��HasPtr��

#include <iostream>
#include <string>

using namespace std;

class HasPtr {
public:
    HasPtr(const std::string &s = std::string()) :
            ps(new std::string(s)), i(0) { }
    HasPtr(const HasPtr &);                 // �������캯��
    HasPtr &operator=(const HasPtr &);      // ������ֵ�����
    HasPtr &operator=(const string &);      // ������ string
    string &operator*();                    // ������
    ~HasPtr();                              // ��������
private:
    std::string *ps;
    int i;
};

HasPtr::HasPtr(const HasPtr &orig) :
        ps(new std::string(*orig.ps)), i(orig.i) { }

HasPtr& HasPtr::operator=(const HasPtr &rhs) {
    std::string *newps = new std::string(*rhs.ps);  // ����ָ��ָ��Ķ���
    delete ps;                                      // ����ԭ string
    ps = newps;                                     // ָ���� string
    i = rhs.i;                                      // ʹ�����õ� int ��ֵ
    return *this;                                   // ����һ���˶��������
}

HasPtr& HasPtr::operator=(const string &rhs) {
    *ps = rhs;
    return *this;
}

string& HasPtr::operator*() {
    return *ps;
}

HasPtr::~HasPtr() {
    delete ps;          // �ͷ� string �ڴ�
}

#endif