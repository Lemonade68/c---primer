#include<iostream>
#include<fstream>
#include<string>

std::istream &func(std::istream &is){
    std::string buf;
    while(is >> buf){
        std::cout << buf << std::endl;
    }
    is.clear();
    return is;
}


int main(){
    // std::cout << "��������  ֱ��ctrl+zΪֹ" << std::endl;
    // func(std::cin);
    std::ifstream in;
    std::string ifile("../text/8_testing.txt");        //���·��
    in.open(ifile);
    if(in)
        std::cout << "succ" << std::endl;
    else
        std::cout << "fail" << std::endl;
    return 0;
}