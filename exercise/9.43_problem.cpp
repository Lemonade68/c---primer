#include <iostream>
#include <vector>
#include <string>

using namespace std;

void replace_string(string &s, const string &oldVal, const string &newVal) {
    // ������Ҳ������oldVal.size()
    // std::distance�������������������ľ���
    for (string::iterator beg = s.begin(); distance(beg, s.end()) >= distance(oldVal.begin(), oldVal.end()); ) {
        if (string{beg, beg + oldVal.size()} == oldVal) {
            beg = s.erase(beg, beg + oldVal.size());
            beg = s.insert(beg, newVal.cbegin(), newVal.cend());

            // ����һ��ͻ��׳�����????
            // s.replace(beg, beg + oldVal.size(), newVal);    // �þ�Ҳ�����ϱ��������
            
            advance(beg, newVal.size());            // std::advance  ��������ǰ��newval.size()����λ
        } else
            ++beg;
    }
}

int main() {
    string s = "tho thru tho!";
    replace_string(s, "thru", "through");
    cout << s << endl;

    replace_string(s, "tho", "though");
    cout << s << endl;

    replace_string(s, "through", "");
    cout << s << endl;

    return 0;
}
