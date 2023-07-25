//��ʹ����İ汾

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <cstdlib>                  // Ҫʹ�� EXIT_FAILURE
#include "./make_plural.h"          // ./��ǰĿ¼    ../��Ŀ¼

using namespace std;

using line_no = vector<string>::size_type;
using wmType = map<string, set<line_no>>;
using wmIter = wmType::const_iterator;
using lineIter = wmType::mapped_type::const_iterator;
vector<string> file;                // �ļ�ÿ������
wmType wm;                          // ���ʵ��к� set ��ӳ��



string cleanup_str(const string &word) {        //ȫת��Сд�����������ŵ�Ӱ��
    string ret;
    for (string::const_iterator it = word.begin(); it != word.end(); ++it) {
        if (!ispunct(*it))
            ret += tolower(*it);
    }
    return ret;
}

void input_text(ifstream &is) {
    string text;
    while (getline(is, text)) {     // ���ļ���ÿһ��
        file.push_back(text);       // ��������ı�
        int n = file.size() - 1;    // ��ǰ�к�
        istringstream line(text);   // �����ı��ֽ�Ϊ����
        string word;
        while (line >> word) {      // ������ÿ������
            // ����ǰ�кŲ��뵽���к� set ��
            // ������ʲ��� wm �У���֮Ϊ�±��� wm �����һ��
            wm[cleanup_str(word)].insert(n);
        }
    }
}

ostream &query_and_print(const string &sought, ostream &os) {
    // ʹ�� find �������±�����������ҵ��ʣ����⽫������ӵ� wm �У�
    wmIter loc = wm.find(cleanup_str(sought));
    if (loc == wm.end()) {          // δ�ҵ�
        os << sought << " ������ 0 ��" << endl;
    } else {
        wmType::mapped_type lines = loc->second;   // �к� set
        os << sought << " ������ " << lines.size() << " ��" << endl;
        for (line_no num : lines)
            os << "\t���� " << num + 1 << " �У�"
               << *(file.begin() + num) << endl;
    }
    return os;
}

void runQueries(ifstream &infile) {
    // infile ��һ�� ifstream��ָ������Ҫ��ѯ���ļ�
    input_text(infile);     // �����ı���������ѯ map
    // ���û���������ʾ�û�����Ҫ��ѯ�ĵ��ʣ���ɲ�ѯ����ӡ���
    do {
        cout << "enter word to look for, or q to quit: ";
        string s;
        // �������ļ�β���û������� q ʱѭ����ֹ
        if (!(cin >> s) || s == "q")
            break;
        query_and_print(s, cout) << endl;
    } while (true);
}

// �������Ψһ�������в�������ʾ�ı��ļ���
int main(int argc, char **argv) {
    // ��Ҫ��ѯ���ļ�
    ifstream infile("../../text/12_testing.txt");
    // ���ļ�ʧ�ܣ������쳣�˳�
    if (!infile) {
        cerr << "No input file!" << endl;
        return EXIT_FAILURE;
    }
    runQueries(infile);
    return 0;
}
