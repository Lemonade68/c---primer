#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;

void func_20(){
    size_t count;
    vector<string> vec
        {"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};
    count = count_if(vec.begin(), vec.end(), [](const string &s)
             { return s.size() > 6; });
    cout << count << endl;
}

void func_21(){
    int a = 6;
    auto f = [&a] ()-> bool {if(a>0) {--a; return false;} else {return true;}};

    for (int i = 0; i < 10; ++i){
        bool flag = f();
        if(flag == true)
            cout << "=0 ";
        else
            cout << "!=0 ";
    }
    cout << endl;
}

void mutable_lambda() {
    int i = 5;
    // ����ʱ��i��һֱ���������lambda����������������У����ÿ��i--�����ϴεĻ����Ͻ���
    auto f = [i] () mutable -> bool {     
        if (i > 0) {
            --i;
            return false;
        } else
            return true;
    };

    for (int j = 0; j < 6; ++j)
        cout << f() << " ";
    cout << endl;
}


int main(){
    func_21();
    mutable_lambda();
    return 0;
}