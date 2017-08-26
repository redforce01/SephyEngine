#pragma once

#include "World_Island_Data.h"
#include "world_Event_Log.h"


namespace world_userNS
{
	const int MAX_BUILD = 12;
	const int KIND_RESOURCE = 4;

	const int EVENT_LIST = 7;
	const int EVENT_RESOURCE_LIST = 3;
	const int RESOURCE_AMOUNT = 300;
	const int RAND_RANGE = 10000;
	const int DBUF_TURN = 3;
	const int BUF_TURN = 5;

	const float PROBABILITY = 0.2f;

	const std::string EVENT_RESOURCE	= "광맥 발견! 자원 증가";
	const std::string EVENT_TURN		= "남은 턴 : ";
	const std::string EVENT_ZERO		= "저품질 철 생산";
	const std::string EVENT_ZERO_1		= "철 보유량에서 -20% 감소";
	const std::string EVENT_ZERO_2		= "철 생산 량 - 10% 감소";
	const std::string EVENT_ONE			= "경제 대 공황";
	const std::string EVENT_ONE_1		= "돈 보유량에서 -20% 감소";
	const std::string EVENT_ONE_2		= "돈 생산 량 - 10% 감소";
	const std::string EVENT_TWO			= "제철소 호황";
	const std::string EVENT_TWO_1		= "유닛 생산 속도 - 1턴 감소";
	const std::string EVENT_THREE		= "경제 호황";
	const std::string EVENT_THREE_1		= "돈 생산량 + 10% 증가";
	const std::string EVENT_FOUR		= "넘치는 연료";
	const std::string EVENT_FOUR_1		= "함선 유지 비용 - 10% 감소";
	const std::string EVENT_FIVE		= "넘치는 철";
	const std::string EVENT_FIVE_1		= "건물 건설 비용 -10% 감소";
	const std::string EVENT_SIX			= "생산 과부화";
	const std::string EVENT_SIX_1		= "배 1대 생성";
}

class CWorld_MainSystem;
class CWorld_User
{
protected:
	CWorld_MainSystem* scene;
	CWorld_Island_Data* island_data;

protected:
	Graphics* m_pGraphics;
	Input* m_pInput;

	CWorld_Event_Log* event_log;

	std::vector<CWorld_Island*> island_node;	//현재 보유 섬

	std::vector<CProduction_Ship*> current_ship;	//현재 선택 배(이동할 배)
	
	RECT rt_rand;
	
	int current_building[world_userNS::MAX_BUILD];

	int money;
	int iron;
	int fuel;
	int research;

	int rand_ship_count;

	int buf_type;
	int buf_turn;

	int increase_resource[world_userNS::KIND_RESOURCE];
	int decrease_resource[world_userNS::KIND_RESOURCE];

	bool is_update;

	void active_event();
	void random_create_ship();
	void world_event();

public:
	void SetLoadLinkData(CWorld_Island_Data* _data) { island_data = _data; }
	void SetLoadLinkScene(CWorld_MainSystem* _scene) { scene = _scene; }

	CWorld_User();
	~CWorld_User();

	virtual void initialize(Graphics* g, Input* i, int _money, int _iron, int _fuel, int _research);
	void release();

	void add_island(CWorld_Island* _island) { island_node.emplace_back(_island); }
	void add_ship(CProduction_Ship* _ship, CWorld_Island* _island);
	void add_cur_ship(CProduction_Ship* _ship) { current_ship.emplace_back(_ship); }
	void add_cur_building(int _index) { current_building[_index]++; }
	void destroy_cur_building(int _index) { current_building[_index]--; }
	void add_resource(E_RESOURCE _type, int _resource);
	void add_increase_resource(E_RESOURCE _type, int _amount) { increase_resource[_type] += _amount; }
	void add_decrease_resource(E_RESOURCE _type, int _amount) { decrease_resource[_type] += _amount; }
	void remove_cur_ship(int _index) { current_ship.erase(current_ship.begin() + _index); }
	void clear_cur_ship() { current_ship.clear(); }
	void set_is_update(bool _is) { is_update = _is; }
	void remove_island(int _index);
	void print_world_log(const std::string message);
	void turn_event();

	std::deque<std::string> get_log_message();
	std::vector<CWorld_Island*> get_island() { return island_node; }
	std::vector<CProduction_Ship*> get_cur_ship() { return current_ship; }

	CWorld_Island_Data* get_data() { return island_data; }
	CWorld_MainSystem* get_scene() { return scene; }

	int get_buf_type() { return buf_type; }
	int get_cur_building(int _index) { return current_building[_index]; }
	int get_resource(E_RESOURCE _type);
	int get_increase_resource(E_RESOURCE _type) { return increase_resource[_type]; }
	int get_decrease_resource(E_RESOURCE _type) { return decrease_resource[_type]; }

	bool is_rand_ship();
	bool spend_resource(E_RESOURCE _type, int _amount);
};
