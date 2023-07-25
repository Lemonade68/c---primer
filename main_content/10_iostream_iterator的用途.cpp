#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<functional>
#include<iterator>

using namespace std;
using namespace std::placeholders;

int main(){
    // istream_iterator<int> in_iter(cin), eof;
    // vector<int> vec(in_iter, eof);
    istream_iterator<string> it(cin), eof;
    ostream_iterator<string> out(cout, " ");
    
    vector<string> vec(it, eof);

    copy(vec.begin(), vec.end(), out);  //ʹ��copy������ļ�д��
    cout << endl;

    for(auto e : vec)       //���ʱʹ��ostream_iterator��д��
        *out++ = e;
    cout << endl;

    return 0;
}
