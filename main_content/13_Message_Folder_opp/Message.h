#ifndef MESSAGE
#define MESSAGE

#include<string>
using std::string;

#include<set>
using std::set;

#include<iostream>
using std::cerr;
using std::endl;

class Folder;                       //ǰ�����������У���Ȼ����Message����ĺ���Folder����ʾδ����

class Message{
    friend class Folder;
    friend void swap(Message &, Message &);

public:
    //folders����ʽ��ʼ��Ϊ�ռ���
    explicit Message(const string &str = " "): contents(str){}
    //�������Ƴ�Ա�����ڹ���ָ��Message��ָ��
    Message(const Message &);
    Message(Message &&);
    Message &operator=(const Message &);
    Message &operator=(Message &&);
    ~Message();
    //�Ӹ���Folder���������/ɾ����Message
    void save(Folder &);
    void remove(Folder &);

    void debug_print();             //��ӡ���ݣ���������ʹ��

private:
    string contents;                // ʵ���ı���Ϣ
    set<Folder *> folders;          //������Message��Folder
  
    //�������캯����������ֵ�����������������ʹ�õĹ��ߺ���
    //����Message��ӵ�ָ�������Folder��
    void add_to_Folders(const Message &);
    void remove_from_Folders();

    //��Folders��ʹ�õĹ��ߺ���
    void addFldr(Folder *f) { folders.insert(f); }
    void remFldr(Folder *f) { folders.erase(f); }

    //���ƶ�����͸�ֵ�����ʹ�õĹ��ߺ���
    void move_Folders(Message *);           //����ָ��ԭMessage��Folders
};



class Folder{
    friend class Message;
    friend void swap(Message &, Message &);

public:
    Folder() = default;
    Folder(const Folder &);
    Folder &operator=(const Folder &);
    ~Folder();

    void save(Message &);
    void remove(Message &);

    void debug_print();             //��ӡ���ݣ���������ʹ��

private:
    set<Message *> messages;

    //���������캯�������������Ϳ�����ֵ�����ʹ�õĹ��ߺ���
    void add_to_msgs(const Folder &);                   // һ����ӵ����������messages�����У���Ϊ�ǿ�����
    void remove_from_msgs();                            // һ���������messages������ɾ��

    void addMsg(Message *m) { messages.insert(m); }
    void remMsg(Message *m) { messages.erase(m); }
};


//ע��δ����noexcept����Ϊ��set�в���Ԫ�ؿ��ܻ��׳��쳣
void Message::move_Folders(Message *m){
    folders = std::move(m->folders);                    //ʹ��set���ƶ���ֵ�����
    for(auto f :folders){                               //�ı�Folder�б����Messageָ��
        f->remMsg(m);
        f->addMsg(this);
    }
    m->folders.clear();
}


Message::Message(const Message &m) : contents(m.contents),folders(m.folders){
    add_to_Folders(m);
}

Message::Message(Message &&m):contents(m.contents){
    move_Folders(&m);           //�ƶ�folders������Folderָ��
}


void Message::save(Folder &f){
    folders.insert(&f);
    f.addMsg(this);
}

void Message::remove(Folder &f){
    folders.erase(&f);
    f.remMsg(this);
}

//����message��ӵ�ָ��m��Folder��
void Message::add_to_Folders(const Message &m){         //���const����Ϊset�ж���ĵ�ַ��û�иı�
    //ʹ��range forû�����ԭ������ĵ��ǳ�Աָ��ĵط��Ķ��󣬶���Ա������ַ��û�б�
    //������³�����Ļ����԰���������д
    for(auto f : m.folders)                             
        f->addMsg(this);        //���һ��ָ��message��ָ��
}

void Message::remove_from_Folders(){
    for(auto f : folders)
        f->remMsg(this);
}

Message::~Message(){
    remove_from_Folders();
}

//Ҳִ�п������캯����������������Ϊ������Ҫע���Ը�ֵ����
Message& Message::operator=(const Message &m){
    remove_from_Folders();
    contents = m.contents;
    folders = m.folders;
    add_to_Folders(m);                      //��add��remove�Ļ���������Ը�ֵ�����ߵ�ַһ������ȫ��ɾ��
    return *this;
}

//�ƶ���ֵ�����ֱ�Ӽ���Ը�ֵ���
Message& Message::operator=(Message &&rhs){
    if(this != &rhs){                       //ֱ�Ӽ���Ը�ֵ
        remove_from_Folders();
        contents = std::move(rhs.contents);
        move_Folders(&rhs);                 //����Foldersָ��Message
    }
    return *this;
}



void swap(Message &lhs, Message &rhs){      //lhs�Ǹ�ֵ��Ŀ�ĵأ�rhs�Ǹ�ֵ��Դͷ��=���ң�
    using std::swap;                        //���ϸ�Ҫ������д�����Ǹ���ϰ��

    for(auto f : lhs.folders)
        f->remMsg(&lhs);
    for(auto f : rhs.folders)
        f->remMsg(&rhs);

    swap(lhs.contents, rhs.contents);
    swap(lhs.folders, rhs.folders);

    for(auto f : lhs.folders)
        f->addMsg(&lhs);
    for (auto f : rhs.folders)
        f->addMsg(&rhs);
}







void Folder::add_to_msgs(const Folder &f){
    for(auto m : f.messages)
        m->addFldr(this);
}

Folder::Folder(const Folder &f) : messages(f.messages) { 
    add_to_msgs(f); 
}

void Folder::remove_from_msgs(){
    while (!messages.empty())
        (*messages.begin())->remove(*this);             //��Ϊremoveʱ��һ������message.begin()��ɾ����
}

Folder::~Folder(){
    remove_from_msgs();
}

Folder& Folder::operator=(const Folder &rhs){
    remove_from_msgs();
    messages = rhs.messages;
    add_to_msgs(rhs);
    return *this;
}

void Folder::save(Message &m){
    messages.insert(&m);
    m.addFldr(this);
}

void Folder::remove(Message &m){
    messages.erase(&m);
    m.remFldr(this);
}


void Folder::debug_print(){
    cerr << "Folder contains: " << messages.size() << " messages " << endl;
    int ctr = 1;
    for(const auto &m : messages)
        cerr << "Message " << ctr++ << ":\n\t" << m->contents << endl;
}

void Message::debug_print(){
    cerr << "Message:\n\t" << contents << endl;
    cerr << "Appears in " << folders.size() << " Folders " << endl;
}


#endif