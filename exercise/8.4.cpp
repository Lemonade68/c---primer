#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using std::ifstream;
using std::ofstream;

int main(){
    ifstream input("../text/8_testing.txt");
    if(!input){
        std::cerr << "�޷��������ļ�" << std::endl;
        return -1;
    }
    std::string line;
    std::vector<std::string> vec;
    while(std::getline(input, line)){
    // while(input >> line){            // 8.5 ��������ʹ��   istream����ֱ��>>�ǵ��ո��س���ֹͣ
        vec.push_back(line);
    }
    input.close();

    for(const auto &a : vec)
        std::cout << a << std::endl;

    return 0;
}



