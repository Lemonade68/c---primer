#include<iostream>
#include<string>
#include<forward_list>
#include<vector>
using namespace std;

void func(forward_list<string> &l, const string &s1, const string &s2){
    auto pre = l.before_begin();
    auto cur = l.begin();
    while(cur != l.end()){
        if(*cur == s1){
            cur = l.insert_after(cur, s2);
            ++pre;
            return;
        }
        else{
            ++cur;
            ++pre;
        }

    }
    cur = l.insert_after(pre, s2);          // ���ﴫ����pre, cur�Ѿ���end�ˣ����Ԫ�صĺ�һ����
}

int main(){
    vector<string> vec;
    string s;
    cout << "����һ�����ʣ�" << endl;
    while(cin>>s && s!="Q")
        vec.push_back(s);
    forward_list<string> l(vec.cbegin(),vec.cend());    // �����б��ʼ���ķ�ʽ 
    string s1("good"),s2("XDU");
    cout << "������������s1,s2:" << endl;            // Ϊʲô���治��Q������ctrl+zʱ  ����������ֱ�ӳ������
    cin >> s1 >> s2;
    func(l, s1, s2);
    for(auto a: l)
        cout << a << " ";
    cout << endl;
    return 0;
}