#ifndef TEST_STRBLOB_H
#define TEST_STRBLOB_H

#include<vector>
#include<string>
#include<memory>
#include<exception>

using std::initializer_list;
using std::make_shared;
using std::out_of_range;
using std::runtime_error;
using std::shared_ptr;
using std::string;
using std::vector;
using std::weak_ptr;


// ��StrBlob�е���Ԫ��˵����ǰ�������Ǳ�Ҫ��
class StrBlobPtr;
class StrBlob{
public:
    typedef vector<string>::size_type size_type;
    friend class StrBlobPtr;

public:
    StrBlob();
    StrBlob(initializer_list<string> il);
    size_type size() { return data->size(); }
    bool empty() { return data->empty(); }
    // ��Ӻ�ɾ��Ԫ��
    void push_back(const string &t) { data->push_back(t); }
    void push_back(string &&t) { data->push_back(std::move(t)); }
    void pop_back();

    void push_back(const string &t) const;              //��ʹ�õ�ԭ��վ��ʹ���ߵĽǶ�Ӧ�ô������const vector
    void pop_back(const string &t) const;               //������ʼ��ϵ����ӽ���

    // Ԫ�ط���
    string& front();
    string& back();
    const string& front() const;                        //�Գ������������
    const string& back() const;

    // �ṩ��StrBlobPtr�Ľӿ�
    // ����ָ����Ԫ�غ�β��Ԫ�ص�StrBlobPtr
    StrBlobPtr begin();                                 //����StrBlobPtr����ܶ�������������
    StrBlobPtr end();                                   //StrBlob�������;ͻ���뺯���壬������ﶨ��Ļ��ᱨ��
    StrBlobPtr begin() const;                           //�Գ������������, cbegin�ŷ���const��strblobptr
    StrBlobPtr end() const;


private:
    shared_ptr<vector<string>> data;
    // ���data[i]���Ϸ����׳�һ���쳣
    void check(size_type i, const string &msg) const;   //���ߺ���������Ƿ��ںϷ���Χ�ڣ�msg�����˴�������
};



//.cpp�е�����

StrBlob::StrBlob():
    data(make_shared<vector<string>>()) { }             //�ڶ�̬�ڴ���Ĭ�Ϸ���һ���յ�vector

StrBlob::StrBlob(initializer_list<string> il):
    data(make_shared<vector<string>>(il)) { }           //�ڶ�̬�ڴ���ʹ���б��ʼ������һ��vector

void StrBlob::check(size_type i, const string &msg) const{
    if(i>=data->size())
        throw out_of_range(msg);
}

string& StrBlob::front(){
    check(0, "front on empty StrBlob");
    return data->front();
}

const string& StrBlob::front()const{
    check(0, "front on empty StrBlob");
    return data->front();
}

string& StrBlob::back(){
    check(0, "back on empty StrBlob");
    return data->back();
}

const string& StrBlob::back()const{
    check(0, "back on empty StrBlob");
    return data->back();
}

void StrBlob::pop_back(){
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}


// ����ֻ��һ��shared_ptr��Ա����˿�������ֵ�����ٵĶ���������ݳ�Ա��
// �Ӷ�ʵ�ֶ��StrBlob��ָ��һ��vector��Ŀ��


// �˲�ָ����StrBlobPtr, �Է���һ��������Ԫ�صĳ��ԣ�StrBolobPtr���׳��쳣
class StrBlobPtr{
    friend bool eq(const StrBlobPtr &, const StrBlobPtr &);

public:
    StrBlobPtr():curr(0){ }
    StrBlobPtr(StrBlob &a, size_t sz = 0):
            wptr(a.data),curr(sz){}
    StrBlobPtr(const StrBlob &a, size_t sz = 0):
            wptr(a.data),curr(sz){}
    string& deref() const;
    StrBlobPtr& incr();
    StrBlobPtr& decr();

private:
    size_t curr;
    weak_ptr<vector<string>> wptr;                      //ע�⣺ʹ��weak_ptrǰ��Ҫ���
    shared_ptr<vector<string>> check(size_t, const string &) const;
};

bool eq(const StrBlobPtr &, const StrBlobPtr &);



//.cpp�ļ�����
shared_ptr<vector<string>> StrBlobPtr::check(size_t i, const string &msg) const{
    auto ret = wptr.lock();
    if(!ret)
        throw runtime_error("unbound StrBlobPtr");
    if(i>=ret->size())
        throw out_of_range(msg);
    return ret;                                         //���򣬷���ָ��vector��shared_ptr
}

string& StrBlobPtr::deref() const{
    auto ret = check(curr, "dereference past end");
    return (*ret)[curr];
}

StrBlobPtr& StrBlobPtr::incr() {
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;                                       //ǰ�õ�������������������Ϊ��ֵ
}

StrBlobPtr& StrBlobPtr::decr(){
    --curr;
    check(curr, "decrement past begin of SrtBlobPtr");     //�����ϵĴ���汾(ȷʵд����)
    return *this;
    // if(curr == 0)
        // throw out_of_range("decrement past begin of StrBlobPtr");
}

//StrBlob��begin��end��Ա�Ķ���
StrBlobPtr StrBlob::begin(){
    return StrBlobPtr(*this);
}

StrBlobPtr StrBlob::end(){
    return StrBlobPtr(*this, data->size());
}

StrBlobPtr StrBlob::begin()const{
    return StrBlobPtr(*this);
}

StrBlobPtr StrBlob::end()const{
    return StrBlobPtr(*this, data->size());
}


//StrBlobPtr�ıȽϲ���
bool eq(const StrBlobPtr &lhs, const StrBlobPtr &rhs){
    auto l = lhs.wptr.lock(), r = rhs.wptr.lock();
    //���ײ��vector��ͬһ��
    if(l==r)
        return (!r || lhs.curr == rhs.curr);            //��ָ�붼Ϊ�գ���ָ����ͬԪ��ʱ�����
    else
        return false;                                   //ָ��ͬԪ����ɿ϶�����
}

bool neq(const StrBlobPtr &lhs, const StrBlobPtr &rhs){
    return !eq(lhs, rhs);
}


#endif                                  //TEST_STRBLOB_H