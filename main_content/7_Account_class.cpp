#include<string>
#include<iostream>


class Account{
public:
    void calculate(){
        amount += amount * interestRate;
    }
    static double rate(){               //��Ա������ֱ�ӷ��ʾ�̬��Ա
        return interestRate;
    }
    static void rate(double);

private:
    std::string owner;
    double amount;
    static double interestRate;
    static double initRate();
};


//���ⶨ��static��Ա����
void Account::rate(double newRate){
    interestRate = newRate;
}

//���岢��ʼ��һ����̬��Ա
double Account::interestRate = initRate();          //���������в��ֶ����������������
