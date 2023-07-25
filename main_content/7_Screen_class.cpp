#include<iostream>
#include<string>
#include<vector>

class Screen{
    friend class Window_mgr;                                //���� + ������Ԫ

public:
    typedef std::string::size_type pos;                     //���Թ��û�ʹ��(Ҫ����������)
    // using pos = std::string::size_type;

    Screen() = default;
    Screen(pos ht, pos wd):
        height(ht), width(wd), contents(ht * wd, ' ') { }
    Screen(pos ht, pos wd, char c):
        height(ht), width(wd), contents(ht * wd, c) { }     //ע��string�����ʼ����ȫ��������һ���ַ����ظ�


    char get() const { return contents[cursor]; }           //����괦���ַ�  ��ʽ����
    inline char get(pos ht, pos wd) const;                  //��ʽ�����Լ���������
    Screen &move(pos r, pos c);                             //֮����Ϊ����

    void some_member() const;

    Screen &set(char);
    Screen &set(pos, pos, char);

    //���ݶ����Ƿ���const������display����
    Screen &display(std::ostream &os) { 
        do_display(os);
        return *this;
    }
    const Screen &display(std::ostream &os) const{
        do_display(os);
        return *this;
    }

    void setHeight(pos);

private:
    pos cursor = 0;                     //���
    pos height = 0, width = 0;          //��Ļ�ߺͿ�
    std::string contents;
    mutable size_t access_ctr;          //mutable ��ʾ�ɱ����ݳ�Ա
    void do_display(std::ostream &os) const { os << contents; }     //�ú��������壺�����պ�Ĳ���
};


char Screen::get(pos r, pos c) const {
    pos row = r * width;
    return contents[row + c];
}

inline Screen &Screen::move(pos r, pos c){                  
    pos row = r * width;
    cursor = row + c;                                       //����ƶ���ָ��λ��
    return *this;
}

void Screen::some_member()const{
    ++access_ctr;
}

inline Screen &Screen::set(char c){
    contents[cursor] = c;
    return *this;
}

inline Screen &Screen::set(pos r, pos c, char ch){
    contents[r * width + c] = ch;
    return *this;
}

//��Ա�������������ⲿʱ���迼�Ƕ���ǰȫ���������е�����      ��  setHeight ����
Screen::pos verify(Screen::pos);
void Screen::setHeight(pos var){
    height = verify(var);
}



class Window_mgr{                                           
public:
    using ScreenIndex = std::vector<Screen>::size_type;     //���ͳ�Ա

    void Clear(ScreenIndex);
    ScreenIndex addScreen(const Screen &);

private:
    std::vector<Screen> screens{Screen(24, 80, ' ')};       //����Screen�Ĺ��캯������һ��screen���󣬸���vector

};

void Window_mgr::Clear(ScreenIndex i){
    Screen &s = screens[i];                                 //ע�������ã����Ǹ�ֵ��
    s.contents = std::string(s.height * s.width, ' ');      //����
}

Window_mgr::ScreenIndex Window_mgr::addScreen(const Screen &s){     //ע������������������
    screens.push_back(s);
    return screens.size() - 1;                              //���ر��
}



int main() {
    Screen::pos ht = 24, wd = 80;

    Screen myScreen(5, 5, 'X');
    myScreen.move(4, 0).set('#').display(std::cout);
    std::cout << "\n";
    myScreen.display(std::cout);
    std::cout << "\n";

    return 0;
}
