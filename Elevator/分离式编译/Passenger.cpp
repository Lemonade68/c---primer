#include"Passenger.h"
#include"Elevator.h"
#include"Settings.h"
using namespace std;

size_t Passenger::pas_remained = N;
size_t Passenger::pas_code = 1;
// vector<Passenger> Passenger::wait_list;

vector<Passenger*> pas_wait_list;                   // ���ڵȴ�������(ֱ��ֵ��������)  ��̬������ȫ�ֱ�����Ҫ��cpp�г�ʼ��
extern vector<Elevator> ele_vec;                  	// ��ʼ��10�����ݣ�ע����߲�������(ELE_NUM)����Ȼ�Ƕ����ˣ�  ����Ӧ��������



void push_wait_list(Passenger *p) {
	pas_wait_list.push_back(p);
}

void pop_wait_list(Passenger *p) {
	auto it = std::find_if(pas_wait_list.begin(), pas_wait_list.end(), [&p](Passenger *pas) { return pas->getcode() == p->getcode(); });
	if (it != pas_wait_list.end())
		pas_wait_list.erase(it);
}


//�˿�ѡ����ݲ���
void choose_elevator_first(Passenger& p) {
	vector<size_t> enabled_ele;                             //����ѡ��ĵ��ݼ���
	int i = 0;
	//����õ��ݿ��Ե����¥�㣬����ӵ�������
	for (; i < ELE_NUM; ++i)
		if (ele_vec[i].enabled_floor(p.dest_floor))
			enabled_ele.push_back(i);
	size_t sz = enabled_ele.size();
	p.ele_code = enabled_ele[rand() % sz];                  //������ɳ�ʼѡ��ĵ��ݱ��(�±�Ϊ0 ~ sz-1)
	ele_vec[p.ele_code].isselected = true;                  //�øõ��ݱ�ѡ��
}

void choose_elevator(Passenger &p) {
	//�е���δ��ѡ���ҷ������������
	vector<size_t> en_ele;
	size_t i = 0, least = 0, last = 0;                      //least��ʾ���е����о��Լ������¥���ֵ
	bool first = true, all_is_selected = true;
	for (; i < ELE_NUM; ++i) {
		if (ele_vec[i].enabled_floor(p.dest_floor) && ele_vec[i].enabled_floor(p.cur_floor)) {         //����ȥ��dest_floor������뼯��
			en_ele.push_back(i);
			//����õ���δ��ѡ�л�ѡ�е���initial����δ��֡ѡ��
			if ((!ele_vec[i].isselected || (ele_vec[i].isselected && ele_vec[i].initial)) && !ele_vec[i].frame_chose) {
				if (first) {                                  //����ǵ�һ��,ֱ������least
					first = false;
					last = i;
					ele_vec[i].frame_chose = true;
					all_is_selected = false;                //˵���е��ݿ���
					least = abs(int(ele_vec[i].cur_floor) - int(p.cur_floor));      //ǿ������ת���£�abs����size_t������Ч
					p.ele_code = i;
				}
				else {                                       //���ǵ�һ�����ȽϺ�����least  
					int tmp = abs(int(ele_vec[i].cur_floor) - int(p.cur_floor));
					if (tmp < least) {
						least = tmp;
						p.ele_code = i;
						ele_vec[last].frame_chose = false;
						ele_vec[i].frame_chose = true;
						last = i;
					}
				}
			}
		}
	}
	//�������еĻ����ѡ��һ������ȥ�ĵ���
	if (all_is_selected)                                     //������е��ݶ����ڱ�ʹ��
		p.ele_code = en_ele[rand() % (en_ele.size())];      //����ڿ���ȥ���ĵ�����ѡ��һ���ȴ�
}


//��ʼ���˿Ͷ���
Passenger::Passenger() : arrived(false), code(pas_code++), cur_floor(1), on_ele(false), finishd(false), chosen_ele(true), press_button(false) {
	arrive_time = rand() % M;                               //����0-M�ĵ���ʱ��
	dest_floor = rand() % 39 + 2;                           //����2-40�����Ŀ��¥��
	//���ݹ�����ĺ󣬳˿ͳ�ʼѡ����ݣ�
	choose_elevator_first(*this);
	L = rand() % MAX_Times + 1;                             //�������Ҫ�����Ĵ�����10̫�࣬����3������
	push_wait_list(this);                                   //����Ⱥ�����
}


void Passenger::run(size_t cur_time, vector<Elevator>& ele_vec) {
	//�Ѿ�����Ŀ�ĵأ��򷵻�
	if (finishd)
		return;
	if (cur_time >= arrive_time)
		arrived = true;

	//����ڵ����ϻ���δ���ֳ������أ�ǰ�߽��������ദ��
	if (on_ele || !arrived)
		return;

	if (counter < wait_time) {                            //����ȴ�ʱ�䣬���֮���°�ť
		++counter;
		return;
	}

	//��¼�°��°�ť��ʱ��
	if (!press_button) {
		press_button = true;
		tmp_time = cur_time;
	}

	//ѡ���µĵ��ݣ������µ�ele_code(������֮��ֱ���´εȴ�ǰ����������ѡ��¥��)
	if (!chosen_ele) {
		choose_elevator(*this);
		ele_vec[ele_code].initial = false;              //���ĵ��ݳ�ʼ״̬
		chosen_ele = true;
		return;                                         //��ֹ�˴ξ�ֱ���ϵ��ݣ��Ӷ��������һֱ����δ��ѡ�е�״̬
	}
	// if(!ele_vec[ele_code].isselected)                   //����ֱ��δ��ѡ���ˣ��ٸĻ�ȥ����֡����ѡ��
		// chosen_ele = false;

	//ѡ��ĵ��ݲ���ͬһ��¥���ȴ�
	if (ele_vec[ele_code].get_floor() != cur_floor)
		return;
	//����������¥��䣬�ȴ�
	if (ele_vec[ele_code].between_floors == true)
		return;
	//���ϵ��ݵ��³��أ��ȴ�
	if (ele_vec[ele_code].get_pasgr().size() + 1 > MAXPEOPLE)
		return;
	//���������Լ���Ҫȥ�ķ���ͬ�ҵ��������ˣ��ȴ���û��˵����ר�����ӵģ�������ܻ᲻ͬ���������ϵ��ݣ�
	if (ele_vec[ele_code].dir_up() != pressup() && ele_vec[ele_code].pasgr.size() != 0)
		return;
	//�������ͬ�ҵ������ˣ����Լ����ǵ���Ҫ�ӵĵ�һ���˿ͣ�����
	if (ele_vec[ele_code].dir_up() != pressup() && ele_vec[ele_code].pasgr.size() == 0 && ele_vec[ele_code].first_pas_code != code)
		return;
	//������ݾ����Լ��Һ��Լ�������ͬ�������ڽӵ�һ���˿ͺ�Ҫȥ�ķ�����Լ��෴�����Ȳ��ϵ���
	if (ele_vec[ele_code].first_dir_up != pressup())
		return;

	counter = 0;                                        //counter����
	wait_time = 0;                                      //wait_time����
	pop_wait_list(this);                                //�ӵȺ�����ɾ��

	//��¼�°��°�ť���ϵ��ݵĵȴ�ʱ��
	pas_resting_time_vec.push_back(cur_time - tmp_time);
	press_button = false;

	ele_vec[ele_code].push_pasgr(*this);                //���Լ����뵽��������
	on_ele = true;
}