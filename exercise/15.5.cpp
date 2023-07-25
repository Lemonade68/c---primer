#include <iostream>

// ��ϰ15.20
class Base {
public:
    void pub_mem();         // public ��Ա
protected:
    int prot_mem;           // protected ��Ա
private:
    int priv_mem;           // private ��Ա
};

struct Pub_Derv : public Base {
    // ��ȷ���������ܷ��� protected ��Ա
    int f() { return prot_mem; }
    // ����private ��Ա������������˵�ǲ��ɷ��ʵ�
    // char g() { return priv_mem; }

    void memfcn(Base &b) {
        b = *this;
        std::cout << "Pub_Derv" << std::endl;
    }
};

struct Priv_Derv : private Base {
    // private ��Ӱ��������ķ���Ȩ��
    int f1() { return prot_mem; }

    void memfcn(Base &b) {
        b = *this;
        std::cout << "Priv_Derv" << std::endl;
    }
};

struct Prot_Derv : protected Base {
    int f2() { return prot_mem; }

    void memfcn(Base &b) {
        b = *this;
        std::cout << "Prot_Derv" << std::endl;
    }
};

struct Derived_from_Public : public Pub_Derv {
    // ��ȷ��Base::prot_mem �� Pub_Derv ����Ȼ�� protected ��
    int use_base() { return prot_mem; }

    void memfcn(Base &b) {
        b = *this;
        std::cout << "Derived_from_Public" << std::endl;
    }
};

struct Derived_from_Private : public Priv_Derv {
//     ����Base::prot_mem �� Priv_Derv ����Ȼ�� private ��
//     int use_base() { return prot_mem; }

// Base �޷����ʡ���Ϊ Priv_Derv : private Base, Priv_Derv ��
// ˽�з�ʽ�̳е� Base��Priv_Derv �������� Derived_from_Private
// ��Ȩ������ֱ�ӻ��� Priv_Derv ��˽�г�Ա
//    void memfcn(Base &b) {
//        b = *this;
//        std::cout << "Derived_from_Private" << std::endl;
//    }
};

struct Derived_from_Protected : public Prot_Derv {
    // ��ȷ��Base::prot_mem �� Prot_Derv ����Ȼ�� protected ��
    int use_base() { return prot_mem; }

    void memfcn(Base &b) {
        b = *this;
        std::cout << "Derived_from_Protected" << std::endl;
    }
};



int main() {
    Pub_Derv d1;            // �̳��� Base �ĳ�Ա�� public ��
    Priv_Derv d2;           // �̳��� Base �ĳ�Ա�� private ��
    Prot_Derv d3;           // �̳��� Base �ĳ�Ա�� protected ��

    // ��ϰ 15.18
    Derived_from_Public dd1;
    Derived_from_Private dd2;
    Derived_from_Protected dd3;
    Base base;
    Base *p = new Base;
    p = &d1;                // d1 �������� Pub_Derv
    // p = &d2;                // d2 �������� Priv_Derv
    // p = &d3;                // d3 �������� Prot_Derv
    p = &dd1;               // dd1 �������� Derived_from_Public
    // p = &dd2;               // dd2 �������� Derived_from_Private
    // p = &dd3;               // dd3 �������� Derived_from_Protected

    // ��ϰ 15.19
    d1.memfcn(base);
    d2.memfcn(base);
    d3.memfcn(base);
    dd1.memfcn(base);
    // dd2.memfcn(base);
    dd3.memfcn(base);

    return 0;
}