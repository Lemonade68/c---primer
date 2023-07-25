//�˿������ʲôʱ���ϵ��ݣ����������ʲôʱ���³˿�

#include<iostream>
#include<vector>
#include<string>
#include<ctime>
#include<cmath>
#include<Windows.h>
#include<algorithm>

#define MAXPEOPLE 10        // ��������ؿ���
#define ELE_NUM 10          // ������
#define N 12                // �˿���
#define M 10                // �����ʱ��γ���(��)
#define S 3                 // ��������ʱS��ÿ��
#define T 2                 // ÿ���˿����µ��ݵ�ʱ��
#define play_speed 10       // ���ٲ��ţ�*n��

// enum elevator_status{halt,waiting,runing};

using std::cout;
using std::endl;
using std::vector;


class Passenger;

class Elevator{
    size_t friend choose_elevator(Passenger &, vector<Elevator> &);     // �˿�ѡ����ݣ����ص��ݱ�ţ������õȴ�ʱ��
    friend class Passenger;
    static size_t ele_code;

public:
    Elevator() : isselected(true), code(ele_code++), isempty(true), direction_up(true), between_floors(false), waiting_pas(true), cur_floor(1),initial(true), wait_time(0) { }
    void run(size_t);                               //ÿһ������ж�״̬

public:
    bool overweighing() const
        { return pasgr.size() > MAXPEOPLE ? true : false; }             //�Ƿ���
    bool empty() const{ return isempty; }
    bool dir_up() const{ return direction_up; }
    //������   
    bool selected() const { return isselected; }
    bool wp() const { return waiting_pas; }
    const size_t &get_count() const { return count; }


    const size_t &get_waittime() const { return wait_time; }
    const size_t& get_floor() const { return cur_floor; }
    const size_t& get_code() const{ return code; }
    bool get_bf() const { return between_floors; }
    const vector<Passenger*> &get_pasgr() const { return pasgr; }
    void push_pasgr(Passenger&);            // ��ӳ˿ͣ�����new_pas_num                               
    void pop_pasgr();                       // ɾ���˿ͣ�����lev_pas_num
    void check (const vector<Passenger>&);                           // �������û�г˿ͣ��ж��Ƿ��г˿���Ҫ�Լ�ȥ��


private:
    size_t code;                            // ���ݱ��
    bool isselected;                        // �����Ƿ��ѱ�ѡ��
    bool isempty;                           // �����Ƿ�Ϊ��
    bool direction_up;                      // ���ݷ�����Ϊ���ϣ�������
    bool between_floors;                    // �Ƿ������������½����̣�¥�䣩
    bool waiting_pas;                       // �Ƿ����ڵȴ��˿����µ���
    bool initial;
    size_t count;                           // ����  Ĭ��Ϊ0
    size_t wait_time;                       // ����¥���Ⱥ�˿����µ���ʱʹ��   ��ʼ��Ϊ0
    size_t cur_floor;                       // Ŀǰͣ��¥��
    size_t dest_floor;                      // ��һ��ͣ���㣨����û�˶�ȥ����ʱ��״̬��

    size_t new_pas_num;                     // �ò��������ĳ˿���  ��ʼ��0
    size_t lev_pas_num;                     // �ò���ȥ�ĳ˿���  ��ʼ��0

    vector<Passenger*> pasgr;               // �˿�vec��Ĭ�ϳ�ʼ��Ϊ��   ��ָ�룬ʹ���淽���޸�ԭֵ
    //selected_floor�����Ż���set���Ӷ�����ÿ�αȽϵ�ʱ��
    vector<size_t> selectedfloor;           // ����Ϊ��ʱҪȥ�ӵĳ˿͵�¥�㣬Ĭ�ϳ�ʼ��Ϊ��

    //���ߺ���
    void refresh();                         // ���ڶ�̬���µ����еĳ˿͵ĵ�ǰ¥��
};
size_t Elevator::ele_code = 0;              // ���Ϊ0-9



class Passenger{
    friend class Elevator;
    size_t friend choose_elevator(Passenger&, vector<Elevator>&);   // �˿�ѡ����ݣ����ص��ݱ��
    static size_t pas_code;
public:
    Passenger();
    void run(size_t, vector<Elevator>&);                            // ÿ���ж�״̬

public:
    // static vector<Passenger> wait_list;          // ���ڵȵ��ݵĳ˿�����
    static size_t pas_remained;                     // ʣ��δ����Ŀ�ĵس˿���
    bool finished() const;                          // �ж��Ƿ񵽴�Ŀ�ĵ�¥��
    bool pressup() const { return dest_floor > cur_floor; }     // �Ƿ������ϼ�
    // bool onboard() const { return on_ele; }                  //�Ƿ��ڵ�����
    const size_t &getcode() const { return code; }
    const size_t &getdest() const { return dest_floor; }
    const size_t &get_ele_num() const { return ele_code; }
    const size_t &get_wait_time() const { return wait_time; }

private:
    bool arrived;                                   // ��ʼʱ�Ƿ��Ѿ�����1��                        
    size_t code;                                    // �˿ͱ��
    size_t dest_floor;                              // Ŀ��¥�㣨�����ɸ��ģ�
    size_t cur_floor;                               // Ŀǰ¥�㣨������ݣ�   
    size_t wait_time;                               // �˿͵ȴ�����ʱ�䣨������һ�Σ�
    size_t ele_code;                                // �������ĵ��ݵı��
    bool on_ele;                                    // �Ƿ��ڵ�����
    bool finishd;                                   // �˿ͽ�������
    
    // ���ߺ���
    // size_t cal_wait_time(const Elevator &);      // ����ȴ�ʱ��
};
size_t Passenger::pas_remained = N;
size_t Passenger::pas_code = 1;
// vector<Passenger> Passenger::wait_list;



vector<Passenger> pas_wait_list;                    // ���ڵȴ�������(ֱ��ֵ��������)




void push_wait_list(Passenger &p){
    pas_wait_list.push_back(p);
}

void pop_wait_list(const Passenger &p){
    auto it = std::find_if(pas_wait_list.begin(), pas_wait_list.end(),[&p](const Passenger &pas){ return pas.getcode() == p.getcode();});
    if(it != pas_wait_list.end())
        pas_wait_list.erase(it);
}



//�������ϵ���ʱ����������Ҫȥ��¥����ѡ�������һ��ͣ����¥��
size_t choosefloor(const vector<size_t> &vec, bool is_up){
    if(is_up)
        return *std::min_element(vec.begin(), vec.end());
    else
        return *std::max_element(vec.begin(), vec.end());
}


//�˿���������ʹ��
void Elevator::push_pasgr(Passenger& p){
    pasgr.push_back(&p);
    isempty = false;
    //�����ĳ˿�һ����˳�ŵ��ݷ���ģ���Ҫ�Ƚ� Ҫȥ��¥�����ѡ�е�¥��Ĵ�С
    // selectedfloor.push_back(p.dest_floor);
    //���Ŀǰ����ֻ��1�ˣ���ô�������з�����Ǹó˿�Ҫȥ�ķ���
    if(pasgr.size() == 1)
        direction_up = p.pressup();    
    //�ڵ��ݵ����г˿���ѡ����һ��ͣ����¥��         
    // dest_floor = choosefloor(selectedfloor, direction_up);
    //�����˿���+1
    ++new_pas_num;          
}
//ע���޸ĵ�����Ϣempty���ж��Ƿ��޸ķ���ѡ�У���һ��ͣ����


//���������ʹ�ã�������ȥ��������ÿ��runʱʹ�ü���
void Elevator::pop_pasgr(){
    static size_t count = 0;                        //��ȥ�˿͵�����
    count = 0;
    auto it = std::find_if(pasgr.begin(),pasgr.end(),[this](Passenger *p){return cur_floor == p->dest_floor;});
    while(it != pasgr.end()){
        ++count;
        (*it)->on_ele = false;

//*****************************************************
        (*it)->finishd = true;                 //�˿͵�������Ŀ��¥�㣬��������   ����Ҫ���и���
//*****************************************************

        if(!(*it)->finished())                 //������滹û�������ټӻ�wait_list 
            pas_wait_list.push_back(*(*it));
        else
            --Passenger::pas_remained;         //��������յ㣬ʣ��ĳ˿���-1
        pasgr.erase(it);
        it = std::find_if(pasgr.begin(),pasgr.end(),[this](Passenger *p){return cur_floor == p->dest_floor;});
    }

    // if(count > 0){                              //��ѡ���destfloor��ɾ���ò�
    //     for (int i = 0; i < count; ++i){
    //         auto iter = find_if(selectedfloor.begin(), selectedfloor.end(), [this](const size_t &a) { return a == this->cur_floor; });
    //         selectedfloor.erase(iter);
    //     }
    // }
        
    lev_pas_num = count;                        //��¼ �µ��ݵĳ˿���
}
//ע���޸�isempty������


void Elevator::refresh(){
    for(auto &p : pasgr){
        p->cur_floor = cur_floor;
    }
}


//*****************************************************

//����new_pas_num �� lev_pas_num
//������һʱ�̵��ݵ�״̬

void Elevator::run(size_t cur_time){
    // ��߲�������static count = 0         �����⣡��

    if(pasgr.size() != 0)
        initial = false;
    if(initial)                             //���ݴ��ڳ�ʼ״̬��ֱ�ӷ���
        return;

    if(!pasgr.size())
        check(pas_wait_list);               //����ʱ���Ƿ�������Ҫ��������
    if(!isselected)                         //û���򷵻�
        return;

    //�ж��Ƿ�Ϊ�ȴ�����
    if(waiting_pas){
        // cout << code << " wp" << endl;
        pop_pasgr();                            //���ó˿���ȥ���õ���ȥ�������������������ɳ˿����ṩ
        wait_time += (new_pas_num + lev_pas_num) * T;   //���õȴ�ʱ��

        //�м��״̬        
        if(new_pas_num + lev_pas_num == 0 && wait_time == 0){     //�����һʱ�̼Ȳ������˿�Ҳ����ȥ�˿��Ҳ���Ҫ�ٵȴ�  ֱ������һ����
            waiting_pas = false;
            between_floors = true;
            count = 0;
            goto FLAG;                          //�������������½�ѭ��
        }

        //�ȴ���״̬
        if(count >= wait_time){                 //�ȴ���ɣ�ִ����һ��
            count = 0;
            wait_time = 0;
            new_pas_num = 0;                    //���״̬
            lev_pas_num = 0;                    //���״̬
            waiting_pas = false;
            between_floors = true;
            //�жϴ�ʱ�������Ƿ�����
            check(pas_wait_list);
            return;
        }
        ++count;                                //ÿһ��count + 1
        new_pas_num = 0;
        lev_pas_num = 0;
        return;
    }
    //�ж��Ƿ�Ϊ�������½�����
    else if(between_floors){
    FLAG :
        // cout << code << " bf" << endl;
        wait_time = S;                                  //������һ���ʱ��
        if(count >= wait_time){                         //��߸ĳ�==�������⣿     Ϊɶ
            if(direction_up){
                ++cur_floor;
                refresh();
            }
            else{
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
//Ŀǰȱ�ݣ�����������ͬʱ���˷�������ʱ������ȥ���һ��������ܲ������߼�
void Elevator::check(const vector<Passenger> &wait_list){
    // �ж��Ƿ��г˿�
    if(pasgr.size() == 0){
        //����wait_list���Ƿ��г˿���Ҫ�Լ�����
        for(const auto &p : wait_list){
            if(p.ele_code == code){
                //����δ��ӹ��������
                auto it = std::find_if(selectedfloor.begin(),selectedfloor.end(),[&p](const size_t &a){return a == p.cur_floor;});
                if(it == selectedfloor.end()){
                    selectedfloor.push_back(p.cur_floor);
                    direction_up = (cur_floor > p.cur_floor) ? false : true;
                }
            }
        }
        if(selectedfloor.size() == 0){
            isselected = false;
            waiting_pas = true;
            between_floors = false;
        }
        else{
            isselected = true;
            waiting_pas = false;
            between_floors = true;
        }
    }
}
//*****************************************************



//��ʼ���˿Ͷ���
Passenger::Passenger() : arrived(false), code(pas_code++), cur_floor(1), on_ele(false), finishd(false) {
    wait_time = rand() % M;                     //����0-M�ĵ���ʱ��
    dest_floor = rand() % 39 + 2;               //����2-40�����Ŀ��¥��
    ele_code = rand() % 10;                     //���ѡ��һ������        ��һ��   choose_elevator����ʹ��
    push_wait_list(*this);                      //����Ⱥ�����
}       


void Passenger::run(size_t cur_time, vector<Elevator>& ele_vec){
    //�Ѿ�����Ŀ�ĵأ��򷵻�
    if(finishd)
        return;
    if(cur_time >= wait_time)
        arrived = true;
    //����ڵ����ϻ���δ���ֳ������أ�ǰ�߽��������ദ��
    if(on_ele || !arrived)
        return;                                 
    //ѡ��ĵ��ݲ���ͬһ��¥���ȴ�
    if(ele_vec[ele_code].get_floor() != cur_floor)
        return;
    //����������¥��䣬�ȴ�
    if(ele_vec[ele_code].between_floors == true)
        return;
    //���ϵ��ݵ��³��أ��ȴ�
    if(ele_vec[ele_code].get_pasgr().size() + 1 > MAXPEOPLE)  
        return; 
    //���������Լ���Ҫȥ�ķ���ͬ�ҵ��������ˣ��ȴ���û��˵����ר�����ӵģ�������ܻ᲻ͬ���������ϵ��ݣ�
    if(ele_vec[ele_code].dir_up() != pressup() && ele_vec[ele_code].pasgr.size()!=0)   
        return;
    ele_vec[ele_code].push_pasgr(*this);        //��Ȼ�Ͱ��Լ����뵽��������
    on_ele = true;
    pop_wait_list(*this);                       //�ӵȺ�����ɾ��
    //�����selectedfloor�б��ϣ�����ɾ��
    if(ele_vec[ele_code].pasgr.size() == 1){
        auto it = std::find_if(ele_vec[ele_code].selectedfloor.begin(),ele_vec[ele_code].selectedfloor.end(),[this](const size_t &a){return a == cur_floor;});
        if(it != ele_vec[ele_code].selectedfloor.end())
            ele_vec[ele_code].selectedfloor.erase(it);
    }
}

// ************************************************************     ����Ҫ��
bool Passenger::finished() const{                   
    return finishd;
}
// ************************************************************


size_t choose_elevator(Passenger& pasgr, vector<Elevator> &vec){
    pasgr.ele_code = rand() % 10;       // �˿ͳ����ĵ��ݺ���
    return 0;
    //�ж���û�е��ݿ�������
    // bool has_ele = false;           //�Ƿ��пյĵ���
    // for(const auto &e : vec){
    //     if(e.empty())
    //         has_ele = true;
    //     else if()
    // }
    // for(auto &e : vec){
    //     if(e.empty() && !e.isselected){
    //         has_ele = true;
    //         e.isselected = true;
    //         pasgr.wait_time = (e.cur_floor - pasgr.cur_floor)*;
    //         pasgr.ele_code = e.code;
    //         e.push_pasgr(pasgr);
    //         e.dest_floor = pasgr.dest_floor;
    //     }
    // }
    // if(!has_ele){
    //     pasgr.ele_code;             //ѡ����ݱ��      ��ûд
    //     pasgr.wait_time = pasgr.cal_wait_time(vec[pasgr.ele_code]);      //����ȴ�ʱ��
    //     Passenger::wait_list.push_back(pasgr);                           //����ȴ�����
    // }
}


int main(){
    srand((unsigned)time(NULL));                //�������������

    vector<Elevator> ele_vec(10);               //��ʼ��10������
    vector<Passenger> pasgr_vec(N);             //��ʼ��N���˿�
    // for(auto &p : pasgr_vec)
        // choose_elevator(p, ele_vec);            //ѡ��ÿ���˿���Ҫ�����ĵ���
    cout << "Simulation starts, passengers' information are as follows:" << endl << endl;
    for(const auto &p : pasgr_vec)
        cout << p.getcode() << "--" << p.getdest() <<" arrives at "<<p.get_wait_time()<< " , selects elevator " << p.get_ele_num() << endl;
    cout << endl;
    for(const auto & e : ele_vec){
        cout << "Elevator " << e.get_code() << " (cur_floor: " << e.get_floor() << ") Passengers:\t";
        for(const auto & p : e.get_pasgr())
            cout << p->getcode() << "--" << p->getdest() << " ;\t";
        cout << endl;
    }
    system("pause");                            //�����Լ���

    size_t timer = 0;                           //��ʱ��
    while(Passenger::pas_remained != 0){        //����ʱ��ѭ������û�г˿���Ҫ������ʱ��������
        system("cls");
        for(auto &p : pasgr_vec)
            p.run(timer, ele_vec);
        for(auto &e : ele_vec)
            e.run(timer);



        for(const auto & e : ele_vec){
            cout << "Elevator " << e.get_code() << (e.dir_up() ? " �� " : " �� ") << "\t"
                 << "(cur_floor:" << e.get_floor() << ")"
                 << "\twait_time: " << e.get_waittime() << "\t Passengers: \t";
            for(const auto & p : e.get_pasgr())
                cout << p->getcode() << "--" << p->getdest() << ";\t";
            cout << endl;
            //�����ô���
            // cout << "\tisselected:" << (e.selected() ? " true " : " false ") << "\twaiting_pas:" << (e.wp() ? " true " : " false ") << "\tbetween_floor:" << (e.bf() ? " true " : " false ") << endl;
            // cout << " waiting_time "<<e.get_waittime() << endl;
        }
        cout << endl;
        cout << "Remained Passengers' List:" << endl;
        if(pas_wait_list.size() == 0)
            cout << "None!" << endl << endl;
        else{
            for(const auto &p : pas_wait_list)
                cout << p.getcode() << "--" << p.getdest() << "\tarrives at " << p.get_wait_time() << "\tselects elevator " << p.get_ele_num() << endl;
            cout << endl;
        }
        cout << "Number of Remained Passengers: " << Passenger::pas_remained << endl;
        cout << endl;
        cout << "current time: " << timer << endl;
        cout << endl;
        system("pause");
        // Sleep(1000/play_speed);                            //���������޸ģ����Ĳ����ٶ�
        ++timer;
    }

    cout << "Finished! :D" << endl;
    return 0;
}