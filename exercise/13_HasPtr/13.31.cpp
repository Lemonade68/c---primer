#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
#include<sstream>
#include"HasPtr.h"
using namespace std;


// ���ܵ����⣺����������operator=���巽��   ����ӡsort
// ԭ�򣺶���sort���ԣ�ֻ������������һ��ֵʱ�Ż�ʹ�ÿ������򣬴Ӷ��õ�swap��
// ����ʹ��ֱ�Ӳ������򣬲�ʹ��swap

int main() {
    ifstream in("text.txt");
    if (!in) {
        cerr << "�޷��������ļ�" << endl;
        return -1;
    }
    vector<HasPtr> hvec;
    string line, word;
    while (getline(in, line)) {
        istringstream l_in(line);           // �����ַ���������ȡ����
        while (l_in >> word)
            hvec.push_back(word);
    }
    for (auto p : hvec)
        cout << *p << " ";
    cout << endl;
    sort(hvec.begin(), hvec.end());
    for (auto p : hvec)
        cout << *p << " ";
    cout << endl;

    return 0;
}