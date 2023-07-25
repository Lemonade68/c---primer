// �������汾�ļ�opp�ļ���

#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<map>
#include<set>
#include<memory>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::istringstream;
using std::map;
using std::ostream;
using std::set;
using std::shared_ptr;
using std::string;
using std::vector;


class QueryResult;

class TextQuery{
public:
    using line_no = vector<string>::size_type;          //���ͱ�������ʾ�кţ���vector�е��±�
    TextQuery() = default;
    TextQuery(ifstream &);                              //��дIO������ı���״̬����˲�����ʹ��const������ 
    QueryResult query(const string &) const;

private:
    shared_ptr<vector<string>> file;                    //�����ļ�
    map< string, shared_ptr<set<line_no>> > wm;         //word_map
};

TextQuery::TextQuery(ifstream &is): file(new vector<string>) {
    string text;
    while(getline(is,text)){
        file->push_back(text);
        int n = file->size() - 1;                       //��ǰ�к�
        istringstream line(text);
        string word;
        while(line>>word){
            auto &lines = wm[word];                     //ʹ��lines��Ϊ���
            if(!lines)                                  //��һ������wordʱ��wm[word]ֵ��ʼ��Ϊ��ָ��
                lines.reset(new set<line_no>);
            lines->insert(n);                           //��Ϊ��set���������һ�����ʶ�γ�����ͬһ�У�insert�����ظ�����
        }
    }
}



class QueryResult{                                  //һ�����ʶ�Ӧ�����в�ѯ�����
    friend ostream &print(ostream &, const QueryResult &);
public:
    QueryResult(string s, shared_ptr<set<TextQuery::line_no>> p, shared_ptr<vector<string>> f):
        sought(s),lines(p),file(f) { }              //�����߸�������ָ����

private: 
    string sought;   //��ѯ����
    shared_ptr<set<TextQuery::line_no>> lines;      //���ֵ��к�set
    shared_ptr<vector<string>> file;                //�����ļ���Ӧ�ı�
};


QueryResult TextQuery::query(const string &sought)const{            //��sought����map�ж����к�set
    static shared_ptr<set<line_no>> nodata(new set<line_no>);       //��Ӧ�Ҳ������ĵ���
    //ʹ��find���ҵ��ʣ����⽫������ӵ�wm��
    auto loc = wm.find(sought);
    if(loc == wm.end())
        return QueryResult(sought, nodata, file);           //δ�ҵ������������һ���յ��к�set��shared_ptr
    else
        return QueryResult(sought, loc->second, file);      //�ҵ�������wm��pair�е�shared_ptr
}


inline string make_plural(size_t ctr, const string &word, const string &ending){
    return ctr > 1 ? word + ending : word;
}

ostream &print(ostream &os, const QueryResult &qr){
    //�����������������"word"Ϊʲô���У�
    os << endl;
    os << qr.sought << " occurs " << qr.lines->size() 
        << make_plural(qr.lines->size()," time","s") << endl;
    for(auto num : *qr.lines)                               //���qr.lines��һ��shared_ptr��������֮�����set
        os << "\t(line " << num + 1 << ")  " << *(qr.file->begin() + num) << endl;
    return os;
}


void runQueries(std::ifstream &infile){
    TextQuery tq(infile);
    while(true){
        cout << "enter word to look for, or q to quit: ";
        string s;
        if(!(cin>>s) || s == "q")
            break;
        print(cout, tq.query(s)) << endl;
    }
    cout << "Thank you! Have a nice day :D" << endl;
}


int main(){
    ifstream infile("../text/12_testing.txt");
    if(!infile){
        std::cerr << "failed to open file" << endl;
        return -1;
    }
    runQueries(infile);
    return 0;
}