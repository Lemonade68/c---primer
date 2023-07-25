#ifndef STRVEC
#define STRVEC

#include<iostream>

#include<string>
using std::string;

#include<memory>
using std::allocator;
using std::uninitialized_copy;

#include<utility>
using std::pair;

using std::make_move_iterator;

#include<initializer_list>
using std::initializer_list;

#include<algorithm>
using std::equal;
using std::for_each;

class StrVec{
public:
    friend bool operator==(const StrVec &, const StrVec &);
    friend bool operator!=(const StrVec &, const StrVec &);
    friend bool operator<(const StrVec &s1, const StrVec &s2);
    friend bool operator<=(const StrVec &s1, const StrVec &s2);
    friend bool operator>(const StrVec &s1, const StrVec &s2);
    friend bool operator>=(const StrVec &s1, const StrVec &s2);

public:
    StrVec():elements(nullptr), first_free(nullptr), cap(nullptr){ }
    StrVec(const StrVec &);
    StrVec(StrVec &&) noexcept;     //�ƶ����캯������Ҫconst����noexcept�������Ͷ���ʱ����Ҫ��
    ~StrVec();
    
public:
    StrVec &operator=(const StrVec &);
    StrVec &operator=(StrVec &&);
    //��ϰ14.23,     ע��initializer_listֻ����һ��ָ�룬���ƵĴ��ۺ�С������Ҫconst &
    StrVec &operator=(initializer_list<string>);
    //�±��������ע���������汾�����const����ͷ�const����
    string &operator[](size_t n) { return elements[n]; }
    const string &operator[](size_t n) const { return elements[n]; }

    void push_back(const string &);     //����Ԫ��
    void push_back(string &&);          //�ƶ�Ԫ��
    const size_t size() const{ return first_free - elements; }
    const size_t capacity() const{ return cap - elements; }
    string *begin() { return elements; }
    string *end() { return cap; }
    const string *begin() const { return elements; }
    const string *end() const { return cap; }

    //��ϰ13.39
    void reserve(size_t n){ if(n>capacity()) reallocate(n); }       //Ԥ��һ���ֿռ�
    void resize(size_t);
    void resize(size_t, const string &);

    //��ϰ13.40
    StrVec(initializer_list<string>);

private:
    static allocator<string> alloc;     //����Ԫ�أ�����һ������
    
    // ���Ԫ�صĺ���ʹ��
    void chk_n_alloc() { if(size() == capacity())  reallocate(); }      
    
    //���ߺ��������������캯������ֵ���������������ʹ��
    pair<string *, string *> alloc_n_copy(const string *, const string *);
    void free();                //����Ԫ�أ��ͷ��ڴ�
    void reallocate();          //��ø����ڴ棬����������Ԫ��

    string *elements;           //ָ��������Ԫ�ص�ָ��
    string *first_free;         //ָ�������һ������Ԫ�ص�ָ��
    string *cap;                //ָ������β��λ�õ�ָ��
    
    void reallocate(size_t);    //������ʽ
};

bool operator==(const StrVec &, const StrVec &);
bool operator!=(const StrVec &, const StrVec &);
bool operator<(const StrVec &s1, const StrVec &s2);
bool operator<=(const StrVec &s1, const StrVec &s2);
bool operator>(const StrVec &s1, const StrVec &s2);
bool operator>=(const StrVec &s1, const StrVec &s2);





//ʣ�²���Ӧ�÷���cpp�ļ���

//��̬��Ա����Ҫ��cpp�ļ��ж���
allocator<string> StrVec::alloc;

void StrVec::push_back(const string &s){
    chk_n_alloc();              //ȷ���пռ�������Ԫ��
    alloc.construct(first_free++, s);       
}

void StrVec::push_back(string &&s){
    chk_n_alloc();
    alloc.construct(first_free++, std::move(s));    //ע����߲���s����ΪsҲ��һ����ֵ
}

pair<string*, string*> StrVec::alloc_n_copy(const string *b, const string *e){      //n - and
    //����ռ䱣�������Χ�е�Ԫ��
    auto data = alloc.allocate(e - b);
    //��ʼ��������һ��pair����data���׵�ַ����uninitialized_copy�ķ���ֵ��β��ָ�룩����
    return {data, uninitialized_copy(b, e, data)};
}

void StrVec::free(){
    //���ܴ��ݸ�deallocateһ����ָ�룬���elementsΪ�գ���ʲôҲ����
    if(elements){
        for (auto p = first_free; p != elements; )      //����ʹ��range for��ֱ���޸�Ԫ��
            alloc.destroy(--p);
        //ʹ��for_each��lambda�����汾
        // for_each(elements, first_free, [this](string &s) {alloc.destroy(&s);});
        alloc.deallocate(elements, capacity());
    }
}

StrVec::StrVec(const StrVec &s){
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec::StrVec(StrVec &&s) noexcept : elements(s.elements),first_free(s.first_free),cap(s.cap){
    s.elements = s.first_free = s.cap = nullptr;
}

StrVec::~StrVec(){
    free();
}

StrVec& StrVec::operator=(const StrVec &rhs){
    auto newdata = alloc_n_copy(rhs.begin(), rhs.end());        //��һ�����ȣ�����Ը�ֵ����
    free();
    elements = newdata.first;
    first_free = cap = newdata.second;
    return *this;
}

StrVec& StrVec::operator=(StrVec &&rhs){
    if(this != &rhs){                   //ֱ�Ӽ���Ը�ֵ
        free();
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}

void StrVec::reallocate(){
    auto newcapacity = size() ? 2 * size() : 1;     //���������Ĵ�С����Ϊ�գ�������СΪ1���ڴ�
    auto newdata = alloc.allocate(newcapacity);     //�������ڴ�

    //�����ݴӾ��ڴ��ƶ������ڴ�
    auto dest = newdata;                //ָ���������е���һ������λ��
    auto elem = elements;               //ָ��������е���һ��Ԫ��
    for (size_t i = 0; i != size(); ++i){
        alloc.construct(dest++, std::move(*elem++));        //std::move����һ����ֵ���ã�construct������ֵ���ô���ƶ���Ч��
    }
    free();                             //�ƶ���Ԫ�ؾ��Ƿž��ڴ�ռ�
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}

void StrVec::reallocate(size_t newcapacity){
    auto newdata = alloc.allocate(newcapacity);

    auto dest = newdata;                //ָ��Ŀ�ĵأ���construct��һ������ʹ��
    auto elem = elements;               

    for (size_t i = 0; i < size(); ++i)
        alloc.construct(dest++, std::move(*elem++));
    free();

    elements = newdata;
    first_free = elem;
    cap = elements + newcapacity;
}


//ʹ���ƶ��������汾��reallocate
void StrVec::reallocate(){
    auto newcapacity = size() ? 2 * size() : 1;
    auto first = alloc.allocate(newcapacity);

    auto last = uninitialized_copy(make_move_iterator(begin()), make_move_iterator(end()), first);
    free();

    elements = first;
    first_free = last;
    cap = elements + newcapacity;
}


void StrVec::resize(size_t count){
    resize(count, string());            //�����Լ������ذ汾
}

void StrVec::resize(size_t count, const string &s){
    if(count > size()){
        if(count > capacity())
            reserve(count * 2);         //Ԥ������Ŀռ�
        for (auto i = size(); i != count; ++i)
            alloc.construct(first_free++, s);
    }
    else if(count < size()){
        while(first_free != elements + count)
            alloc.destroy(--first_free);
    }
}

StrVec::StrVec(initializer_list<string> il){
    auto newdata = alloc_n_copy(il.begin(), il.end());
    elements = newdata.first;
    cap = first_free = newdata.second;
}


//��ϰ14.3.1
// bool operator==(const StrVec &lhs, const StrVec &rhs){
//     //�����С����ȣ��϶����ȣ�    ��ע��Ƚ�vector��Ԥ����Ĵ�С�޹أ�ֻ�뵱ǰ�����к��е�Ԫ�ظ������
//     if(lhs.size() != rhs.size())
//         return false;

//     //�ж�ÿ��Ԫ���Ƿ����
//     for (auto it1 = lhs.begin(), it2 = rhs.begin(); it1 != lhs.end(), it2 != rhs.end(); ++it1, ++it2)
//         if(*it1 != *it2)
//             return false;

//     return true;
// }

//ѧϰ����д��
bool operator==(const StrVec &lhs, const StrVec &rhs){
    return (lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin()));
}

bool operator!=(const StrVec &lhs, const StrVec &rhs){
    return !(lhs == rhs);
}

bool operator<(const StrVec &s1, const StrVec &s2) {
    auto p1 = s1.begin(), p2 = s2.begin();
    for ( ; p1 != s1.end() && p2 != s2.end(); ++p1, ++p2) {
        if (*p1 < *p2)          // ֮ǰ�� string ����ȣ���ǰ string ��С
            return true;
        else if (*p1 > *p2)     // ֮ǰ�� string ����ȣ���ǰ string ����
            return false;
    }
    // s1 �е����� string ���� s2 �е� string ��ȣ��� s1 ����
    if (p1 == s1.end() && p2 != s2.end())
        return true;
    return false;
}

bool operator>(const StrVec &s1, const StrVec &s2) {
    return s2 < s1;
}

bool operator<=(const StrVec &s1, const StrVec &s2) {
    return !(s2 < s1);
}

bool operator>=(const StrVec &s1, const StrVec &s2) {
    return !(s1 < s2);
}


// ��ϰ14.23
StrVec& StrVec::operator=(initializer_list<string> il){
    auto data = alloc_n_copy(il.begin(), il.end());
    free();                                 //����ԭ����
    elements = data.first;
    first_free = cap = data.second;         //ע��capҲ��Ҫ��ֵ
    return *this;
}

#endif