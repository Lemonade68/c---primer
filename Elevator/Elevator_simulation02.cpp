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
#define M 5                 // �����ʱ��γ���
#define S 3                 // ��������ʱS��ÿ��
#define T 2                 // ÿ���˿����µ��ݵ�ʱ��
#define play_speed 2        // ���ٲ��ţ�*n��
#define MAX_Times 3         // �����Ĵ��������������    5����ʾʱ��̵�

// enum elevator_status{halt,waiting,runing};

using std::cout;
using std::endl;
using std::vector;


class Passenger;

class Elevator{
    friend size_t choose_elevator(Passenger &, vector<Elevator> &);     // �˿�ѡ����ݣ����ص��ݱ�ţ������õȴ�ʱ��
    friend class Passenger;
    static size_t elevator_code;

public:
    Elevator() : isselected(true), code(elevator_code++), first_dir_up(true), set(true), isempty(true), direction_up(true), between_floors(false), waiting_pas(true), cur_floor(1),initial(true),wait_time(0) { }
    void run(size_t);                                                   //ÿһ������ж�״̬

public:
    bool overweighing() const
        { return pasgr.size() > MAXPEOPLE ? true : false; }             //�Ƿ���
    bool empty() const{ return isempty; }
    bool dir_up() const{ return direction_up; }
    //������   
    bool selected() const { return isselected; }
    bool wp() const { return waiting_pas; }
    const size_t &get_count() const { return count; }
    bool getset() const { return set; }
    const size_t &get_fpc() const { return first_pas_code; }

    const size_t &get_waittime() const { return wait_time; }
    const size_t& get_floor() const { return cur_floor; }
    const size_t& get_code() const{ return code; }
    size_t get_seltd_floor_num() const { return selectedfloor.size(); }
    bool get_bf() const { return between_floors; }
    const vector<Passenger*> &get_pasgr() const { return pasgr; }
    void push_pasgr(Passenger&, vector<Elevator>&);                     // ��ӳ˿ͣ�����new_pas_num                               
    void pop_pasgr();                                                   // ɾ���˿ͣ�����lev_pas_num
    void check (const vector<Passenger*>&);                             // �������û�г˿ͣ��ж��Ƿ��г˿���Ҫ�Լ�ȥ��

private:
    size_t code;                            // ���ݱ��
    bool isselected;                        // �����Ƿ��ѱ�ѡ��
    bool isempty;                           // �����Ƿ�Ϊ��
    bool direction_up;                      // ���ݷ�����Ϊ���ϣ�������
    bool between_floors;                    // �Ƿ������������½����̣�¥�䣩
    bool waiting_pas;                       // �Ƿ����ڵȴ��˿����µ���
    bool initial;                           // �Ƿ�Ϊ��ʼ״̬����δ�Ӵ��˿ͣ�
    
    //��2���¼�
    bool first_dir_up;                      // ��һ�����°�ť���˵ĳ�������
    bool set;                               // �ж��Ƿ��ǵ�һ�����°�ť���ˣ���ʼΪtrue������Ϊfalse
    size_t first_pas_code;                  // ��¼��һ�����°�ť�ĳ˿͵ı�ţ���ʼ��Ϊ0

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
    void reverse_dir();
};
size_t Elevator::elevator_code = 0;         // ���Ϊ0-9  �������ʱҪд��cpp�ļ��У�����д��.h�ļ���



class Passenger{
    friend class Elevator;
    friend size_t choose_elevator(Passenger&, vector<Elevator>&);   // �˿�ѡ����ݣ����ص��ݱ��
    static size_t pas_code;
public:
    Passenger();
    void run(size_t, vector<Elevator>&);                            // ÿ���ж�״̬

public:
    // static vector<Passenger> wait_list;                          // ���ڵȵ��ݵĳ˿�����
    static size_t pas_remained;                                     // ʣ��δ����Ŀ�ĵس˿���
    bool finished() const { return finishd; };                      // �ж��Ƿ񵽴�Ŀ�ĵ�¥��
    bool pressup() const { return dest_floor > cur_floor; }         // �Ƿ������ϼ�
    // bool onboard() const { return on_ele; }                      //�Ƿ��ڵ�����
    const size_t &getcode() const { return code; }
    const size_t &getdest() const { return dest_floor; }
    const size_t &getcur() const { return cur_floor; }
    const size_t &get_ele_num() const { return ele_code; }
    const size_t &get_arrive_time() const { return arrive_time; }
    const size_t &get_wait_time() const { return wait_time; }
    const size_t &get_L() const { return L; }
    const size_t &get_took_time() const { return took_time; }
    const size_t &get_counter() const { return counter; }


private:
    bool arrived;                                   // ��ʼʱ�Ƿ��Ѿ�����1��                        
    bool on_ele;                                    // �Ƿ��ڵ�����
    bool finishd;                                   // �˿ͽ�������
    size_t code;                                    // �˿ͱ��
    size_t dest_floor;                              // Ŀ��¥�㣨�����ɸ���   ע�ⲻ���������ǰ��¥�㣩  
    size_t cur_floor;                               // Ŀǰ¥�㣨������ݣ�   
    size_t arrive_time;                             // �˿͵ȴ�����ʱ�䣨������һ�Σ�
    size_t ele_code;                                // �������ĵ��ݵı��
    
    //�ڶ����ϻ����
    size_t L;                                       // Ҫ�����ĵ��ݵĴ���
    size_t took_time;                               // �������ĵ��ݵĴ�������ʼ��Ϊ0
    size_t wait_time;                               // ��¥���ϵȴ���ʱ��
    size_t counter;                                 // �ȴ�ʱ�ļ���������ʼ��Ϊ0

    // ���ߺ���
    // size_t cal_wait_time(const Elevator &);      // ����ȴ�ʱ��
};
size_t Passenger::pas_remained = N;
size_t Passenger::pas_code = 1;
// vector<Passenger> Passenger::wait_list;


vector<Passenger*> pas_wait_list;                    // ���ڵȴ�������


void push_wait_list(Passenger *p){
    pas_wait_list.push_back(p);
}

void pop_wait_list(Passenger *p){
    auto it = std::find_if(pas_wait_list.begin(), pas_wait_list.end(),[&p](Passenger *pas){ return pas->getcode() == p->getcode();});
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
void Elevator::push_pasgr(Passenger& p, vector<Elevator> &ele_vec){
    pasgr.push_back(&p);
    isempty = false;
    //�����ĳ˿�һ����˳�ŵ��ݷ���ģ���Ҫ�Ƚ� Ҫȥ��¥�����ѡ�е�¥��Ĵ�С
    // selectedfloor.push_back(p.dest_floor);
    //���Ŀǰ����ֻ��1�ˣ���ô�������з�����Ǹó˿�Ҫȥ�ķ���
    
    // if(selectedfloor.size() == 0)            //��������
    
    //�����selectedfloor�б��ϣ���selectedfloor�Ͻ���ɾ��
    auto it = std::find_if(ele_vec[p.ele_code].selectedfloor.begin(),ele_vec[p.ele_code].selectedfloor.end(),[&p](const size_t &a){return a == p.cur_floor;});
    if(it != ele_vec[p.ele_code].selectedfloor.end())
        ele_vec[p.ele_code].selectedfloor.erase(it);

    if(p.code == first_pas_code){               //����Ǹõ��ݿճ˿�ʱ��һ�����°�ť�ĳ˿�
        set = true;                             //����
        // first_pas_code = 0;                     //����
    }
    if(pasgr.size() == 1){                      
        direction_up = p.pressup();
        first_dir_up = p.pressup();
    }
    //�ڵ��ݵ����г˿���ѡ����һ��ͣ����¥��         
    // dest_floor = choosefloor(selectedfloor, direction_up);
    //�����˿���+1
    ++new_pas_num;          
}
//ע���޸ĵ�����Ϣempty���ж��Ƿ��޸ķ���ѡ�У���һ��ͣ����


//���������ʹ�ã�������ȥ�������������øó˿���һ�ε����ݣ�ÿ��runʱʹ�ü���
void Elevator::pop_pasgr(){
    static size_t count = 0;                    //��ȥ�˿͵�����
    count = 0;
    auto it = std::find_if(pasgr.begin(),pasgr.end(),[this](Passenger *p){return cur_floor == p->dest_floor;});
    while(it != pasgr.end()){
        ++count;

        //���� *�´ε�* ״̬
        (*it)->took_time++;                                     //���ǵڼ���
        (*it)->on_ele = false;

        // (*it)->wait_time = rand() % 111 + 10;                   //����´ε�����ȴ�ʱ��
        (*it)->wait_time = rand() % 11 + 10;                    //����´ε�����ȴ�ʱ�䣨�Ȱ�10-20�㣩
        (*it)->counter = 0;                                     //����������
        if((*it)->took_time < (*it)->L){                        //����С��L�Σ���������´ε�dest_floor��������L�Σ�
            (*it)->dest_floor = rand() % 39 + 2;
            while((*it)->cur_floor == (*it)->dest_floor)        //����������㣬�������
                (*it)->dest_floor = rand() % 39 + 2;
        }
        else if((*it)->took_time == (*it)->L){                  //��L���µ��ݣ�����L+1�ε�״̬
            (*it)->dest_floor = 1;
        }
        else{                                                   //��L+1���µ���
            (*it)->wait_time = 0;                               //״̬��0
            (*it)->finishd = true;                              //�˿͵���1�㣬��������
        }

        if(!(*it)->finished())                                  //������滹û�������ټӻ�wait_list 
            pas_wait_list.push_back(*it);
        else if((*it)->cur_floor == (*it)->dest_floor)          //���isfinished�����Ѿ�����Ŀ��¥�㣨1�㣩
            --Passenger::pas_remained;                          //ʣ��ĳ˿���-1
        
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

//��bug�õ�
void Elevator::reverse_dir(){
    if(direction_up == true)
        direction_up = false;
    else
        direction_up = true;
}


//����new_pas_num �� lev_pas_num
//������һʱ�̵��ݵ�״̬

void Elevator::run(size_t cur_time){
    // ��߲�������static count = 0         �����⣡��     //������Ķ����ڵ��øú���ʱ�����������

    if(pasgr.size() != 0)
        initial = false;
    if(initial)                                         //���ݴ��ڳ�ʼ״̬��ֱ�ӷ���
        return;

    check(pas_wait_list);                               //����ʱ���Ƿ�������Ҫ��������
    if(!isselected){                                    //û���򷵻�
        waiting_pas = true;
        between_floors = false;
        return;
    }

    //�ж��Ƿ�Ϊ�ȴ�����
    if(waiting_pas){
        // cout << code << " wp" << endl;
        pop_pasgr();                                                //���ó˿���ȥ���õ���ȥ�������������������ɳ˿����ṩ
        wait_time += (new_pas_num + lev_pas_num) * T;               //���õȴ�ʱ��

        //�м��״̬        
        if(new_pas_num + lev_pas_num == 0 && wait_time == 0){       //�����һʱ�̼Ȳ������˿�Ҳ����ȥ�˿��Ҳ���Ҫ�ٵȴ�  ֱ������һ����
            waiting_pas = false;
            between_floors = true;
            count = 0;
            goto FLAG;                          //�������������½�ѭ��
        }

        //�ȴ���״̬
        if(count >= wait_time){                 //�ȴ���ɣ�ִ����һ��
            count = 0;
            new_pas_num = 0;                    //���״̬
            lev_pas_num = 0;                    //���״̬
            waiting_pas = false;
            between_floors = true;
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
void Elevator::check(const vector<Passenger*> &wait_list){
    // �ж��Ƿ��г˿�
    static bool sign;                                                                    //�Լ��Ƿ���ó˿�ͬ¥��
    sign = false;
    if(pasgr.size() == 0){
        //����wait_list���Ƿ��г˿���Ҫ�Լ����ӣ����ȳ���һ�����°�ť�ĳ˿ͣ�ʹ��push_back���������wait_list�ں��棩
        for(const auto &p : wait_list){
            if(p->counter >= p->wait_time && p->ele_code == code){                              //�˿�ѡ�е����ҳ˿��Ѿ��ȴ���ϣ���ʱ���°�ť�����ҵ�һ������ť�ĳ˿�
                if(cur_floor == p->cur_floor){
                    wait_time = 2;                                                              //�������㣺���ݵȴ�����ֹ������һ���ٷ���
                    if(set){
                        sign = true;
                        first_pas_code = p->code;                                               //��¼�ó˿͵ı��
                        direction_up = p->pressup();
                        first_dir_up = p->pressup();                                            //���øó˿ͽ�Ҫȥ�ķ���
                    }
                }
                else{
                    if(set){
                        first_pas_code = p->code;
                        direction_up = (cur_floor > p->cur_floor) ? false : true;               //���÷���
                        first_dir_up = p->pressup();
                    }
                }
                //����δ��ӹ��������
                auto it = std::find_if(selectedfloor.begin(),selectedfloor.end(),[&p](const size_t &a){return a == p->cur_floor;});
                if(it == selectedfloor.end())
                    selectedfloor.push_back(p->cur_floor);
                set = false;
            }
        }
        if(selectedfloor.size() == 0){
            set = true;                                 //���һֱû��ѡ��,set���ϻ�ԭΪtrue�����ֻ�ڳ˿���ӵĻ�������˿�ǰsetΪfalse���Ӳ���ȥ����ֻ�н�ȥ�˲��ܱ��true
            isselected = false;
            count = 0;
            wait_time = 0;
            waiting_pas = true;
            between_floors = false;
        }
        else{
            if(sign){
                isselected = true;
                waiting_pas = true;
                between_floors = false;
            }else{
                isselected = true;
                waiting_pas = false;
                between_floors = true;                 //���ó�false : �Ա��ڵ�ǰ��ĳ˿Ϳ���ֱ�����������run�еĸ���waiting_pas״̬ʹ�ã� 
            }
        }
    }
}
//*****************************************************

//��ʼ���˿Ͷ���
Passenger::Passenger() : arrived(false), code(pas_code++), cur_floor(1), on_ele(false), finishd(false) {
    arrive_time = rand() % M;                       //����0-M�ĵ���ʱ��
    dest_floor = rand() % 39 + 2;                   //����2-40�����Ŀ��¥��
    ele_code = rand() % 10;                         //���ѡ��һ������        ��һ��   choose_elevator����ʹ��
    L = rand() % MAX_Times + 1;                     //�������Ҫ�����Ĵ���     10̫�࣬����3������
    push_wait_list(this);                           //����Ⱥ�����
}       


void Passenger::run(size_t cur_time, vector<Elevator>& ele_vec){
    //�Ѿ�����Ŀ�ĵأ��򷵻�
    if(finishd)
        return;
    if(cur_time >= arrive_time)
        arrived = true;
    
    //����ڵ����ϻ���δ���ֳ������أ�ǰ�߽��������ദ��
    if(on_ele || !arrived)
        return;                                 
    
    if(counter < wait_time){                            //����ȴ�ʱ�䣬���֮���°�ť
        ++counter;
        return;
    }
    
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
    if(ele_vec[ele_code].dir_up() != pressup() && ele_vec[ele_code].pasgr.size() != 0)   
        return;
    //�������ͬ�ҵ������ˣ����Լ����ǵ���Ҫ�ӵĵ�һ���˿ͣ�����
    if(ele_vec[ele_code].dir_up() != pressup() && ele_vec[ele_code].pasgr.size() == 0 && ele_vec[ele_code].first_pas_code != code)
        return;
    //������ݾ����Լ��Һ��Լ�������ͬ�������ڽӵ�һ���˿ͺ�Ҫȥ�ķ�����Լ��෴�����Ȳ��ϵ���
    if (ele_vec[ele_code].first_dir_up != pressup())
        return;

    counter = 0;                                        //counter����
    wait_time = 0;                                      //wait_time����
    pop_wait_list(this);                                //�ӵȺ�����ɾ��


    ele_vec[ele_code].push_pasgr(*this, ele_vec);       //���Լ����뵽��������
    on_ele = true;
}


size_t choose_elevator(Passenger& pasgr, vector<Elevator> &vec){
    pasgr.ele_code = rand() % 10;                       // �˿ͳ����ĵ��ݺ���
    return 0;
    //�ж���û�е��ݿ�������
    // bool has_ele = false;                            //�Ƿ��пյĵ���
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
    srand((unsigned)time(NULL));                    //�������������

    vector<Elevator> ele_vec(10);                   //��ʼ��10������
    vector<Passenger> pasgr_vec(N);                 //��ʼ��N���˿�
    // for(auto &p : pasgr_vec)
        // choose_elevator(p, ele_vec);             //ѡ��ÿ���˿���Ҫ�����ĵ���
    cout << "Simulation starts, passengers' information are as follows:" << endl << endl;
    for(const auto &p : pasgr_vec)
        cout << p.getcode() << "--" << p.getdest() <<" arrives at "<<p.get_arrive_time()<< " , selects elevator " << p.get_ele_num() << endl;
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
            if(!p.finished())                   //�����û�������������иó˿�
                p.run(timer, ele_vec);
        for(auto &e : ele_vec)
            e.run(timer);



        for(const auto & e : ele_vec){
            //����ʱ��ʾ״̬��
            // cout << "Elevator " << e.get_code() << " has "<<e.get_seltd_floor_num()<<" passengers to take "<< ((e.get_pasgr().size() == 0 && e.get_seltd_floor_num() == 0) ? " - " : (e.dir_up() ? " �� " : " �� ")) << "\t"
                //  << "(cur_floor:" << e.get_floor() << ")" << "\t direction_up:"<<(e.dir_up()?" true ":" false ")
            cout << "Elevator " << e.get_code() << ((e.get_pasgr().size() == 0 && e.get_seltd_floor_num() == 0) ? " - " : (e.dir_up() ? " �� " : " �� ")) << "\t"
                 << "(cur_floor:" << e.get_floor() << ")" << "\tfirst_pas_code: " << e.get_fpc() 
                 << "\twait_time: " << e.get_waittime() << "\t Passengers: \t";
            for(const auto & p : e.get_pasgr())
                cout << p->getcode() << "--" << p->getdest() << ";\t";
            cout << endl;
            //�����ô���
            cout << "isselected:" << (e.selected() ? " true" : " false") << "\twaiting_pas:" << (e.wp() ? " true" : " false") << "\tbetween_floor:" << (e.get_bf() ? " true" : " false") <<"\tset: "<<(e.getset() ? " true" : " false") << endl;
            cout << endl;
        }
        cout << endl;
        cout << "Remained Passengers' List:" << endl;
        if(pas_wait_list.size() == 0)
            cout << "None!" << endl << endl;
        else{
            for(const auto &p : pas_wait_list)
                cout << p->getcode() << "\tarrives at " << p->get_arrive_time() << "\tselects elevator " << p->get_ele_num()
                     << "\tcurrent_floor: " << p->getcur() << "\tdest_floor: " << p->getdest() << "\t  wait_time: " << p->get_wait_time() << "\t  Total_took_time_L: " << p->get_L() << "\ttook_time: " << p->get_took_time()
                     << "\tis_ready:" << ((p->get_counter() >= p->get_wait_time()) ? " Yes " : " No ") << endl;
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