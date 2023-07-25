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
    StrVec():elements(nullptr), first_free(nullptr), cap(nullptr){ }
    StrVec(const StrVec &);
    StrVec(StrVec &&) noexcept;     //�ƶ����캯������Ҫconst����noexcept�������Ͷ���ʱ����Ҫ��
    ~StrVec();
    
public:
    StrVec &operator=(const StrVec &);
    StrVec &operator=(StrVec &&);

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


#endif