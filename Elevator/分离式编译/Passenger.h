#pragma once

#include"Settings.h"
#include"Elevator.h"

#include<vector>
using std::vector;

#include<cstddef>
using std::size_t;

#include<algorithm>
using std::find_if;

class Passenger {
	friend void choose_elevator_first(Passenger &);                 // �˿�ѡ����ݣ����ص��ݱ��
	friend void choose_elevator(Passenger &);                       // �˿�ѡ����ݣ����ص��ݱ�ţ������õȴ�ʱ��
	friend class Elevator;
	static size_t pas_code;

public:
	static size_t pas_remained;                                     // ʣ��δ����Ŀ�ĵس˿���
	Passenger();

	void run(size_t, vector<Elevator>&);                            // ÿ���ж�״̬
	bool finished() const { return finishd; };                      // �ж��Ƿ񵽴�Ŀ�ĵ�¥��
	bool pressup() const { return dest_floor > cur_floor; }         // �Ƿ������ϼ�

	const size_t &getcode() const { return code; }
	const size_t &getdest() const { return dest_floor; }
	const size_t &getcur() const { return cur_floor; }
	const size_t &get_ele_num() const { return ele_code; }
	const size_t &get_arrive_time() const { return arrive_time; }
	const size_t &get_wait_time() const { return wait_time; }
	const size_t &get_L() const { return L; }
	const size_t &get_took_time() const { return took_time; }
	const size_t &get_counter() const { return counter; }

	//��4������
	vector<size_t> get_vec() const { return pas_resting_time_vec; }

private:
	bool arrived;                                   // ��ʼʱ�Ƿ��Ѿ�����1��                        
	bool on_ele;                                    // �Ƿ��ڵ�����
	bool finishd;                                   // �˿ͽ�������
	size_t code;                                    // �˿ͱ��
	size_t dest_floor;                              // Ŀ��¥�㣨�����ɸ���   ע�ⲻ���������ǰ��¥�㣩  
	size_t cur_floor;                               // Ŀǰ¥�㣨������ݣ�   
	size_t arrive_time;                             // �˿͵ȴ�����ʱ�䣨������һ�Σ�
	size_t ele_code;                                // �������ĵ��ݵı��

	//��2���ϻ�����
	size_t L;                                       // Ҫ�����ĵ��ݵĴ���
	size_t took_time;                               // �������ĵ��ݵĴ�������ʼ��Ϊ0
	size_t wait_time;                               // ��¥���ϵȴ���ʱ��
	size_t counter;                                 // �ȴ�ʱ�ļ���������ʼ��Ϊ0

	//��3���ϻ�����
	bool chosen_ele;                                // �ȴ��������Ƿ��Ѿ�ѡ����˵���

	// ���ߺ���
	// size_t cal_wait_time(const Elevator &);      // ����ȴ�ʱ��

	//��4���ϻ�����
	vector<size_t> pas_resting_time_vec;            // �˿ͷ����˿�Ҫ���ĵȴ�ʱ��ļ���
	size_t tmp_time;                                // ��¼����Ҫ���ʱ�䣬��ʼ=arrive_time
	bool press_button;                              // �Ƿ��°�ť
};
void choose_elevator_first(Passenger &);       // �˿�ѡ����ݣ����ص��ݱ�ţ������õȴ�ʱ��
void choose_elevator(Passenger &);             // �˿�ѡ����ݣ����ص��ݱ�ţ������õȴ�ʱ��
//��Ҫ��cpp�г�ʼ����������ͷ�ļ��г�ʼ��
//size_t Passenger::pas_remained = N;
//size_t Passenger::pas_code = 1;
// vector<Passenger> Passenger::wait_list;

