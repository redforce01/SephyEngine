#ifndef _BATTLE_RESULT_SYSTEM_H
#define _BATTLE_RESULT_SYSTEM_H
#define WIN32_LEAN_AND_MEAN

namespace battleResultSystemNS
{
	const std::string DATA_BEGIN_KEY = "BEGIN";
	const std::string DATA_END_KEY = "END";
	const std::string WORLD_INDEX_KEY = "WorldIndex";
	const std::string PLAYER_DATA_KEY = "PlayerData";
	const std::string ENEMY_DATA_KEY = "AIData";
	const std::string DAMAGE_SCORE_KEY = "DamageScore";
}

class CBattle_UnitSystem;
class CBattle_ResultSystem
{
private:
	CBattle_UnitSystem* m_pBattleUnitSystem;
public:
	void setMemoryLinkBattleUnitSystem(CBattle_UnitSystem* pBattleUnitSystem)
	{
		m_pBattleUnitSystem = pBattleUnitSystem;
	}
private: // For Load - Battle Result Data Variables
	std::string m_strWorldIndex;
	std::vector<std::string> m_vPlayerShips;
	std::vector<std::string> m_vComputerShips;

	int m_fPlayerScore;
	int m_fComputerScore;
private:
	void recogWorldIndex(std::string strWorldIndex);
	void recogPlayerShipData(std::vector<std::string> vArray);
	void recegComputerShipData(std::vector<std::string> vArray);

public:
	CBattle_ResultSystem();
	~CBattle_ResultSystem();

	void saveBattleResult();
	void loadBattleResult();

	std::string getResultWorldIndex() const
	{
		return m_strWorldIndex;
	}
	std::vector<std::string> getResultPlayerShips() const
	{
		return m_vPlayerShips;
	}
	std::vector<std::string> getResultComputerShips() const
	{
		return m_vComputerShips;
	}
	int getResultPlayerScore() const
	{
		return m_fPlayerScore;
	}
	int getResultComputerScore() const
	{
		return m_fComputerScore;
	}
};

#endif // !_BATTLE_RESULT_SYSTEM_H#