#include"Elevator.h"
#include"Passenger.h"										//����include  ��Ȼ����c2061��   ��Ϊ����ͷ�ļ������໥����
#include"Settings.h"

size_t Elevator::elevator_code = 0;							// ���Ϊ0-9����̬������ȫ�ֱ�����Ҫ��cpp�г�ʼ��

extern vector<Passenger*> pas_wait_list;                    // ���ڵȴ�������
vector<Elevator> ele_vec(ELE_NUM);							// ��ʼ��10������



//��3���ϻ�����
bool Elevator::enabled_floor(const size_t &floor) {
	switch (code) {                                          // �Ե��ݵ�code�����жϴ����¥���Ƿ�ɴ�
	case 0: case 1:
		return true;
	case 2: case 3:
		if (floor == 1 || floor >= 25)
			return true;
		else
			return false;
	case 4: case 5:
		if (floor <= 25)
			return true;
		else
			return false;
	case 6: case 7:
		if (floor == 1 || (floor % 2 == 0))
			return true;
		else
			return false;
	case 8: case 9:
		if (floor % 2 == 1)
			return true;
		else
			return false;
	default:
		return true;
	}
}


// �˿���������ʹ��
// �����ĳ˿�һ����˳�ŵ��ݷ����
void Elevator::push_pasgr(Passenger& p) {
	pasgr.push_back(&p);
	isempty = false;

	//�����selectedfloor�б��ϣ���selectedfloor�Ͻ���ɾ��
	auto it = std::find_if(ele_vec[p.ele_code].selectedfloor.begin(), ele_vec[p.ele_code].selectedfloor.end(), [&p](const size_t &a) {return a == p.cur_floor; });
	if (it != ele_vec[p.ele_code].selectedfloor.end())
		ele_vec[p.ele_code].selectedfloor.erase(it);

	if (p.code == first_pas_code) {               //����Ǹõ��ݿճ˿�ʱ��һ�����°�ť�ĳ˿�
		set = true;                             //����
		// first_pas_code = 0;                     //����
	}

	//���Ŀǰ����ֻ��1�ˣ���ô�������з�����Ǹó˿�Ҫȥ�ķ���
	if (pasgr.size() == 1) {
		direction_up = p.pressup();
		first_dir_up = p.pressup();
	}

	//�����˿���+1
	++new_pas_num;
}
//ע���޸ĵ�����Ϣempty���ж��Ƿ��޸ķ���ѡ�У���һ��ͣ����


//���������ʹ�ã�������ȥ�������������øó˿���һ�ε����ݣ�ÿ��runʱʹ�ü���
void Elevator::pop_pasgr() {
	static size_t count = 0;                                    //��ȥ�˿͵�����
	count = 0;
	auto it = std::find_if(pasgr.begin(), pasgr.end(), [this](Passenger *p) {return cur_floor == p->dest_floor; });
	while (it != pasgr.end()) {
		++count;

		if ((*it)->code == first_pas_code)                           //��һλ�˿��µ��ݣ����������Ϊ0
			first_pas_code = 0;
		//���� *�´ε�* ״̬
		(*it)->took_time++;                                         //���ǵڼ���
		(*it)->on_ele = false;
		(*it)->chosen_ele = false;                                  //��������Ϊ��δѡ��
		(*it)->ele_code = ELE_NUM;                                  //��������λ����ֹ�������¼�����

		// (*it)->wait_time = rand() % 111 + 10;                    //����´ε�����ȴ�ʱ��
		(*it)->wait_time = rand() % 11 + 10;                        //����´ε�����ȴ�ʱ�䣨�Ȱ�10-20�㣩
		(*it)->counter = 0;                                         //����������
		if ((*it)->took_time < (*it)->L) {                            //����С��L�Σ���������´ε�dest_floor��������L�Σ�
			(*it)->dest_floor = rand() % 39 + 2;
			while ((*it)->cur_floor == (*it)->dest_floor)            //����������㣬�������
				(*it)->dest_floor = rand() % 39 + 2;
		}
		else if ((*it)->took_time == (*it)->L) {                      //��L���µ��ݣ�����L+1�ε�״̬
			(*it)->dest_floor = 1;
		}
		else {                                                       //��L+1���µ���
			(*it)->wait_time = 0;                                   //״̬��0
			(*it)->finishd = true;                                  //�˿͵���1�㣬��������
		}

		if (!(*it)->finished())                                      //������滹û�������ټӻ�wait_list 
			pas_wait_list.push_back(*it);
		else if ((*it)->cur_floor == (*it)->dest_floor)              //���isfinished�����Ѿ�����Ŀ��¥�㣨1�㣩
			--Passenger::pas_remained;                              //ʣ��ĳ˿���-1

		pasgr.erase(it);
		it = std::find_if(pasgr.begin(), pasgr.end(), [this](Passenger *p) {return cur_floor == p->dest_floor; });
	}
	lev_pas_num = count;                                            //��¼ �µ��ݵĳ˿���
}


void Elevator::refresh() {
	for (auto &p : pasgr) {
		p->cur_floor = cur_floor;
	}
}


//����new_pas_num �� lev_pas_num
//������һʱ�̵��ݵ�״̬

void Elevator::run(size_t cur_time) {
	// ��߲�������static count = 0         �����⣡��     //������Ķ����ڵ��øú���ʱ�����������

	//ÿһʱ�̿�ʼ��ˢ��֡ѡ��
	frame_chose = false;

	if (pasgr.size() != 0)
		initial = false;
	if (initial) {                                        //���ݴ��ڳ�ʼ״̬��ֱ�ӷ���
		++resting_time;
		return;
	}
	check(pas_wait_list);                               //����ʱ���Ƿ�������Ҫ��������
	if (!isselected) {                                    //û���򷵻�
		waiting_pas = true;
		between_floors = false;
		++resting_time;                                 //�ȴ�ʱ��++
		return;
	}

	//���û���˳�����Ϊ��ѡ��
	++running_time;                                     //����ʱ��++

	//01 �ж��Ƿ�Ϊ�ȴ�����
	if (waiting_pas) {
		// cout << code << " wp" << endl;
		pop_pasgr();                                                //���ó˿���ȥ���õ���ȥ�������������������ɳ˿����ṩ
		wait_time += (new_pas_num + lev_pas_num) * T;               //���õȴ�ʱ��

		//�м��״̬        
		if (new_pas_num + lev_pas_num == 0 && wait_time == 0) {       //�����һʱ�̼Ȳ������˿�Ҳ����ȥ�˿��Ҳ���Ҫ�ٵȴ�  ֱ������һ����
			waiting_pas = false;
			between_floors = true;
			count = 0;
			goto FLAG;                                  //�������������½�ѭ��
		}

		//�ȴ���״̬
		if (count >= wait_time) {                         //�ȴ���ɣ�ִ����һ��
			count = 0;
			new_pas_num = 0;                            //���״̬
			lev_pas_num = 0;                            //���״̬
			waiting_pas = false;
			between_floors = true;
			return;
		}
		++count;                                        //ÿһ��count + 1
		new_pas_num = 0;
		lev_pas_num = 0;
		return;
	}
	//02 �ж��Ƿ�Ϊ�������½�����
	else if (between_floors) {
	FLAG:
		// cout << code << " bf" << endl;
		wait_time = S;                                  //������һ���ʱ��
		if (count >= wait_time) {                         //��߸ĳ�==�������⣿     Ϊɶ
			if (direction_up) {
				++cur_floor;
				refresh();
			}
			else {
				--cur_floor;
				refresh();
			}
			wait_time = 0;
			count = 0;
			new_pas_num = 0;
			lev_pas_num = 0;
			between_floors = false;
			waiting_pas = true;
			return;
		}
		++count;
		return;
	}
	// �ǵ����ȸ������г˿͵�Ŀǰ¥�㣬������¥����״̬��isempty״̬
}


//*****************************************************
//���ĵ�ǰ���ݵ�isselected, selected_floor, direction_up״̬����װ���������˰���selected_floor��
void Elevator::check(const vector<Passenger*> &wait_list) {
	// �ж��Ƿ��г˿�
	static bool sign;                                                                           //�Լ��Ƿ���ó˿�ͬ¥��
	sign = false;
	if (pasgr.size() == 0) {
		//����wait_list���Ƿ��г˿���Ҫ�Լ����ӣ����ȳ���һ�����°�ť�ĳ˿ͣ�ʹ��push_back���������wait_list�ں��棩
		for (const auto &p : wait_list) {
			if (p->counter >= p->wait_time && p->ele_code == code) {                              //�˿�ѡ�е����ҳ˿��Ѿ��ȴ���ϣ���ʱ���°�ť�����ҵ�һ������ť�ĳ˿�
				if (cur_floor == p->cur_floor) {
					wait_time = 2;                                                              //�������㣺���ݲ�ͣ�ȴ�
					if (set) {
						sign = true;
						first_pas_code = p->code;                                               //��¼�ó˿͵ı��
						direction_up = p->pressup();
						first_dir_up = p->pressup();                                            //���øó˿ͽ�Ҫȥ�ķ���
					}
				}
				else {
					if (set) {
						first_pas_code = p->code;
						direction_up = (cur_floor > p->cur_floor) ? false : true;               //���÷���
						first_dir_up = p->pressup();
					}
				}
				//����δ��ӹ��������
				auto it = std::find_if(selectedfloor.begin(), selectedfloor.end(), [&p](const size_t &a) {return a == p->cur_floor; });
				if (it == selectedfloor.end())
					selectedfloor.push_back(p->cur_floor);
				set = false;
			}
		}
		if (selectedfloor.size() == 0) {
			set = true;                                     //���һֱû��ѡ��,set���ϻ�ԭΪtrue�����ֻ�ڳ˿���ӵĻ�������˿�ǰsetΪfalse���Ӳ���ȥ����ֻ�н�ȥ�˲��ܱ��true
			isselected = false;
			count = 0;
			wait_time = 0;
			waiting_pas = true;
			between_floors = false;
		}
		else {
			if (sign) {
				isselected = true;
				waiting_pas = true;
				between_floors = false;
			}
			else {
				isselected = true;
				waiting_pas = false;
				between_floors = true;                      //���ó�false : �Ա��ڵ�ǰ��ĳ˿Ϳ���ֱ�����������run�еĸ���waiting_pas״̬ʹ�ã� 
			}
		}
	}
}
//*****************************************************

