#include<iostream>
#include<fstream>
#include<sstream>
#include"../main_content/12_StrBlob.h"

using namespace std;

void func_19(){
    StrBlob b1;
    {
        StrBlob b2 = {"a", "an", "the"};
        b1 = b2;
        b2.push_back("about");
        cout << b2.size() << endl;
    }
    // b2 �ڻ�������ʧЧ������������ڻ�������
    // cout << b2.size() << endl;
    cout << b1.size() << endl;
    cout << b1.front() << " " << b1.back() << endl;

    const StrBlob b3 = b1;
    cout << b3.front() << " " << b3.back() << endl;

    cout << endl;

    for (auto iter = b1.end().decr(); neq(iter, b1.begin()); iter.decr())       //����ڼ���decr()���������ٴ�ͷ��
        cout << iter.deref() << " ";
    cout << endl;

    // ����д��
    for (auto iter = b1.begin(); neq(iter, b1.end()); iter.incr())
        cout << iter.deref() << " ";
    cout << endl;
}

// ����Ϊ��λ
void func_20(){
    ifstream in("../text/12_testing.txt");
    if(!in){
        cerr << "failed to open files" << endl;
        return;
    }
    StrBlob sb;
    string line;
    while(getline(in, line)){
        sb.push_back(line);
    }
    for (auto b = sb.begin(); neq(b,sb.end()); b.incr())
        cout << b.deref() << endl;
}

// �Ե���Ϊ��λ
void func_20_se(){
    ifstream in("../text/12_testing.txt");
    if(!in){
        cerr << "failed to open files" << endl;
        return;
    }
    StrBlob sb;
    string line, word;
    while(getline(in, line)){
        istringstream words(line);
        while(words>>word)
            sb.push_back(word);
    }
    for (auto b = sb.begin(); neq(b,sb.end()); b.incr())
        cout << b.deref() << endl;
}

void func_22(){
    const StrBlob b = {"Hello", "World", "!"};
    for (auto iter = b.begin(); neq(iter, b.end()); iter.incr())
        cout << iter.deref() << endl;
}


int main() {
    // func_19();
    // func_20();
    // func_20_se();
    func_22();
    return 0;
}