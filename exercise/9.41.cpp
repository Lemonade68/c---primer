#include<iostream>
#include<string>
#include<vector>

int main(){
    std::vector<char> vec{'a', 'b', 'c', 'd'};
    
    //����������ָ�룡
    // std::string s(vec.cbegin(), 4);

    // data��Ա��������vector�������׵�ַ
    std::string s(vec.data(), vec.size());
    
    s.push_back('e');       // push_backֻ֧�ֵ�Ԫ�أ��ַ���
    s.append("fgh");        // append֧�ֵ�Ԫ�����Ԫ�أ��������ַ�����
    s.append("i");

    std::cout << s << std::endl;
    return 0;
}