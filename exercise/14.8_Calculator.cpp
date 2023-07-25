#include<iostream>
#include<string>
#include<functional>
#include<map>

//��ͨ����
int add(int i, int j) { return i + j; }

//lambda������һ��δ�����ĺ���������
auto mod = [](int i, int j){ return i % j; };

//����������
struct divide{
    int operator()(int d1, int d2) { return d1 / d2; }
};

// �о��˿ɵ��ö������Ԫ�������Ӧ��ϵ�ı��
// ���пɵ��ö��󶼱���������� int������һ�� int
// ���е�Ԫ�ؿ����Ǻ���ָ�롢����������� lambda
std::map<std::string, std::function<int(int, int)>> binops = {
    {"+", add},                                 // ����ָ��
    {"-", std::minus<int>()},                   // ��׼�⺯������
    {"*", [] (int i, int j) { return i * j; }}, // δ������ lambda
    {"/", divide()},                            // �û�����ĺ�������
    {"%", mod}                                  // �����˵� lambda ����
};


int main(){
    while(true){
        std::cout << "�����룺op1 op op2" << std::endl;
        int a, b;
        std::string c;
        std::cin >> a >> c >> b;
        //binops[c]����һ��function��function������operator()��ʹ�����������ݸ�����Ŀɵ��ö���
        std::cout << binops[c](a, b) << std::endl;      
    }
    return 0;
}