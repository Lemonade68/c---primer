// ���ֻ����ϰ13.13

#include <iostream>
#include <vector>

using namespace std;

struct X {
    X() { cout << "���캯�� X()" << endl; }
    X(const X &) { cout << "�������캯�� X(const X &)" << endl; }
    X &operator=(const X &rhs) {
        cout << "������ֵ����� =(const X &)" << endl;
        return *this;
    }
    ~X() { cout << "�������� ~X()" << endl; }
};

void f1(X x) { }
void f2(X &x) { }

int main() {
    cout << "�ֲ�������" << endl;
    X x;
    cout << endl;

    cout << "�����ò������ݣ�" << endl;
    f1(x);
    cout << endl;

    cout << "���ò������ݣ�" << endl;
    f2(x);
    cout << endl;

    cout << "��̬���䣺" << endl;
    X *px = new X;                  //ʹ����Ĭ�Ϲ��캯����
    cout << endl;

    cout << "��ӵ������У�" << endl;
    vector<X> vx;
    vx.push_back(x);
    cout << endl;

    cout << "�ͷŶ�̬�������" << endl;
    delete px;
    cout << endl;

    cout << "������ʼ���͸�ֵ��" << endl;
    X y = x;
    y = x;
    cout << endl;

    cout << "���������" << endl;

    // �����������������Ӧ  y,vector�е�xԪ��,x
    return 0;
}
