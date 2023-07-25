#include<iostream>
#include<memory>

using namespace std;

struct connection{ };
struct destination{ };
connection connect(destination *pd){
    cout << "connection begins" << endl;
    return connection();
}
void disconnect(connection c){
    cout << "connection ends" << endl;
}

void f_new(destination &d){
    cout << "manage connect directly" << endl;
    connection c = connect(&d);
    //�����������ǵ���disconnect���ر�����
    cout << "f_new finished" << endl;
}

void end_connection(connection *p){
    disconnect(*p);
}

void f_s_p(destination &d){
    cout << "manage connect with shared_ptr" << endl;
    connection c = connect(&d);
    shared_ptr<connection> p(&c, end_connection);       //ע����ߵ�������ʽ   1 ȡַ  2 deleter
    cout << "f_shared_ptr finished" << endl;
}

void f_sp_15(destination &d){
    cout << "manage connect with shared_ptr" << endl;
    connection c = connect(&d);
    shared_ptr<connection> p(&c, [](connection *p)      
                             { end_connection(p); });   //ʹ��lambda�汾
    cout << "f_shared_ptr finished" << endl;
}

void func_14(){
    destination d;
    f_new(d);
    cout << endl;
    f_s_p(d);
}

void func_15(){
    destination d;
    f_new(d);
    cout << endl;
    f_sp_15(d);
}

int main(){
    // func_14();
    func_15();
    return 0;
}