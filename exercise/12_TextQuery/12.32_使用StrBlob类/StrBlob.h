#ifndef TEST_STRBLOB_H
#define TEST_STRBLOB_H

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
class StrBlob {
    friend class StrBlobPtr;
public:
    typedef vector<string>::size_type size_type;
    StrBlob();
    StrBlob(initializer_list<string> il);
    // new add code
    StrBlob(vector<string> *p);
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
    StrBlobPtr begin() const;     // ���� StrBlobPtr ����ܶ�������������
    StrBlobPtr end() const;

private:
    shared_ptr<vector<string>> data;
    // ��� data[i] ���Ϸ����׳�һ���쳣
    void check(size_type i, const string &msg) const;
};

inline StrBlob::StrBlob() : data(make_shared<vector<string>>()) { }
inline StrBlob::StrBlob(initializer_list <string> il) :
        data(make_shared<vector<string>>(il)) { }
// new add code
inline StrBlob::StrBlob(vector<string> *p) : data(p) { }

inline void StrBlob::check(vector<string>::size_type i, const string &msg) const {
    if (i >= data->size())
        throw out_of_range(msg);
}

inline string& StrBlob::front() {
    // ��� vector Ϊ�գ�check ���׳�һ���쳣
    check(0, "front on empty StrBlob");
    return data->front();
}

// const �汾 front
inline const string& StrBlob::front() const {
    check(0, "front on empty StrBlob");
    return data->front();
}

inline string& StrBlob::back() {
    check(0, "back on empty StrBlob");
    return data->back();
}

// const �汾 back
inline const string& StrBlob::back() const {
    check(0, "back on empty StrBlob");
    return data->back();
}

inline void StrBlob::pop_back() {
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}


class StrBlobPtr {
    friend bool eq(const StrBlobPtr &, const StrBlobPtr &);

public:
    StrBlobPtr() : curr(0) {}
    StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
    StrBlobPtr(const StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}

    string& deref() const;
    // new add code
    string& deref(int off) const;
    StrBlobPtr& incr();     // ǰ׺����
    StrBlobPtr& decr();     // ��׺�ݼ�
private:
    // �����ɹ���check ����һ��ָ�� vector �� shared_ptr
    shared_ptr<vector<string>> check(size_t, const string&) const;
    // ����һ�� weak_ptr����ζ�ŵײ� vector ���ܻᱻ����
    weak_ptr<vector<string>> wptr;
    size_t curr;            // �������еĵ�ǰλ��
};

inline shared_ptr<vector<string>> StrBlobPtr::check(size_t i, const string &msg) const {
    auto ret = wptr.lock(); // vector ��������
    if (!ret)
        throw runtime_error("unbound StrBlobPtr");
    if (i >= ret->size())
        throw out_of_range(msg);
    return ret;             // ���򣬷���ָ�� vector �� shared_ptr
}

inline string& StrBlobPtr::deref() const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];      // (*P) �Ƕ�����ָ��� vector
}

// new add code
inline string& StrBlobPtr::deref(int off) const {
    auto p = check(curr + off, "dereference past end");
    return (*p)[curr + off];// (*P) �Ƕ�����ָ��� vector
}

// ǰ׺���������ص�����Ķ��������
inline StrBlobPtr& StrBlobPtr::incr() {
    // ��� curr �Ѿ�ָ��������β��λ�ã��Ͳ��ܵ�����
    check(curr, "increment past end of StrBlobPtr");
    ++curr;                 // �ƽ���ǰλ��
    return *this;
}

// ǰ׺�ݼ������صݼ���Ķ��������           ���decre������  ��main_content�����
inline StrBlobPtr& StrBlobPtr::decr() {
    // ��� curr �Ѿ�Ϊ 0���ݼ��������һ���Ƿ��±�
    --curr;                 // �ݼ���ǰλ��
    check(-1, "decrement past begin of StrBlobPtr");
    return *this;
}

// StrBlob �� begin �� end ��Ա�Ķ���
inline StrBlobPtr StrBlob::begin() const {
    return StrBlobPtr(*this);
}
inline StrBlobPtr StrBlob::end() const {
    auto ret = StrBlobPtr(*this, data->size());
    return ret;
}

// StrBlobPtr �ıȽϲ���
inline bool eq(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
    auto l = lhs.wptr.lock(), r = rhs.wptr.lock();
    // ���ײ�� vector ��ͬһ��
    if (l == r)
        // ������ָ�붼�ǿգ�����ָ����ͬԪ��ʱ���������
        return (!r || lhs.curr == rhs.curr);
    else
        return false;       // ��ָ��ͬ vector���򲻿������
}

inline bool neq(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
    return !eq(lhs, rhs);
}

#endif //TEST_STRBLOB_H
