#include<iostream>
#include<string>
#include<vector>



class Sales_data{
//��Ԫ��������ü��з�����ǰ�������棩
    friend Sales_data add(const Sales_data &, const Sales_data &);
    friend std::ostream &print(std::ostream &, const Sales_data &);
    friend std::istream &read(std::istream &, Sales_data &);

private:
// ���ݳ�Ա
    std::string bookNo;
    unsigned units_sold = 0;                        // unsigned����ʹ�� = unsigned int
    double revenue = 0.0;                           // ���룬���������ź�������
    double avg_price() const;                       // ���̺������ǽӿ�

public:
//���캯�������public��
    Sales_data() = default;
    Sales_data(const std::string &s) : 
            bookNo(s) { }
    // explicit Sales_data(const std::string &s) : bookNo(s) { }        //�ܾ�ʹ����ʽת��
    Sales_data(const std::string &s, unsigned n, double p) :
            bookNo(s), units_sold(n), revenue(p*n) { }
    Sales_data(std::istream &);

// ����Sales_data����Ĳ�������Ա�ӿں�����
    std::string isbn() const { return bookNo; }     // std::string isbn() const { return this->bookNo; }
    Sales_data &combine(const Sales_data &);        // �����������������ⲿ
};
// Sales_data�ķǳ�Ա�ӿں��� ����Щ������������Ա����������ֱ����
Sales_data add(const Sales_data &, const Sales_data &);
std::ostream &print(std::ostream &, const Sales_data &);
std::istream &read(std::istream &, Sales_data &);



//���ⲿ�����Ա����    ע��������    (���ⶨ��������ĺ���)
inline double Sales_data::avg_price() const{
    if(units_sold)
        return revenue / units_sold;
    else
        return 0;
}

//����һ������this����ĺ���
Sales_data& Sales_data::combine(const Sales_data &rhs){
    units_sold += rhs.units_sold;                   //rhs�ĳ�Ա�ӵ�this����ĳ�Ա��
    revenue += rhs.revenue;
    return *this;                                   //���ص��øú����Ķ���
}

//����read��print�������ǳ�Ա����������������
std::istream &read(std::istream &is, Sales_data &item){
    double price = 0.0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

std::ostream &print(std::ostream &os, const Sales_data &item){
    os << item.isbn() << " " << item.units_sold << " " 
       << item.revenue << " " << item.avg_price();
    return os;
}

//����add����
Sales_data add(const Sales_data &lhs, const Sales_data & rhs){
    Sales_data sum = lhs;
    sum.combine(rhs);                               //rhs���ݳ�Ա�ӵ�sum��
    return sum;
}

//���ⲿ���幹�캯��
Sales_data::Sales_data(std::istream &is){
    read(is, *this);                                //��thisָ��Ľ����þ��ǵ�ǰ�Ķ���
}


int main(){
    std::string s = "109";
    Sales_data item;
    item.combine(s);                                //���ʹ��explicit�汾�Ĺ��캯���������Ҳ�ᱨ��
    // item.combine("109");                            //Ҫִ��������ʽת�����ᱨ��
    return 0;
}