#ifndef TEST_SALES_DATA_H
#define TEST_SALES_DATA_H


//.h����
#include <iostream>
#include <string>
using std::string;

// added overloaded input, output, addition, and compound-assignment operators
class Sales_data {
    //ע����߶���Ϊ�ǳ�Ա����
    friend std::istream &operator>>(std::istream&, Sales_data&);        // input������ı�״̬�����������
    friend std::ostream &operator<<(std::ostream&, const Sales_data&);  // output��������ı�״̬�������const����
    friend Sales_data operator+(const Sales_data&, const Sales_data&);  // addition

public:
    Sales_data(const std::string &s, unsigned n, double p)
        : bookNo(s), units_sold(n), revenue(n * p) { }
    Sales_data() : Sales_data("", 0, 0.0f) { }
    Sales_data(const std::string &s) : Sales_data(s, 0, 0.0f) { }
    Sales_data(std::istream&);

    Sales_data &operator+=(const Sales_data&);          // compound-assignment
    std::string isbn() const { return bookNo; }

    Sales_data &operator=(const string &);

private:
    double avg_price() const;

    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0;
};

// ������Ԫ��������Ҫ��ʵ�ڵ�����
std::istream &operator>>(std::istream&, Sales_data&);
std::ostream &operator<<(std::ostream&, const Sales_data&);
Sales_data operator+(const Sales_data&, const Sales_data&);

// ��Ա��������Ҫ��������������Ԫ��Ҫ
// Sales_data& Sales_data::operator=(const string &);

inline
double Sales_data::avg_price() const {
    return units_sold ? revenue / units_sold : 0;
}


//.cpp����

Sales_data::Sales_data(std::istream &is) : Sales_data() {
    is >> *this;
}

//��ֵ���㷵����ֵ
Sales_data& Sales_data::operator+=(const Sales_data &rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

std::istream &operator>>(std::istream &is, Sales_data &item) {
    double price = 0.0;
    is >> item.bookNo >> item.units_sold >> price;
    //һ������������ټ���
    if (is)
        item.revenue = price * item.units_sold;
    else
        item = Sales_data();
    return is;
}

std::ostream &operator<<(std::ostream &os, const Sales_data &item) {
    //ע�����û��endl�����ﶨ��ʱ����Ҫˢ�����buf��
    os << item.isbn() << " " << item.units_sold << " " << item.revenue
       << " " << item.avg_price();
    return os;
}


//�������㷵����ֵ�����Է��ؾֲ�������ֵ������ö���һ����ʱ��������Ϊ����������const
Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs) {
    Sales_data sum = lhs;
    sum += rhs;
    return sum;
}

Sales_data& Sales_data::operator=(const string &isbn){
    bookNo = isbn;
    return *this;
}

#endif //TEST_SALES_DATA_H
