#include<iostream>
#include<string>
#include<memory>
#include<cstring>
#define n 100

using namespace std;


void func_23(){
    const char *s1 = "Hello ";
    const char *s2 = "World!";
    char *c = new char[strlen(s1) + strlen(s2) + 1];    //+1��Ԥ����\0��������
    strcpy(c, s1);
    strcat(c, s2);
    cout << c << endl;

    string st1{"Hello "};
    string st2{"World!"};
    strcpy(c, (st1 + st2).c_str());         //s1+s2ת����c����ַ���
    cout << c << endl;

    delete[] c;
}

void func_24(){
    size_t size;
    cout << "plz input the size:";
    cin >> size;
    cin.ignore();                           //��������size���һ���ַ����ո��س�������cin.get()Ҳ����
    // cin.get();
    char *r = new char[size + 1]();         //ֵ��ʼ��
    cin.get(r, size + 1);                   //cin.get�������char����
    cout << "The input string is:\n" << r << endl;

    delete[] r;
}

void func_26(){
    // int n = 100;
    allocator<string> alloc;
    auto const p = alloc.allocate(n);       //ָ���׵�ַ
    string s;
    string *q = p;                          //���� auto q = p;                    
    while(cin>>s && q != p + n){
        alloc.construct(q++, s);            //ע���Ǻ��õ���
    }
    const size_t size = q - p;
    for (size_t i = 0; i < size; ++i)
        cout << p[i] << endl;
        
    while(q!=p)
        alloc.destroy(--q);                 //ע���ȵݼ�

    alloc.deallocate(p, n);
}


int main(){
    // func_23();
    // func_24();
    func_26();
    return 0;
}