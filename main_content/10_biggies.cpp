//����������ȥ�غ������ȶ���������ӡ�����ȴ������볤�ȵĵ��ʸ���
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<functional>                    //bind������placeholders�����ռ�

using namespace std;
using namespace std::placeholders;      //ʹ��ռλ��

void prt(const vector<string> &s){
    for(const auto &a : s)
        cout << a << " ";
    cout << endl;
}

void elimDups(vector<string> &s){
    sort(s.begin(), s.end());
    auto it = unique(s.begin(), s.end());
    s.erase(it, s.end());
}

string make_plural(int count, const string &s1, const string &s2){
    return count > 1 ? s1 + s2 : s1;
}

bool check_size(const string &s, string::size_type sz){
    return s.size() >= sz;
}


// find_if�汾���ҵ���һ��ν�ʷ���true�ģ�ֻ����һԪν�ʣ�
void biggies_findif(vector<string> &words, vector<string>::size_type sz){
    elimDups(words);
    prt(words);
    stable_sort(words.begin(), words.end(),
                [](const string &s1, const string &s2)
                { return s1.size() < s2.size(); });
    prt(words);

    //������Ŀ
    
    //ʹ��lambda�汾
    // auto it = find_if(words.begin(), words.end(), 
                    // [sz](const string &s)
                    //   { return s.size() >= sz; });
    
    //ʹ��bind������check_size����
    auto it = find_if(words.begin(), words.end(),
                      bind(check_size, _1, sz));


    auto count = words.end() - it;
    cout << count << " " << make_plural(count, "word", "s") << " of length " << sz << " or longer" << endl;

    //ʹ��for_each������ӡ��Ӧ����
    for_each(it, words.end(), 
            [](const string &s)
             { cout << s << " "; });
    cout << endl;
}


// partition�汾��ǰ�󻮷�
void biggies_partition(vector<string> &words, vector<string>::size_type sz){
    elimDups(words);
    prt(words);

    // partition����Ҫstable_sort��

    //������Ŀ    ��partitionҲ���ԣ�
    auto it = stable_partition(words.begin(), words.end(), 
                    [sz](const string &s)            
                     { return s.size() >= sz; });
    auto count = it - words.begin();
    cout << count << " " << make_plural(count, "word", "s") << " of length " << sz << " or longer" << endl;

    //��ӡ��Ӧ����
    for_each(words.begin(), it, 
            [](const string &s)
             { cout << s << " "; });
    cout << endl;   

}

void func_24(const vector<string> &s, const string &str){
    auto it = find_if(s.begin(), s.end(), bind(check_size, _1, str.size()));
    cout << *it << endl;
}

int main(){
    vector<string> vec{"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};
    biggies_findif(vec, 5);
    cout << "-----------------------------------" << endl;
    biggies_partition(vec, 4);
    return 0;
}   