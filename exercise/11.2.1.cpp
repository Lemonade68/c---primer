#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<utility>       

using namespace std;


//�����ӹؼ���ʱΪ��Ҫfind�������ֵʱ����Ҫʹ��find!

void add_family(map<string, vector<pair<string, string>>> &families, const string &family) {
    if (families.find(family) == families.end())
        families[family] = vector<pair<string,string>>();
}

// ���溯�����и��򵥵İ汾���£�����Ĭ�ϳ�ʼ��
// families[family];
// �Ѵ���family: ���ʶ��������κβ���
// ������family: Ĭ�ϳ�ʼ������ֵ�����ɿ�vector��

void add_child(map<string, vector<pair<string, string>>> &families, const string &family, const string &child, const string &birth) {
    families[family].push_back({child,birth});
}

//����Ϊ11.14Ҫ��İ汾
void func_7_se(){
    map<string, vector<pair<string, string>>> families;
    add_family(families, "��");
    add_child(families, "��", "ǿ", "2002.12.20");
    add_child(families, "��", "��", "2001.12.20");
    add_child(families, "��", "��", "2003.12.20");
    add_family(families, "��");
    for (auto f : families) {
        cout << f.first << "�ҵĺ��ӣ�";
        for (auto c : f.second)
            cout << f.first << c.first << " " << c.second << "; ";
        cout << endl;
    }
}

void func_7(){
    map<string, vector<string>> m = {{"A", {"A1", "A2"}},       // ע�����vector��ʼ��ʱҪ��{} 
                                     {"B", {"B1"}},
                                     {"C", {"C1", "C2", "C3"}}};
    string family,child;
    
    while(cin>>family && family != "Q"){
        if(m.find(family) == m.end()){                          // map��Ա��find����, ��Ȼ�Ļ����в��������ԭ������
            m[family] = vector<string>();                       // ��map[key]��Ա�������оͲ�����û�оʹ�����Ԫ��
        }
    }
    
    while(cin>>family>>child && family!="Q" && child!="Q"){
        m[family].push_back(child);
    }
    
    for(const auto &s : m){
        cout << "Family: " << s.first << (s.second.size() > 1 ? " Children: " : " Child: ");
        for(const auto &a : s.second)
            cout << a << " ";
        cout << endl;
    }
}


void func_8(){
    //ÿ�����ǰʹ��find��������
}


int main(){
    // func_7();
    func_7_se();
    return 0;
}

