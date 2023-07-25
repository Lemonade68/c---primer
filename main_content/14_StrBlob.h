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
class ConstStrBlobPtr;

class StrBlob{
public:
    friend class StrBlobPtr;
    friend class ConstStrBlobPtr;
    friend bool operator==(const StrBlob &, const StrBlob &);
    friend bool operator!=(const StrBlob &, const StrBlob &);
    friend bool operator<(const StrBlob &s1, const StrBlob &s2);
    friend bool operator<=(const StrBlob &s1, const StrBlob &s2);
    friend bool operator>(const StrBlob &s1, const StrBlob &s2);
    friend bool operator>=(const StrBlob &s1, const StrBlob &s2);

public:
    typedef vector<string>::size_type size_type;
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
    
    // �ṩ�� ConstStrBlobPtr �Ľӿ�
    // ����ָ����Ԫ�غ�β��Ԫ�ص� ConstStrBlobPtr
    ConstStrBlobPtr cbegin() const;                     // ���� ConstStrBlobPtr ����ܶ�������������
    ConstStrBlobPtr cend() const;
    
    // StrBlobPtr cbegin() const;                           //�Գ������������, cbegin�ŷ���const��strblobptr
    // StrBlobPtr cend() const;

    //��ϰ14.26
    string &operator[](size_t n);
    const string &operator[](size_t n) const;

private:
    shared_ptr<vector<string>> data;
    // ���data[i]���Ϸ����׳�һ���쳣
    void check(size_type i, const string &msg) const;   //���ߺ���������Ƿ��ںϷ���Χ�ڣ�msg�����˴�������
};

bool operator==(const StrBlob &, const StrBlob &);
bool operator!=(const StrBlob &, const StrBlob &);
bool operator<(const StrBlob &s1, const StrBlob &s2);
bool operator<=(const StrBlob &s1, const StrBlob &s2);
bool operator>(const StrBlob &s1, const StrBlob &s2);
bool operator>=(const StrBlob &s1, const StrBlob &s2);



//.cpp�е�����

bool operator==(const StrBlob &lhs, const StrBlob &rhs){
    return lhs.data == rhs.data;
}

//ʹ�������==������
bool operator!=(const StrBlob &lhs, const StrBlob &rhs){
    return !(lhs == rhs);
}

bool operator<(const StrBlob &s1, const StrBlob &s2) {
    return *s1.data < *s2.data;
}

bool operator<=(const StrBlob &s1, const StrBlob &s2) {
    return *s1.data <= *s2.data;
}

bool operator>(const StrBlob &s1, const StrBlob &s2) {
    return *s1.data > *s2.data;
}

bool operator>=(const StrBlob &s1, const StrBlob &s2) {
    return *s1.data >= *s2.data;
}


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


string& StrBlob::operator[](size_t n){
    check(n, "out of range");
    return data->at(n);
}

const string& StrBlob::operator[](size_t n)const{
    check(n, "out of range");
    return data->at(n);
}




// �˲�ָ����StrBlobPtr, �Է���һ��������Ԫ�صĳ��ԣ�StrBolobPtr���׳��쳣
class StrBlobPtr{
    friend bool eq(const StrBlobPtr &, const StrBlobPtr &);
    friend bool operator==(const StrBlobPtr &, const StrBlobPtr &);
    friend bool operator!=(const StrBlobPtr &, const StrBlobPtr &);
    friend bool operator<(const StrBlobPtr &, const StrBlobPtr &);
    friend bool operator<=(const StrBlobPtr &, const StrBlobPtr &);
    friend bool operator>(const StrBlobPtr &, const StrBlobPtr &);
    friend bool operator>=(const StrBlobPtr &, const StrBlobPtr &);

public:
    StrBlobPtr():curr(0){ }
    StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data),curr(sz){}
    StrBlobPtr(const StrBlob &a, size_t sz = 0) : wptr(a.data),curr(sz){}
    string& deref() const;
    StrBlobPtr& incr();
    StrBlobPtr& decr();

    const string &operator[](size_t) const;
    //�����͵ݼ��������ע���޷���ͨ�������������ֺ�������
    StrBlobPtr &operator++();                           //ǰ�ð汾��û�в�������������
    StrBlobPtr &operator--();
    StrBlobPtr operator++(int);                         //���ð汾��int�������֣�������ֵ
    StrBlobPtr operator--(int);             
    
    // ��ϰ 14.28
    StrBlobPtr &operator+=(size_t);
    StrBlobPtr &operator-=(size_t);
    StrBlobPtr operator+(size_t) const;
    StrBlobPtr operator-(size_t) const;

    //��ϰ 14.30
    string &operator*() const;                          //���ڷǳ������󣺷���ֵ���޸�
    string *operator->() const;

private:
    size_t curr;
    weak_ptr<vector<string>> wptr;                      //ע�⣺ʹ��weak_ptrǰ��Ҫ���
    shared_ptr<vector<string>> check(size_t, const string &) const;
};

bool eq(const StrBlobPtr &, const StrBlobPtr &);
bool operator==(const StrBlobPtr &, const StrBlobPtr &);
bool operator!=(const StrBlobPtr &, const StrBlobPtr &);
bool operator<(const StrBlobPtr &s1, const StrBlobPtr &s2);
bool operator<=(const StrBlobPtr &s1, const StrBlobPtr &s2);
bool operator>(const StrBlobPtr &s1, const StrBlobPtr &s2);
bool operator>=(const StrBlobPtr &s1, const StrBlobPtr &s2);



//ָ���������constStrblobptr
class ConstStrBlobPtr {
    // ��ϰ 14.16
    friend bool operator==(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs);
    friend bool operator!=(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs);
    // ��ϰ 14.18
    friend bool operator<(const ConstStrBlobPtr &s1, const ConstStrBlobPtr &s2);
    friend bool operator<=(const ConstStrBlobPtr &s1, const ConstStrBlobPtr &s2);
    friend bool operator>(const ConstStrBlobPtr &s1, const ConstStrBlobPtr &s2);
    friend bool operator>=(const ConstStrBlobPtr &s1, const ConstStrBlobPtr &s2);

public:
    ConstStrBlobPtr() : curr(0) {}
    ConstStrBlobPtr(const StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}

    string& deref() const;
    ConstStrBlobPtr& incr();     // ǰ׺����
    ConstStrBlobPtr& decr();     // ��׺�ݼ�
    // ��ϰ 14.26
    const string &operator[](size_t) const;
    // ��ϰ 14.27
    ConstStrBlobPtr &operator++();       // ǰ�������
    ConstStrBlobPtr &operator--();
    ConstStrBlobPtr &operator++(int);    // ���������
    ConstStrBlobPtr &operator--(int);
    // ��ϰ 14.28
    ConstStrBlobPtr &operator+=(size_t);
    ConstStrBlobPtr &operator-=(size_t);
    ConstStrBlobPtr operator+(size_t) const;
    ConstStrBlobPtr operator-(size_t) const;
    // ��ϰ 14.30
    const string &operator*() const;
    const string *operator->() const;

private:
    // �����ɹ���check ����һ��ָ�� vector �� shared_ptr
    shared_ptr<vector<string>> check(size_t, const string&) const;
    // ����һ�� weak_ptr����ζ�ŵײ� vector ���ܻᱻ����
    weak_ptr<vector<string>> wptr;
    size_t curr;            // �������еĵ�ǰλ��
};
bool operator==(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs);
bool operator!=(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs);
bool operator<(const ConstStrBlobPtr &s1, const ConstStrBlobPtr &s2);
bool operator<=(const ConstStrBlobPtr &s1, const ConstStrBlobPtr &s2);
bool operator>(const ConstStrBlobPtr &s1, const ConstStrBlobPtr &s2);
bool operator>=(const ConstStrBlobPtr &s1, const ConstStrBlobPtr &s2);





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


//���������ذ汾
bool operator==(const StrBlobPtr &lhs, const StrBlobPtr &rhs){
    //weak_ptr����֧��operator==����
    auto l = lhs.wptr.lock(), r = rhs.wptr.lock();
    if(l == r)
        return (!r || lhs.curr == rhs.curr);    //��Ϊ������ȣ����߲�Ϊ������һ�����ݳ�Ա���Ҳ���
    else
        return false;                           //ָ��ͬ����϶������
}

bool operator!=(const StrBlobPtr &lhs, const StrBlobPtr &rhs){
    return !(lhs == rhs);
}


// ָ���<�Ƚϣ�����ָ��ͬһ�����У�Ȼ��Ƚ�ǰ��˳��
bool operator<(const StrBlobPtr &s1, const StrBlobPtr &s2) {
    auto l = s1.wptr.lock(), r = s2.wptr.lock();
    if (l == r) {
        if (!r)
            return false;               // ����ָ�붼Ϊ�գ���Ϊ�����
        return (s1.curr < s2.curr);     // ָ����ͬ vector���Ƚ�ָ��λ��
    } else {
        return false;                   // ָ��ͬ vector ʱ�����ܱȽ�
    }
}

// ѧϰ���˼�룬�����󲻰������õ� < �Ƚ�ʱ������һ��<��Ȼ������ > / <= / >= 
bool operator>(const StrBlobPtr &s1, const StrBlobPtr &s2) {
    return s2 < s1;
}

// �������ѧϰ
bool operator<=(const StrBlobPtr &s1, const StrBlobPtr &s2) {
    return !(s2 < s1);
}

bool operator>=(const StrBlobPtr &s1, const StrBlobPtr &s2) {
    return !(s1 < s2);
}

const string& StrBlobPtr::operator[](size_t n) const {
    auto p = check(n, "dereference out of range");
    return (*p)[n];
}

//ǰ�ð汾�����ض��������
StrBlobPtr& StrBlobPtr::operator++(){
    //����Ѿ�ָ��������β��λ�ã����޷�����������
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

StrBlobPtr& StrBlobPtr::operator--(){
    //���curr��0��������ݼ��ᵼ��һ����Ч�±�
    --curr;
    check(curr, "decrement past begin of StrBlobPtr");
    return *this;
}

//���ð汾
StrBlobPtr StrBlobPtr::operator++(int){
    auto ret = *this;                   //��¼��ǰֵ
    ++*this;                            //��ǰ����++���Ҳ���Ҫ����Ƿ�Խ�磬��Ϊʹ�õ������ص�ǰ��++
    return ret;
}

StrBlobPtr StrBlobPtr::operator--(int){
    //���������Ч�ԣ�����ǰ�õ���ʱ����Ҫ���
    auto ret = *this;
    --*this;
    return ret;
}

StrBlobPtr& StrBlobPtr::operator+=(size_t n) {
    curr += n;
    check(curr, "increment past end of StrBlobPtr");
    return *this;
}

StrBlobPtr& StrBlobPtr::operator-=(size_t n) {
    curr -= n;
    check(curr, "decrement past begin of StrBlobPtr");
    return *this;
}

//������飺+= �� -= �Ѿ�����
StrBlobPtr StrBlobPtr::operator+(size_t n) const {
    StrBlobPtr ret = *this;
    ret += n;
    return ret;
}

StrBlobPtr StrBlobPtr::operator-(size_t n) const {
    StrBlobPtr ret = *this;
    ret -= n;
    return ret;
}

string& StrBlobPtr::operator*() const{
    auto data = check(curr, "dereference out of range");
    return (*data)[curr];
}

string* StrBlobPtr::operator->() const{
    return & this->operator*();                     //this��ʽд��������
}




//ConstStrBlobPtr�Ķ��壬������ֻ�н����ò��ֲ�ͬ�����ز��ɸı�ĳ�����

shared_ptr<vector<string>> ConstStrBlobPtr::check(size_t i, const string &msg) const {
    auto ret = wptr.lock(); // vector ��������
    if (!ret)
        throw runtime_error("unbound ConstStrBlobPtr");
    if (i >= ret->size())
        throw out_of_range(msg);
    return ret;             // ���򣬷���ָ�� vector �� shared_ptr
}

string& ConstStrBlobPtr::deref() const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];      // (*P) �Ƕ�����ָ��� vector
}

// ǰ׺���������ص�����Ķ��������
ConstStrBlobPtr& ConstStrBlobPtr::incr() {
    // ��� curr �Ѿ�ָ��������β��λ�ã��Ͳ��ܵ�����
    check(curr, "increment past end of ConstStrBlobPtr");
    ++curr;                 // �ƽ���ǰλ��
    return *this;
}

// ǰ׺�ݼ������صݼ���Ķ��������
ConstStrBlobPtr& ConstStrBlobPtr::decr() {
    // ��� curr �Ѿ�Ϊ 0���ݼ��������һ���Ƿ��±�
    --curr;                 // �ݼ���ǰλ��
    check(-1, "decrement past begin of ConstStrBlobPtr");
    return *this;
}

// StrBlob �� begin �� end ��Ա�Ķ���
ConstStrBlobPtr StrBlob::cbegin() const {
    return ConstStrBlobPtr(*this);
}
ConstStrBlobPtr StrBlob::cend() const {
    auto ret = ConstStrBlobPtr(*this, data->size());
    return ret;
}

// ConstStrBlobPtr �ıȽϲ���
bool operator==(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs) {
    auto l = lhs.wptr.lock(), r = rhs.wptr.lock();
    // ���ײ�� vector ��ͬһ��
    if (l == r)
        // ������ָ�붼�ǿգ�����ָ����ͬԪ��ʱ���������
        return (!r || lhs.curr == rhs.curr);
    else
        return false;       // ��ָ��ͬ vector���򲻿������
}

bool operator!=(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs) {
    return !(lhs == rhs);
}

bool operator<(const ConstStrBlobPtr &s1, const ConstStrBlobPtr &s2) {
    auto l = s1.wptr.lock(), r = s2.wptr.lock();
    if (l == r) {
        if (!r)
            return false;               // ����ָ�붼Ϊ�գ���Ϊ�����
        return (s1.curr < s2.curr);     // ָ����ͬ vector���Ƚ�ָ��λ��
    } else {
        return false;                   // ָ��ͬ vector ʱ�����ܱȽ�
    }
}

bool operator>(const ConstStrBlobPtr &s1, const ConstStrBlobPtr &s2) {
    return s2 < s1;
}

bool operator<=(const ConstStrBlobPtr &s1, const ConstStrBlobPtr &s2) {
    return !(s2 < s1);
}

bool operator>=(const ConstStrBlobPtr &s1, const ConstStrBlobPtr &s2) {
    return !(s1 < s2);
}

const string& ConstStrBlobPtr::operator[](size_t n) const {
    auto p = check(n, "dereference out of range");
    return (*p)[n];
}

// ǰ�ð汾�����ص���/�ݼ����������
ConstStrBlobPtr& ConstStrBlobPtr::operator++() {
    // ��� curr �Ѿ�ָ����������β��λ�ã����޷�������
    check(curr, "increment past end of ConstStrBlobPtr");
    ++curr;         // �� curr �ڵ�ǰ״̬����ǰ�ƶ�һ��Ԫ��
    return *this;
}
ConstStrBlobPtr& ConstStrBlobPtr::operator--() {
    // ��� curr �� 0��������ݼ���������һ����Ч�±�
    --curr;         // �� curr �ڵ�ǰ״̬�º�ǰ�ƶ�һ��Ԫ��
    check(curr, "decrement past begin of ConstStrBlobPtr");
    return *this;
}

// ���ð汾������/�ݼ������ֵ���Ƿ���ԭֵ
ConstStrBlobPtr& ConstStrBlobPtr::operator++(int) {
    // �˴���������Ч�ԣ�����ǰ�õ�������ʱ����Ҫ���
    ConstStrBlobPtr ret = *this;         // ��¼��ǰ��ֵ
    ++*this;        // ��ǰ�ƶ�һ��Ԫ�أ�ǰ��++��Ҫ����������Ч��
    return ret;     // ����֮ǰ��¼��״̬
}
ConstStrBlobPtr& ConstStrBlobPtr::operator--(int) {
    // �˴���������Ч�ԣ�����ǰ�õݼ�����ʱ����Ҫ���
    ConstStrBlobPtr ret = *this;         // ��¼��ǰ��ֵ
    ++*this;        // ����ƶ�һ��Ԫ�أ�ǰ��--��Ҫ���ݼ�����Ч��
    return ret;     // ����֮ǰ��¼��״̬
}

ConstStrBlobPtr& ConstStrBlobPtr::operator+=(size_t n) {
    curr += n;
    check(curr, "increment past end of ConstStrBlobPtr");
    return *this;
}

ConstStrBlobPtr& ConstStrBlobPtr::operator-=(size_t n) {
    curr -= n;
    check(curr, "decrement past begin of ConstStrBlobPtr");
    return *this;
}

ConstStrBlobPtr ConstStrBlobPtr::operator+(size_t n) const {
    ConstStrBlobPtr ret = *this;
    ret += n;
    return ret;
}

ConstStrBlobPtr ConstStrBlobPtr::operator-(size_t n) const {
    ConstStrBlobPtr ret = *this;
    ret -= n;
    return ret;
}

const string& ConstStrBlobPtr::operator*() const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];      // (*p) �Ƕ�����ָ�� vector
}

const string* ConstStrBlobPtr::operator->() const {
    // ��ʵ�ʹ���ί�и������������
    return & this->operator*();
}




#endif                                  //TEST_STRBLOB_H