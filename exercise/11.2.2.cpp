#include<iostream>
#include<sstream>           //sstreamͷ�ļ������stringͷ�ļ������û����Ҳû��
#include<fstream>
#include<list>
// #include<algorithm>      //string��erase����������string����
#include<iterator>
#include<map>
// #include<cctype>         //���������std::toupper����Ч��ǰ��std��ʡ��ʱ��

using namespace std;

void trans(string &s){                      //Ҫ�޸ģ�����const
    for (int p = 0; p < s.size(); ++p){     //��string��ÿһ���ַ�����
        if(s[p] >= 'A' && s[p] <= 'Z')
            s[p] = tolower(s[p]);           //����ʹ�õ���ctype.h��tolower��iostream����������
        else if(s[p]=='.' || s[p] ==',' || s[p]=='!')
            s.erase(p, 1);
    }
}

void func_9(){
    map<string, list<int>> mp;
    int line_ctr = 0;                       //��ʾ����
    string line,word;
    
    ifstream in("../text/11_words.txt");
    if(!in){
        cerr << "Failed to open file!" << endl;
        return;
    }

    while(getline(in, line)){
        ++line_ctr;
        istringstream is(line);             //��һ�е�string����ʹ��istringstream
        while(is >> word){
            trans(word);
            mp[word].push_back(line_ctr);   //��Ĭ�ϳ�ʼ��һ����list
        }
    }

    ostream_iterator<int> out(cout, " ");
    for(const auto &a : mp){                //�ǰ��ֵ����ӡ
        cout << "word: " << a.first << (a.second.size() > 1 ? " 's lines are: " : " 's line is: ");
        copy(a.second.begin(), a.second.end(), out);
        cout << endl;
    }
}

int main(){
    func_9();
    return 0;
}