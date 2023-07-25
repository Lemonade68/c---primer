#ifndef TEST_STRBLOB_H
#define TEST_STRBLOB_H

//.h�ļ�������

#include <vector>
#include <string>
#include <initializer_list>
#include <memory>
#include <stdexcept>

using std::string;
using std::vector;
using std::initializer_list;
using std::shared_ptr;
using std::weak_ptr;
using std::make_shared;
using std::out_of_range;
using std::runtime_error;

// ���� StrBlob �е���Ԫ������˵����ǰ�������Ǳ�Ҫ��
class StrBlobPtr;
class ConstStrBlobPtr;

//===========================================
//
//    StrBlob - custom vector<string>
//
//===========================================
class StrBlob {
    friend class StrBlobPtr;
    friend class ConstStrBlobPtr;
    // ��ϰ 14.16
    friend bool operator==(const StrBlob &lhs, const StrBlob &rhs);
    friend bool operator!=(const StrBlob &lhs, const StrBlob &rhs);
    // ��ϰ 14.18
    friend bool operator<(const StrBlob &s1, const StrBlob &s2);
    friend bool operator<=(const StrBlob &s1, const StrBlob &s2);
    friend bool operator>(const StrBlob &s1, const StrBlob &s2);
    friend bool operator>=(const StrBlob &s1, const StrBlob &s2);

public:
    typedef vector<string>::size_type size_type;
    StrBlob();
    StrBlob(initializer_list<string> il);
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    // ��Ӻ�ɾ��Ԫ��
    void push_back(const string &t) { data->push_back(t); }
    void pop_back();
    // Ԫ�ط���
    string& front();
    const string& front() const;
    string& back();
    const string& back() const;

    // �ṩ�� StrBlobPtr �Ľӿ�
    // ����ָ����Ԫ�غ�β��Ԫ�ص� StrBlobPtr
    StrBlobPtr begin();     // ���� StrBlobPtr ����ܶ�������������
    StrBlobPtr end();
    // �ṩ�� ConstStrBlobPtr �Ľӿ�
    // ����ָ����Ԫ�غ�β��Ԫ�ص� ConstStrBlobPtr
    ConstStrBlobPtr cbegin() const;     // ���� ConstStrBlobPtr ����ܶ�������������
    ConstStrBlobPtr cend() const;
    // ��ϰ 14.26
    string &operator[](size_t);
    const string &operator[](size_t) const;

private:
    shared_ptr<vector<string>> data;
    // ��� data[i] ���Ϸ����׳�һ���쳣
    void check(size_type i, const string &msg) const;
};
bool operator==(const StrBlob &lhs, const StrBlob &rhs);
bool operator!=(const StrBlob &lhs, const StrBlob &rhs);
bool operator<(const StrBlob &s1, const StrBlob &s2);
bool operator<=(const StrBlob &s1, const StrBlob &s2);
bool operator>(const StrBlob &s1, const StrBlob &s2);
bool operator>=(const StrBlob &s1, const StrBlob &s2);


//===================================================
//
//    StrBlobPtr - custom iterator of StrBlob
//
//===================================================
class StrBlobPtr {
    // ��ϰ 14.16
    friend bool operator==(const StrBlobPtr &lhs, const StrBlobPtr &rhs);
    friend bool operator!=(const StrBlobPtr &lhs, const StrBlobPtr &rhs);
    // ��ϰ 14.18
    friend bool operator<(const StrBlobPtr &s1, const StrBlobPtr &s2);
    friend bool operator<=(const StrBlobPtr &s1, const StrBlobPtr &s2);
    friend bool operator>(const StrBlobPtr &s1, const StrBlobPtr &s2);
    friend bool operator>=(const StrBlobPtr &s1, const StrBlobPtr &s2);

public:
    StrBlobPtr() : curr(0) {}
    StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}

    string& deref() const;
    StrBlobPtr& incr();     // ǰ׺����
    StrBlobPtr& decr();     // ��׺�ݼ�
    // ��ϰ 14.26
    string &operator[](size_t);
    const string &operator[](size_t) const;
    // ��ϰ 14.27
    StrBlobPtr &operator++();       // ǰ�������
    StrBlobPtr &operator--();
    StrBlobPtr &operator++(int);    // ���������
    StrBlobPtr &operator--(int);
    // ��ϰ 14.28
    StrBlobPtr &operator+=(size_t);
    StrBlobPtr &operator-=(size_t);
    StrBlobPtr operator+(size_t) const;
    StrBlobPtr operator-(size_t) const;
    // ��ϰ 14.30
    string &operator*() const;
    string *operator->() const;

private:
    // �����ɹ���check ����һ��ָ�� vector �� shared_ptr
    shared_ptr<vector<string>> check(size_t, const string&) const;
    // ����һ�� weak_ptr����ζ�ŵײ� vector ���ܻᱻ����
    weak_ptr<vector<string>> wptr;
    size_t curr;            // �������еĵ�ǰλ��
};
bool operator==(const StrBlobPtr &lhs, const StrBlobPtr &rhs);
bool operator!=(const StrBlobPtr &lhs, const StrBlobPtr &rhs);
bool operator<(const StrBlobPtr &s1, const StrBlobPtr &s2);
bool operator<=(const StrBlobPtr &s1, const StrBlobPtr &s2);
bool operator>(const StrBlobPtr &s1, const StrBlobPtr &s2);
bool operator>=(const StrBlobPtr &s1, const StrBlobPtr &s2);


//=========================================================
//
//    ConstStrBlobPtr - custom const_iterator of StrBlob
//
//=========================================================
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










//.cpp�ļ�
// #include "StrBlob.h"

/*
 * StrBlob
 */
StrBlob::StrBlob() : data(make_shared<vector<string>>()) { }
StrBlob::StrBlob(initializer_list <string> il) :
        data(make_shared<vector<string>>(il)) { }

void StrBlob::check(vector<string>::size_type i, const string &msg) const {
    if (i >= data->size())
        throw out_of_range(msg);
}

string& StrBlob::front() {
    // ��� vector Ϊ�գ�check ���׳�һ���쳣
    check(0, "front on empty StrBlob");
    return data->front();
}

// const �汾 front
const string& StrBlob::front() const {
    check(0, "front on empty StrBlob");
    return data->front();
}

string& StrBlob::back() {
    check(0, "back on empty StrBlob");
    return data->back();
}

// const �汾 back
const string& StrBlob::back() const {
    check(0, "back on empty StrBlob");
    return data->back();
}

void StrBlob::pop_back() {
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

bool operator==(const StrBlob &lhs, const StrBlob&rhs) {
    return lhs.data == rhs.data;            // ��ָ��� vector ���
}

bool operator!=(const StrBlob &lhs, const StrBlob&rhs) {
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

string& StrBlob::operator[](size_t n) {
    check(n, "out of range");
    return data->at(n);
}

const string& StrBlob::operator[](size_t n) const {
    check(n, "out of range");
    return data->at(n);
}


/*
 * StrBlobPtr
 */
shared_ptr<vector<string>> StrBlobPtr::check(size_t i, const string &msg) const {
    auto ret = wptr.lock(); // vector ��������
    if (!ret)
        throw runtime_error("unbound StrBlobPtr");
    if (i >= ret->size())
        throw out_of_range(msg);
    return ret;             // ���򣬷���ָ�� vector �� shared_ptr
}

string& StrBlobPtr::deref() const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];      // (*P) �Ƕ�����ָ��� vector
}

// ǰ׺���������ص�����Ķ��������
StrBlobPtr& StrBlobPtr::incr() {
    // ��� curr �Ѿ�ָ��������β��λ�ã��Ͳ��ܵ�����
    check(curr, "increment past end of StrBlobPtr");
    ++curr;                 // �ƽ���ǰλ��
    return *this;
}

// ǰ׺�ݼ������صݼ���Ķ��������
StrBlobPtr& StrBlobPtr::decr() {
    // ��� curr �Ѿ�Ϊ 0���ݼ��������һ���Ƿ��±�
    --curr;                 // �ݼ���ǰλ��
    check(curr, "decrement past begin of StrBlobPtr");
    return *this;
}

// StrBlob �� begin �� end ��Ա�Ķ���
StrBlobPtr StrBlob::begin() {
    return StrBlobPtr(*this);
}
StrBlobPtr StrBlob::end() {
    auto ret = StrBlobPtr(*this, data->size());
    return ret;
}

// StrBlobPtr �ıȽϲ���
bool operator==(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
    auto l = lhs.wptr.lock(), r = rhs.wptr.lock();
    // ���ײ�� vector ��ͬһ��
    if (l == r)
        // ������ָ�붼�ǿգ�����ָ����ͬԪ��ʱ���������
        return (!r || lhs.curr == rhs.curr);
    else
        return false;       // ��ָ��ͬ vector���򲻿������
}

bool operator!=(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
    return !(lhs == rhs);
}

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

bool operator>(const StrBlobPtr &s1, const StrBlobPtr &s2) {
    return s2 < s1;
}

bool operator<=(const StrBlobPtr &s1, const StrBlobPtr &s2) {
    return !(s2 < s1);
}

bool operator>=(const StrBlobPtr &s1, const StrBlobPtr &s2) {
    return !(s1 < s2);
}

string& StrBlobPtr::operator[](size_t n) {
    auto p = check(n, "dereference out of range");
    return (*p)[n];
}

const string& StrBlobPtr::operator[](size_t n) const {
    auto p = check(n, "dereference out of range");
    return (*p)[n];
}

// ǰ�ð汾�����ص���/�ݼ����������
StrBlobPtr& StrBlobPtr::operator++() {
    // ��� curr �Ѿ�ָ����������β��λ�ã����޷�������
    check(curr, "increment past end of StrBlobPtr");
    ++curr;         // �� curr �ڵ�ǰ״̬����ǰ�ƶ�һ��Ԫ��
    return *this;
}
StrBlobPtr& StrBlobPtr::operator--() {
    // ��� curr �� 0��������ݼ���������һ����Ч�±�
    --curr;         // �� curr �ڵ�ǰ״̬�º�ǰ�ƶ�һ��Ԫ��
    check(curr, "decrement past begin of StrBlobPtr");
    return *this;
}

// ���ð汾������/�ݼ������ֵ���Ƿ���ԭֵ
StrBlobPtr& StrBlobPtr::operator++(int) {
    // �˴���������Ч�ԣ�����ǰ�õ�������ʱ����Ҫ���
    StrBlobPtr ret = *this;         // ��¼��ǰ��ֵ
    ++*this;        // ��ǰ�ƶ�һ��Ԫ�أ�ǰ��++��Ҫ����������Ч��
    return ret;     // ����֮ǰ��¼��״̬
}
StrBlobPtr& StrBlobPtr::operator--(int) {
    // �˴���������Ч�ԣ�����ǰ�õݼ�����ʱ����Ҫ���
    StrBlobPtr ret = *this;         // ��¼��ǰ��ֵ
    ++*this;        // ����ƶ�һ��Ԫ�أ�ǰ��--��Ҫ���ݼ�����Ч��
    return ret;     // ����֮ǰ��¼��״̬
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

string& StrBlobPtr::operator*() const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];      // (*p) �Ƕ�����ָ�� vector
}

string* StrBlobPtr::operator->() const {
    // ��ʵ�ʹ���ί�и������������
    return & this->operator*();
}


/*
 * ConstStrBlobPtr
 */
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



#endif //TEST_STRBLOB_H
