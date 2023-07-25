#include <iostream>

using namespace std;

class numbered {
private:
    static int seq;
public:
    numbered() { mysn = seq++; }
    // 13.15
    numbered(numbered &n) { mysn = seq++; }     //��func_16Ҫע�͵�
    int mysn;
};

int numbered::seq = 0;

// 13.16
void f(const numbered &s){          //���ô��ݰ汾
    cout << s.mysn << endl;
}

void f_16(const numbered s) {       //ֵ���ݰ汾
    cout << s.mysn << endl;
}



void func_14(){
    //�ǵý�11��ע�͵���ģ��û�п�����ֵ��������
    numbered a, b = a, c = b;
    f_16(a); f_16(b); f_16(c);
}

void func_15(){
    numbered a, b = a, c = b;
    f_16(a); f_16(b); f_16(c);
}

void func_16(){
    numbered a, b = a, c = b;
    f(a); f(b); f(c);
}

int main() {
    // func_14();
    // func_15();
    func_16();
    return 0;
}
