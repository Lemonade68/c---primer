#include <iostream>
#include <vector>

using namespace std;

void func_9_3_8() {
    vector<int> ivec;
    // size Ӧ��Ϊ 0��capacity ��ֵ�����ھ���ʵ��
    cout << "ivec: size: " << ivec.size()
         << " capacity: " << ivec.capacity() << endl;
    // ivec: size: 0 capacity: 0

    // �� ivec ��� 24 ��Ԫ��
    for (vector<int>::size_type ix = 0; ix != 24; ++ix)
        ivec.push_back(ix);
    // size Ӧ��Ϊ 24��capacity Ӧ�ô��ڵ��� 24������ֵ�����ڱ�׼��ʵ��
    cout << "ivec: size: " << ivec.size()
         << " capacity: " << ivec.capacity() << endl;
    // ivec: size: 24 capacity: 32

    ivec.reserve(50);       // �� capacity �����趨Ϊ 50�����ܻ����
    // size Ӧ��Ϊ 24��capacity Ӧ�ô��ڵ��� 50������ֵ�����ڱ�׼��ʵ��
    cout << "ivec: size: " << ivec.size()
         << " capacity: " << ivec.capacity() << endl;
    // ivec: size: 24 capacity: 50

    // ���Ԫ���ù��������
    while (ivec.size() != ivec.capacity())
        ivec.push_back(0);
    // capacity Ӧ��δ�ı䣬size �� capacity ���
    cout << "ivec: size: " << ivec.size()
         << " capacity: " << ivec.capacity() << endl;
    // ivec: size: 50 capacity: 50

    ivec.push_back(42);     // �����һ��Ԫ��
    // size Ӧ��Ϊ 51��capacity Ӧ�ô��ڵ��� 51������ֵ�����ڱ�׼��ʵ��
    cout << "ivec: size: " << ivec.size()
         << " capacity: " << ivec.capacity() << endl;
    // ivec: size: 51 capacity: 100

    ivec.shrink_to_fit();   // Ҫ��黹�ڴ�
    // size Ӧ��δ�ı䣨51����capacity ��ֵ�����ھ���ʵ��
    cout << "ivec: size: " << ivec.size()
         << " capacity: " << ivec.capacity() << endl;
    // ivec: size: 51 capacity: 51
}


void func_9_3_9() {
    vector<string> svec;
    svec.reserve(1024);
    // size Ӧ��Ϊ 0��capacity ��ֵ�����ھ���ʵ��
    cout << "svec: size: " << svec.size()
         << " capacity: " << svec.capacity() << endl;

    // ���� 256 ����
    int count = 0;
    while (count != 1024) {
        svec.push_back("C++");
        ++count;
    }
    // capacity Ӧ��δ�ı䣬size �� capacity ���
    cout << "svec: size: " << svec.size()
         << " capacity: " << svec.capacity() << endl;
    
    // resize �� svec ĩβ��ӵ�ǰ�ַ�������һ����ô��
    // �����ַ��������ǵ�ֵ���ǿմ������ռ䲻���������
    // �㹻������Щ���ַ������ڴ�ռ�
    svec.resize(svec.size() + svec.size() / 2);
    // capacity Ӧ��δ�ı䣬size �� capacity ���
    cout << "svec: size: " << svec.size()
         << " capacity: " << svec.capacity() << endl;

}


int main(){
    func_9_3_8();
    cout << "-----------------------------" << endl;
    func_9_3_9();
    return 0;
}
