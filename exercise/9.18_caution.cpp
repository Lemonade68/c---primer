#include<iostream>
#include<string>
#include<deque>

int main(){
    std::string s;
    std::deque<std::string> q;
    while(std::cin >> s){
        q.push_back(s);
    }
    auto b = q.cbegin();

    // ���õ�ϰ�ߣ���������    ����漰��Ӻ�ɾ�����������ѭ���ᱨ�� 
    auto e = q.cend();                           


    // for (auto b = q.cbegin(), auto e = q.cend(); b != e; ++b)    //����
    for (; b != e; ++b)      //ע�⣺forѭ���е�һ���ֺ�ǰ��������������ͬ���͵�Ԫ�أ�ָ������ÿ��ԣ�
        std::cout << *b << std::endl;
    return 0;
}


//����init-statement�в�����eҲ��

// for (deque<string>::const_iterator db = sd.cbegin(); db != sd.cend(); ++db)
        // cout << *db << endl;