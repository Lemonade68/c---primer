#include<iostream>
#include<string>
#include<algorithm>

class PrintString{
public:
    PrintString(std::ostream &o = std::cout, char c = ' '): 
        os(o),sep(c){}
    void operator()(const std::string &s) { os << s << sep; }

private:
    std::ostream &os;           //���ڲ��ܿ������������������
    char sep;                   //�ָ���
};


//���ã�
// std::string s("hello world");
// PrintString printer;
// printer(s);
// PrintString errors(std::cerr, '\n');
// errors(s);


//��������Ϊ�����㷨��ʵ�Σ���lambda��ͬ��
// std::for_each(vs.begin(), vs.end(), PrintString(cerr, '\n'));