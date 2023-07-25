#ifndef hppl
#define hppl

#include<iostream>
#include<string>

using std::string;

class HasPtr{
public:
    //���캯�������µ�string���µļ�������������������Ϊ1
    HasPtr(const string &s = string()) : ps(new string(s)),i(0),use(new std::size_t(1)) { }
    //�������캯�����������������ݳ�Ա��������������
    HasPtr(const HasPtr &p) : ps(p.ps), i(p.i), use(p.use) { ++*use; }
    HasPtr &operator=(HasPtr &);
    ~HasPtr();

private:
    string *ps;
    int i;
    std::size_t *use;       //��̬��Ա����Ȼ��ֱ�ӷ���ģ���Ҳ��Ҫ������
};

HasPtr& HasPtr::operator=(HasPtr &p){
    ++*p.use;               //    ���������ԭ�򣺴����Ը�ֵ���
    if(--*use == 0){        //��������ǰ�棬���Ӧ�Ը�ֵ���������
        delete ps;
        delete use;
    }
    ps = p.ps;
    i = p.i;
    use = p.use;            //������ҲҪ����
    return *this;
}

HasPtr::~HasPtr(){
    if(--*use == 0){
        delete ps;          //�ͷ�string�ڴ�
        delete use;         //�ͷż������ڴ�
    }
}

#endif