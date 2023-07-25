#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<numeric>

void printstring(const std::vector<std::string> &s){
    for(const auto &a : s)
        std::cout << a << std::endl;
}

bool isShorter(const std::string &s1, const std::string &s2){       //��ν��
    return s1.size() < s2.size();
}


void eliminateDups(std::vector<std::string> &words){
    std::sort(words.begin(), words.end());                          //�ֵ�������
    auto it = std::unique(words.begin(), words.end());              //ȥ��
    words.erase(it, words.end());                                   //ɾ��
    std::stable_sort(words.begin(), words.end(), isShorter);
}


int main(){
    std::vector<std::string> s
        {"i", "have", "a", "pen", "you", "have", "a", "pen", "too"};
    eliminateDups(s);
    printstring(s);
    return 0;
}