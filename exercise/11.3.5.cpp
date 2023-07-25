#include<iostream>
#include<string>
#include<vector>
#include<iterator>
#include<map>
#include<set>
#include<utility>

using namespace std;

void func_31(){
    multimap<string, string> books;
    books.insert({"wyq", "A"});
    books.insert({"wyq", "B"});
    books.insert({"wyq", "C"});
    books.insert({"wy", "D"});
    auto par = books.equal_range("wyq");
    if(par.first == par.second)
        cout << "Oops, failed to find the book of this author!" << endl;
    else
        books.erase(par.first, par.second);
    for(const auto &a : books)
        cout << a.first << " : " << a.second << endl;
}

//ʵ�ֹؼ���Ҳ���ֵ�������ķ���
void func_32_se(){
    std::multimap<string, string> authors{
        {"alan", "DMA"}, {"pezy", "LeetCode"},
        {"alan", "CLRS"}, {"wang", "FTP"}, 
        {"pezy", "CP5"}, {"wang", "CPP-Concurrency"}};
    /*
     * multimap Ĭ���ǰ��ؼ����ֵ������Ԫ�أ��������
     * Ҳ�ǹؼ����ֵ��򣻹ؼ��ֹ�����ֵ�޷���֤����
     */
    for (const auto &author : authors)
        std::cout << author.first << ": " << author.second << std::endl;
    std::cout << std::endl;
    /*
     * ���� map��ʵ�����ߺ���Ʒ��ӳ��
     * key_type ����Ϊ string
     * mapped_type ����Ϊ multiset<string>
     * map �� multiset �Ĺؼ����������
     * �����Ϳ���ʵ�����ߺ����������������
     */
    std::map<string, std::multiset<string>> m;
    // �� authors �е����߼������������뵽 m ��
    for (const auto& author : authors)
        m[author.first].insert(author.second);
    // ���� m��ʵ������������������Ҳ����
    // ��Ȼ���������ָ�����ֵ���
    for (const auto& s : m) {
        std::cout << s.first << ": ";
        for (const auto& b : s.second)
            std::cout << b << " ; ";
        std::cout << std::endl;
    }
}


int main(){
    // func_31();
    func_32_se();
    return 0;
}

