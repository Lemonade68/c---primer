#include<iostream>
#include<memory>
#include<string>
#include<vector>

template<typename T> class Blob{
public:
    typedef T value_type;
    //ע�����typedef���typename���÷�����ʾ�ñ�����֪��vector<T>��size_type��һ������
    //�����vector<T>����һ��δ֪������
    typedef typename std::vector<T>::size_type size_type;
    // typedef std::vector<T>::size_type size_type;

    //���캯��
    Blob();
    Blob(std::initializer_list<T> il);
    //�������
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back(const T &t) { data->push_back(t); }
    void push_back(T &&t) { data->push_back(std::move(t)); }    //�ƶ��汾��ע��ʹ��move��������ֵ����
    void pop_back();
    //Ԫ�ط���
    T &back();
    T &operator[](size_type i);

private:
    std::shared_ptr<std::vector<T>> data;
    //��data[i]��Ч�����׳�msg
    void check(size_type i, const std::string &msg) const;
};



//ʹ��������
// Blob<int> ia;