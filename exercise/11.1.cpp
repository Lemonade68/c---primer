#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<iterator>
#include<cctype>
#include<map>
#include<set>

using namespace std;


string &trans(string &s) {                      //string�ĺ������������±����
    for (int p = 0; p < s.size(); ++p) {
        if (s[p] >= 'A' && s[p] <= 'Z')
            s[p] += ('a' - 'A');
        else if (s[p] == ',' || s[p] == '.')
            s.erase(p, 1);                      // string.erase(pos,len)
    }
    return s;
}


void func_3(){
    map<string, size_t> word_count;
    set<string> exclude{"The", "But", "And", "Or", "An", "A",
                        "the", "but", "and", "or", "an", "a"};
    string word;
    while(cin>>word){
        // if(find(exclude.cbegin(),exclude.cend(),word) == exclude.cend())     //��������������ʹ�÷����㷨��̫��
        if(exclude.find(word) == exclude.end())     //ʹ��set��find��Ա����
            ++word_count[word];
    }
    for(const auto &s:word_count)
        cout << s.first << " occurs " << s.second << (s.second > 1 ? " times" : " time") << endl;
}


void func_4(){
    map<string, size_t> word_count;
    set<string> exclude{"The", "But", "And", "Or", "An", "A",
                        "the", "but", "and", "or", "an", "a"};
    string word;
    while(cin>>word){
        // tolowerǰһ��Ҫ�� ::  ǿ����c�汾��tolower�����ӵĻ��������޷�������std�Ļ���c��
        // std::toupper���ܵ���int���͵�һ��ֵ����char����ת��int, string���У�
        transform(word.begin(), word.end(), word.begin(), ::tolower);   //::toupper����():����ν�ʣ�
        if(*word.rbegin() == '.' || *word.rbegin() == ',')              //ע��string�����������÷��ص���char
            word.erase(word.end() - 1, word.end());                     //erase�����ܷ����������Ϊ����
        
        if(exclude.find(word) == exclude.end())     
            ++word_count[word];
    }
    for(const auto &s : word_count)
        cout << s.first << " occurs " << s.second << (s.second > 1 ? " times" : " time") << endl;
}


void func_4_another_method() {
    // ͳ��ÿ�������������г��ֵĴ���
    map<string, size_t> word_count;     // string �� size_t �Ŀ� map
    string word;
    while (cin >> word)
        ++word_count[trans(word)];      // ��ȡ word �ļ������������ 1
    for (const auto &w : word_count)    // �� map �е�ÿ��Ԫ��
        cout << w.first << " occurs " << w.second << ((w.second > 1) ? " times" : " time") << endl;
}


// ʹ�ù�������insert��Աʵ��
void func_20(){
    string word;
    map<string, size_t> word_count;
    while(cin>>word){
        auto par = word_count.insert({trans(word), 1});
        if(!par.second)
            ++par.first->second;
        // ++word_count.insert({trans(word), 0}).first->second;        //��������һ��д����
    }
    for(const auto &s : word_count)
    cout << s.first << " occurs " << s.second << (s.second > 1 ? " times" : " time") << endl;
}


int main(){
    // func_3();
    // func_4();
    func_20();
    return 0;
}
