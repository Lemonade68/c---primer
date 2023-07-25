#include<iostream>
#include<string>
#include<algorithm>
#include<iterator>
#include<fstream>
#include<sstream>
#include<map>
#include<exception>

using std::string;
using std::map;
using std::ifstream;

//�Լ��İ汾
map<string,string> buildMap_1(ifstream &map_file){
    map<string, string> m;
    bool iscount = true;
    string line, words, key, temp;
    while(std::getline(map_file,line)){
        std::istringstream word(line);
        word >> key;                                //��һ���ؼ��ʣ�����֮������и��ո���Ҫ����
        iscount = true;
        while(word>>temp){                          //cin��Ķ�����ʱ���Զ����Կ�ͷ�Ŀո� tab��
            if(iscount == true){
                words = temp;
                iscount = false;
            }
            else
                words = words + " " + temp;
        }
        m.insert({key, words});
        // words = line.substr(key.size() + 1);    //����Ҳ����ʵ��(����2�ķ���)
        // m.insert({key, words});
    }
    return m;
}

//���ϵİ汾
map<string,string> buildMap_2(ifstream &map_file){
    map<string, string> trans_map;
    string key, value;
    while(map_file>>key && std::getline(map_file,value)){
        if(value.size()>1)
            trans_map[key] = value.substr(1);       //����ǰ���ո�(key����һ�����ʼ�Ŀո�)
        else                                        //������ֻ�йؼ���+�� �������
            throw std::runtime_error("no rule for " + key);
    }
    return trans_map;
}


const string &transform(const string &s, const map<string,string> &m){
    auto map_it = m.find(s);
    if(map_it != m.end())
        return map_it->second;
    else
        return s;
}

void word_transform(ifstream &map_file, ifstream &input){
    map<string, string> m = buildMap_1(map_file);
    // map<string, string> m = buildMap_2(map_file);
    string line, word;
    while(std::getline(input, line)){
        std::istringstream s(line);
        while(s>>word){
            word = transform(word, m);
            std::cout << word << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Finished!" << std::endl;
}

int main(){
    ifstream map_file("../text/11_trans_rules.txt"), input("../text/11_trans_words.txt");
    if(!map_file || !input){
        std::cerr << "failed to open file!" << std::endl;
        return -1;
    }
    word_transform(map_file, input);
    return 0;
}

