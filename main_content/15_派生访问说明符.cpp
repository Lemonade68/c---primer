//չʾ����������˵��������������������

#include<iostream>
using namespace std;

class A{
public:
    int pub_mem = 0;
private:
    int pri_mem = 1;
protected:
    int pro_mem = 2;

};

struct Pub : public A{
    int f1() { return pub_mem; }
    // int f2() { return pri_mem; }        //���ɷ���
    int f3() { return pro_mem; }
};

struct Pri : private A{
    int f1() { return pub_mem; }
    // int f2() { return pri_mem; }        //���ɷ���
    int f3() { return pro_mem; }
};

int main() {
    Pub pub;
    Pri pri;

    // f1 f3���ڶ��߶��Զ���public�ģ��������඼���Է���A�е�public��protected��Ա
    // ���Ƕ���A�е��������������еĳ�Ա��
    // pub_mem����Pub���Ե��ڹ�����Ա������pub���Է��ʣ� ����Pri���Ե���˽�г�Ա������pri���ɷ���
    // pri_mem����Pub��Pri����˽�г�Ա������pub��pri�����ɷ���
    // pro_mem������protected�Ķ��壬����pub��pri�����ɷ���
    
    cout << pub.f1() << " " << pub.f3() << " " << endl;
    cout << pub.pub_mem << endl;            //���Է���
    // cout << pub.pri_mem << endl;            //���ɷ���
    // cout << pub.pro_mem << endl;            //���ɷ���

    cout << pri.f1() << " " << pri.f3() << " " << endl;
    // cout << pri.pub_mem << endl;            //���ɷ���
    // cout << pri.pri_mem << endl;            //���ɷ���
    // cout << pri.pro_mem << endl;            //���ɷ���
    
    return 0;
}