#include<iostream>
#include<list>
#include<deque>

int main(){
    std::list<int> l{1, 2, 3, 4, 5, 6, 7};
    std::deque<int> odd, even;
    for (auto b = l.cbegin(); b != l.cend(); ++b){
        if(*b % 2 == 0)
            even.push_back(*b);
        else
            odd.push_back(*b);
    }
    for (const auto a : even){
        std::cout << a << std::endl;
    }
    for (const auto a : odd){
        std::cout << a << std::endl;
    }
    return 0;
}



// �ж�����ż����һ�������������һλʹ��λ����
// if (*lb & 1)        // �鿴���λ��1��������0��ż��
//     odd_d.push_back(*lb);
// else
//     even_d.push_back(*lb);