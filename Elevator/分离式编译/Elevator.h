#pragma once

#include"Settings.h"
//#include"Passenger.h"		//�����໥��������elevator.cpp

#include<vector>
using std::vector;

#include<cstddef>
using std::size_t;

#include<algorithm>
using std::find_if;

class Passenger;

class Elevator{
    friend void choose_elevator_first(Passenger &);       // �˿�ѡ����ݣ����ص��ݱ�ţ������õȴ�ʱ��
    friend void choose_elevator(Passenger &);             // �˿�ѡ����ݣ����ص��ݱ�ţ������õȴ�ʱ��
    friend class Passenger;
    static size_t elevator_code;

public:
    Elevator() : isselected(true), code(elevator_code++), first_dir_up(true), set(true), 
                 isempty(true), direction_up(true), between_floors(false), waiting_pas(true), 
                 cur_floor(1),initial(true),wait_time(0), frame_chose(false) { }

    bool selected() const { return isselected; }
    bool overweighing() const { return pasgr.size() > MAXPEOPLE ? true : false; }             //�Ƿ���
    bool empty() const{ return isempty; }
    bool dir_up() const{ return direction_up; }
    bool get_bf() const { return between_floors; }
    
    //*������   
    bool wp() const { return waiting_pas; }
    bool getset() const { return set; }
    const size_t &get_fpc() const { return first_pas_code; }
    const size_t &get_count() const { return count; }
    const size_t& get_waittime() const { return wait_time; }
    //*������
    
    const size_t& get_floor() const { return cur_floor; }
    const size_t& get_code() const{ return code; }
    
    size_t get_seltd_floor_num() const { return selectedfloor.size(); }
    const vector<Passenger*> &get_pasgr() const { return pasgr; }
    
    void run(size_t);                                                   // ÿһ������ж�״̬
    void check (const vector<Passenger*>&);                             // �������û�г˿ͣ��ж��Ƿ��г˿���Ҫ�Լ�ȥ��

    //��4������
    const size_t &get_run_time() const { return running_time; }               
    const size_t &get_rest_time() const { return resting_time; }  

private:
    bool isselected;                        // �����Ƿ��ѱ�ѡ��
    bool isempty;                           // �����Ƿ�Ϊ��
    bool direction_up;                      // ���ݷ�����Ϊ���ϣ�������
    bool between_floors;                    // �Ƿ������������½����̣�¥�䣩
    bool waiting_pas;                       // �Ƿ����ڵȴ��˿����µ���
    bool initial;                           // �Ƿ�Ϊ��ʼ״̬����δ�Ӵ��˿ͣ�

    size_t code;                            // ���ݱ��
    size_t count;                           // ����  Ĭ��Ϊ0
    size_t wait_time;                       // ����¥���Ⱥ�˿����µ���ʱʹ��   ��ʼ��Ϊ0
    size_t cur_floor;                       // Ŀǰͣ��¥��
    size_t dest_floor;                      // ��һ��ͣ���㣨����û�˶�ȥ����ʱ��״̬��

    size_t new_pas_num;                     // �ò��������ĳ˿���  ��ʼ��0
    size_t lev_pas_num;                     // �ò���ȥ�ĳ˿���  ��ʼ��0

    vector<Passenger*> pasgr;               // �˿�vec��Ĭ�ϳ�ʼ��Ϊ��   ��ָ�룬ʹ���淽���޸�ԭֵ
    //selected_floor�����Ż���set���Ӷ�����ÿ�αȽϵ�ʱ��
    vector<size_t> selectedfloor;           // ����Ϊ��ʱҪȥ�ӵĳ˿͵�¥�㣬Ĭ�ϳ�ʼ��Ϊ��

    void push_pasgr(Passenger&);            // ��ӳ˿ͣ�����new_pas_num                               
    void pop_pasgr();                       // ɾ���˿ͣ�����lev_pas_num

    //���ߺ���
    void refresh();                         // ���ڶ�̬���µ����еĳ˿͵ĵ�ǰ¥��

    //��2������
    bool first_dir_up;                      // ��һ�����°�ť���˵ĳ�������
    bool set;                               // �ж��Ƿ��ǵ�һ�����°�ť���ˣ���ʼΪtrue������Ϊfalse
    size_t first_pas_code;                  // ��¼��һ�����°�ť�ĳ˿͵ı�ţ���ʼ��Ϊ0
    
    //��3������
    bool frame_chose;                       // ֡ѡ�У���������ͬһʱ�̳˿��Ⱥ��°�ť�����
    bool enabled_floor(const size_t &);     // ����¥�㣬�ж��Ƿ����ͣ��������ͣ���򷵻�true

    //��4������
    size_t running_time;                    // �ܼ�����ʱ�䣬Ĭ��Ϊ0
    size_t resting_time;                    // �ܼ���Ϣʱ�䣬Ĭ��Ϊ0

};
size_t Elevator::elevator_code = 0;         // ���Ϊ0-9  �������ʱҪд��cpp�ļ��У�����д��.h�ļ���


//size_t Elevator::elevator_code = 0;							// ���Ϊ0-9����̬������ȫ�ֱ�����Ҫ��cpp�г�ʼ��
