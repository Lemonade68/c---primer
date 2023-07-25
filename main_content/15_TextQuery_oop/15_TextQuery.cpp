#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<map>
#include<set>
#include<memory>
#include<algorithm>
#include<iterator>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::istringstream;
using std::make_shared;
using std::map;
using std::ostream;
using std::set;
using std::set_intersection;
using std::shared_ptr;
using std::string;
using std::vector;


class QueryResult;

// �����ļ���ͬʱ�������ļ���Ӧ��word_map��֮��ʹ�ã�����map<word,word���ֵ��еļ��ϵ�ָ��>
class TextQuery{
public:
    using line_no = vector<string>::size_type;          //���ͱ�������ʾ�кţ���vector�е��±�
    TextQuery() = default;
    TextQuery(ifstream &);                              //��дIO������ı���״̬����˲�����ʹ��const������ 
    QueryResult query(const string &) const;            //��word_map�в��Ҵ���ĵ��ʣ�����QueryResult����

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
            auto &lines = wm[word];                     //ʹ��lines��Ϊ��ƣ�lines��Ӧ����һ��shared_ptr������ʹ��new����ʼ��
            if(!lines)                                  //��һ������wordʱ����wm[word]ֵ��ʼ��Ϊ��ָ��
                lines.reset(new set<line_no>);
            lines->insert(n);                           //��Ϊ��set���������һ�����ʶ�γ�����ͬһ�У�insert�����ظ�����
        }
    }
}



class QueryResult{                                      //һ�����ʶ�Ӧ�����в�ѯ�����
    friend ostream &print(ostream &, const QueryResult &);
public:
    typedef set<TextQuery::line_no>::const_iterator line_it;
    QueryResult(string s, shared_ptr<set<TextQuery::line_no>> p, shared_ptr<vector<string>> f):
        sought(s),lines(p),file(f) { }                  //�����߸�������ָ����
    
    //����������µĳ�Ա
    line_it begin() const { return lines->begin(); }
    line_it end() const { return lines->end(); }
    shared_ptr<vector<string>> get_file() { return file; }

private: 
    string sought;                                      //��ѯ����
    shared_ptr<set<TextQuery::line_no>> lines;          //���ֵ��к�set
    shared_ptr<vector<string>> file;                    //�����ļ���Ӧ�ı�
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


//15.9����

// 1. �ӿ����������� 

class Query;

//Query_base�࣬�ǳ�����࣬����Ĳ�ѯ���ʹ������������г�Ա����private��(���û�����)
class Query_base{
    friend class Query;                     //Query��Ҫ����Query_base���麯��
protected:
    using line_no = TextQuery::line_no;     //����eval����
    virtual ~Query_base() = default;        //��ʽ�ر����������������������
private:
    //eval�����뵱ǰQueryƥ���QueryResult    e-value ��ֵ
    virtual QueryResult eval(const TextQuery &) const = 0;
    //rep�Ǳ�ʾ��ѯ��һ��string
    virtual std::string rep() const = 0;
};


//����һ������Query_base�̳���ϵ�Ľӿ���
class Query{
    //��Щ�������Ҫ����shared_ptr�Ĺ��캯�������ú�����˽�е�
    friend Query operator~(const Query &);
    friend Query operator|(const Query &, const Query &);
    friend Query operator&(const Query &, const Query &);
public:
    Query(const string &);                              //����һ���µ�WordQuery�����໹δ���壩
    //�ӿں��������ö�Ӧ��Query_base����
    QueryResult eval(const TextQuery &t) const { return q->eval(t); }
    string rep() const { return q->rep(); }
private:
    Query(shared_ptr<Query_base> query) : q(query){ }   //��ϣ���û���㶨��Query_base���󣬷�˽�У������������ʹ��
    shared_ptr<Query_base> q;                           //����Ϊ������࣬�������Ե�����������麯��
};

//������������
ostream& operator<<(ostream &os, const Query &query){
    //Query::rep()ͨ������Query_baseָ���rep()�����������
    return os << query.rep();
}




// 2.������

//word_query�ࣺ�ڸ�����text_query������ʵ��ִ�в�ѯ��Ψһ����
class WordQuery : public Query_base{
    friend class Query;                                 //Queryʹ��WordQuery���캯��
    WordQuery(const string &s) : query_word(s){ }
    //������ࣺword_query���������м̳ж����Ĵ��麯��
    QueryResult eval(const TextQuery &t) const override { return t.query(query_word); }
    string rep() const override { return query_word; }
    string query_word;                  //Ҫ���ҵĵ���
};

inline Query::Query(const string &s) : q(new WordQuery(s)) { }


//NotQuery�༰~�������~����һ��NotQuery�����б���һ����Ҫ����ȡ����Query
class NotQuery : public Query_base{
    friend Query operator~(const Query &);
    NotQuery(const Query &q) : query(q){ }
    //������ࣺnot_query���������м̳ж����Ĵ��麯��
    string rep() const override { return "~(" + query.rep() + ")"; }
    QueryResult eval(const TextQuery &) const override;
    Query query;                    //�����ǵ�����Ҳ������binaryquery�������࣬���ͳһʹ��Query��ʹ��Query�Ļ�ʡȥ��ָ�����������ʹ�ýӿ��������Լ�����
};

Query operator~(const Query &operand){
    return shared_ptr<Query_base>(new NotQuery(operand));   //ʹ�ý���shared_ptr��Query���캯��
}


//BinaryQuery��
class BinaryQuery : public Query_base{
protected:
    BinaryQuery(const Query &l, const Query &r, string s): lhs(l), rhs(r), opSym(s) { }     //Query_baseû�����ݳ�Ա������Ҫ���캯����ʼ��
    //������, BinaryQuery������eval�����Ǽ̳�eval������麯�������ܴ���BinaryQuery����
    string rep() const override { return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")"; }
    Query lhs, rhs;                 //���Ҳ��������
    string opSym;                   //���������
};


//AndQuery��
class AndQuery : public BinaryQuery{
    friend Query operator&(const Query &, const Query &);
    AndQuery(const Query &left, const Query &right) : BinaryQuery(left,right, "&") { }
    //������ࣺAndQuery�̳���rep��������eval������麯��
    QueryResult eval(const TextQuery &) const override;
};

Query operator&(const Query &lhs, const Query &rhs){
    return shared_ptr<Query_base>(new AndQuery(lhs, rhs));  //ʹ�ý���shared_ptr��Query���캯��
}


//OrQuery��
class OrQuery : public BinaryQuery{
    friend Query operator|(const Query &, const Query &);
    OrQuery(const Query &left, const Query &right) : BinaryQuery(left, right, "|") { }
    //������ࣺOrQuery�̳�rep������eval
    QueryResult eval(const TextQuery &) const override;
};

Query operator|(const Query &lhs, const Query &rhs){
    return shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}



//eval����

//OrQuery::eval
QueryResult OrQuery::eval(const TextQuery &text) const{
    //ͨ��Query��Աlhs��rhs���е������
    //����eval����ÿ����������QueryResult
    auto right = rhs.eval(text), left = lhs.eval(text);
    //�����������󿽱������set��
    auto ret_lines = make_shared<set<line_no>>(left.begin(), left.end());
    //�����Ҳ������к�
    ret_lines->insert(right.begin(), right.end());
    //����һ���µ�QueryResult��ʾlhs��rhs�Ĳ���
    return QueryResult(rep(), ret_lines, left.get_file());      //right.get_file()Ҳ����
}


//AndQuery::eval
QueryResult AndQuery::eval(const TextQuery &text) const{
    //ͨ��Query���������е�����ã��Ի���������Ĳ�ѯ���set
    auto left = lhs.eval(text), right = rhs.eval(text);
    //����left��right������set
    auto ret_lines = make_shared<set<line_no>>();
    //��������Χ�Ľ���д��һ��Ŀ�ĵ�������
    //���ε��õ�Ŀ�ĵ�������ret���Ԫ��
    set_intersection(left.begin(), left.end(), right.begin(), right.end(), std::inserter(*ret_lines, ret_lines->begin()));
    return QueryResult(rep(), ret_lines, left.get_file());
}


//NotQuery::eval
QueryResult NotQuery::eval(const TextQuery& text)const{
    //ͨ��Query��������eval���������
    auto result = query.eval(text);
    //��ʼʱ���setΪ��
    auto ret_lines = make_shared<set<line_no>>();
    //���Ǳ��������������ֵ��������н��е���
    auto beg = result.begin(), end = result.end();
    //���������ļ���ÿһ�У�������в���result���У�������ӵ�ret_lines
    auto sz = result.get_file()->size();
    for (size_t n = 0; n != sz; ++n){
        //������ǻ�û�д�����result��������
        //��鵱ǰ���Ƿ����
        if(beg == end || *beg != n)     //��ΪsetĬ���Ǵ�С��������
            ret_lines->insert(n);       //�������result�У������һ��
        else if(beg != end)
            ++beg;
    }
    return QueryResult(rep(), ret_lines, result.get_file());
}
