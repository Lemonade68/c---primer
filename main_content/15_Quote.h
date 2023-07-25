#ifndef TEST_QUOTE_H
#define TEST_QUOTE_H

#include<iostream>
#include<string>
#include<memory>
#include<set>

class Quote{
public:
    //�����������Ҫ�ƶ������Ļ���Ӧ�ڻ�������ʽ�������ϳ��ƶ��������Լ���������

    Quote() = default;
    Quote(const Quote &) = default;
    Quote(Quote &&) = default;
    Quote &operator=(const Quote &) = default;
    Quote &operator=(Quote &&) = default;
    virtual ~Quote() = default;                 //�������������ж�̬��(��ʽʹ��)
    
    Quote(const std::string &book, double sales_price):
                    bookNo(book),price(sales_price) { }

    std::string isbn() const { return bookNo; }
    
    //�����ฺ���д��ʹ�ò�ͬ���ۿۼ����㷨
    virtual double net_price(std::size_t n) const { return n * price; }

    //��ϰ15.11
    virtual void debug();

    //Basket����add_item������ʹ�õ��麯��,���ص�ǰ�����һ�ݶ�̬���俽��
    virtual Quote *clone() const & { return new Quote(*this); }
    virtual Quote *clone() && { return new Quote(std::move(*this)); }       //ע��*this�Ǹ���ֵ

private:
    std::string bookNo;
protected:
    double price = 0.0;
};

inline void Quote::debug(){
    std::cout << "Parameters: " << bookNo << " " << price << std::endl;
}



class Disc_quote : public Quote{
public:
    Disc_quote() = default;
    Disc_quote(const std::string &book, double price, std::size_t qty, double disc):
                Quote(book,price),quantity(qty),discount(disc) { }
    double net_price(std::size_t) const = 0;        //ûдoverrideҲ���ԣ���֤���������β�һ�����ɣ�
protected:
    std::size_t quantity = 0;                       //�ۿ����õĹ�����
    double discount = 0.0;                          //�ۿ�
};




class Bulk_quote : public Disc_quote{
public:
    // Bulk_quote() = default;

    //��ϰ15.27   ʹ��using����������������Ĺ��캯��
    using Disc_quote::Disc_quote;

    Bulk_quote(const std::string &, double, std::size_t, double);
    
    //��д���麯��
    double net_price(std::size_t n) const override;

    //��ϰ15.11
    void debug() override;

    //Basket������Ҫ�ĺ�������д����Ļ�����麯��
    Bulk_quote *clone() const & override { return new Bulk_quote(*this); }
    Bulk_quote *clone() && override { return new Bulk_quote(std::move(*this)); }
};


//���캯�������û���Ĺ��캯����������ಿ��
Bulk_quote::Bulk_quote(const std::string &book, double p, std::size_t qty, double disc):
            Disc_quote(book, price, qty, disc) { }

double Bulk_quote::net_price(std::size_t n) const{
    if (n >= quantity)
        return n * (1 - discount) * price;
    else
        return n * price;
}

void Bulk_quote::debug(){
    Quote::debug();
    std::cout << quantity << " " << discount << std::endl;
}



double print_total(std::ostream &os, const Quote &item, std::size_t n) {
    // ���ݴ��� item �βεĶ������͵��� Quote::net_price
    // ���� Bulk_quote::net_price
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn()
       << " # sold: " << n << " total due: " << ret << std::endl;
    return ret;
}


//15.8 Basket��
class Basket{
public:
    //ʹ�úϳɵ�Ĭ�Ϲ��캯���Ϳ������Ƴ�Ա
    
    //���������м����鼮
    void add_item(const Quote &);           //��ֵ�����汾
    void add_item(Quote &&);                //��ֵ���ð汾
    //��ӡÿ������ܼۺ͹���������������ܼ�
    double total_receipt(std::ostream &) const;

private:
    //�ú������ڱȽ�shared_ptr��multiset��Ա��ʹ����
    static bool compare(const std::shared_ptr<Quote> &lhs, const std::shared_ptr<Quote> &rhs){
        return lhs->isbn() < rhs->isbn();
    }
    //multiset���������ۣ�����compare��Ա����
    std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items{compare};
};


double Basket::total_receipt(std::ostream &os) const{
    double sum = 0.0;                   //����ʵʱ��������ܼ۸�
    //iterָ��isbn��ͬ��һ��Ԫ���еĵ�һ��
    //upper_bound����һ�����������õ�����ָ������Ԫ�ص�β��λ��
    for (auto iter = items.cbegin(); iter != items.cend(); iter = items.upper_bound(*iter)){
        sum += print_total(os, **iter, items.count(*iter));
    }
    os << "Total Sale: " << sum << std::endl;            //��ӡ�����ܼ۸�
    return sum;
}


//����Quote��Bulk_quote����ӵĺ���clone�ǵÿ���
void Basket::add_item(const Quote &sale){
    items.insert(std::shared_ptr<Quote>(sale.clone()));     //sale.clone����new��Quote*��ת��Ϊshared_ptr
}

void Basket::add_item(Quote &&sale){
    items.insert(std::shared_ptr<Quote>(std::move(sale.clone())));
}



#endif