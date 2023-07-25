#include<iostream>
#include<string>
#include<vector>


class Person{
private:
    std::string Name;        //����
    std::string Address;     //��ַ

public:
//Ĭ�Ϲ��캯������������ʵ�εĹ��캯�����ӱ�׼��������ȡ���ݵĹ��캯��
    Person() = default;
    Person(const std::string &name, const std::string &add):
        Name(name),Address(add) { }
    explicit Person(std::istream &is) { read(is, *this); }

    std::string get_name() const { return Name; }                       //���ı����ݳ�Ա��ֵ  �ó�����Ա����   ��const
    std::string get_address() const { return Address; }

    std::istream &read(std::istream &is, Person &p);             
    std::ostream &print(std::ostream &os, const Person &p);             //const������
};


std::istream &Person::read(std::istream &is, Person &p){                //���ⶨ���Ա������������Ҫ�ӣ�ʹ��get_name�ӿ�(�����޷��������ݳ�Ա)       
    is >> p.Name >> p.Address;
    return is;
}

std::ostream &Person::print(std::ostream &os, const Person &p){         //���ⶨ���Ա������������Ҫ�ӣ�ʹ��get_name�ӿ�
    os << p.Name << " " << p.Address;
    return os;
}
