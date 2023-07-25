#include<iostream>
#include<vector>
#include<string>
#include<ctime>
#include<cmath>
#include<Windows.h>
#include<algorithm>

#include"Elevator.h"
#include"Passenger.h"
#include"Settings.h"

using std::cout;
using std::cerr;
using std::endl;
using std::vector;

extern vector<Passenger*> pas_wait_list;				//ȫ�ֺ;�̬����Ӧ����ĳ��cpp�ļ��ж��壬�����ط�ʹ��extern����
extern vector<Elevator> ele_vec;						// ��ʼ��10������, ע����߲�������(ELE_NUM)����Ȼ�Ƕ����ˣ�  ����Ӧ��������

int main() {
	srand((unsigned)time(NULL));                        //�������������
	vector<Passenger> pasgr_vec(N);                     //��ʼ��N���˿ͣ������Ѿ���һ��ʼȫ��������

	cout << "Simulation starts, passengers' information are as follows:" << endl << endl;
	for (const auto &p : pasgr_vec)
		cout << p.getcode() << "--" << p.getdest() << " arrives at " << p.get_arrive_time() << " , selects elevator " << p.get_ele_num() << endl;
	cout << endl;
	for (const auto & e : ele_vec) {
		cout << "Elevator " << e.get_code() << " (cur_floor: " << e.get_floor() << ") Passengers:\t";
		for (const auto & p : e.get_pasgr())
			cout << p->getcode() << "--" << p->getdest() << " ;\t";
		cout << endl;
	}
	system("pause");                                    //�����Լ���

	size_t timer = 0;                                   //��ʱ��

	while (Passenger::pas_remained != 0) {                //����ʱ��ѭ������û�г˿���Ҫ������ʱ��������
		system("cls");
		//���в���: �ȳ˿�, �����
		for (auto &p : pasgr_vec)
			if (!p.finished())                           //�����û�������������иó˿�
				p.run(timer, ele_vec);
		for (auto &e : ele_vec)
			e.run(timer);

		//��ӡ����
		for (const auto & e : ele_vec) {
			//����ʱ��ʾ״̬��
			cout << "Elevator " << e.get_code() << ((e.get_pasgr().size() == 0 && e.get_seltd_floor_num() == 0) ? " - " : (e.dir_up() ? " �� " : " �� ")) << "\t"
				<< "(cur_floor:" << e.get_floor() << ")" << "\tfirst_pas_code: " << e.get_fpc()
				<< "\twait_time: " << e.get_waittime() << "\t Passengers: \t";
			for (const auto & p : e.get_pasgr())
				cout << p->getcode() << "--" << p->getdest() << ";\t";
			cout << endl;
			//�����ô���
			cout << "isselected:" << (e.selected() ? " true" : " false") << "\twaiting_pas:" << (e.wp() ? " true" : " false") << "\tbetween_floor:" << (e.get_bf() ? " true" : " false") << "\tset: " << (e.getset() ? " true" : " false") << endl;
			cout << endl;
		}
		cout << endl;
		cout << "Remained Passengers' List:" << endl;
		if (pas_wait_list.size() == 0)
			cout << "None!" << endl << endl;
		else {
			for (const auto &p : pas_wait_list) {
				cout << p->getcode() << "\tarrives at " << p->get_arrive_time() << "\tselects elevator ";
				if (p->get_counter() < p->get_wait_time())
					cout << "/";
				else if (p->get_ele_num() == ELE_NUM)
					cout << "/";
				else
					cout << p->get_ele_num();
				cout << "\tcurrent_floor: " << p->getcur() << "\tdest_floor: " << p->getdest() << "\t  wait_time: " << p->get_wait_time() << "\t  Total_took_time_L: " << p->get_L() << "\ttook_time: " << p->get_took_time()
					<< "\tis_ready:" << ((p->get_counter() >= p->get_wait_time()) ? " Yes " : " No ") << endl;
			}
			cout << endl;
		}

		cout << "Number of Remained Passengers: " << Passenger::pas_remained << endl;
		cout << endl;
		cout << "current time: " << timer << endl;
		cout << endl;
		++timer;

		//����
		if (MODE == 1)
			system("pause");                                    //�ֶ�����
		else if (MODE == 2)
			Sleep(1000 / play_speed);                             //�Զ����ţ����Ը��Ĳ����ٶ�
		else {
			cerr << "MODE FAULT!" << endl;
			return -1;
		}

	}

	//�����󣬴�ӡ�������ݵ�����ʱ��͵ȴ�ʱ�䣬�Լ��˿Ͱ��°�ť��ĵȴ�ʱ��
	cout << endl;
	for (const auto & e : ele_vec)
		cout << "Elevator " << e.get_code() << "\trunning time: " << e.get_run_time() << "  \tresting time: " << e.get_rest_time() - 1 << endl;
	cout << endl;
	for (const auto &p : pasgr_vec) {
		cout << "Passenger " << p.getcode() << "\twaiting time:\t";
		for (const auto &a : p.get_vec())
			cout << a << ", ";
		cout << endl;
	}
	cout << endl;
	cout << "Finished! :D" << endl;
	Sleep(5000);
	return 0;
}