#pragma once

namespace battleParticleNS
{
	//=======================================================================
	// ARMOR BREAK PARTICLE LIST
	//=======================================================================

	const std::string ARMOR_BREAK_PARTICLE_KEY_01 = "Particle_1_";
	const std::string ARMOR_BREAK_PARTICLE_KEY_02 = "Particle_2_";
	const std::string ARMOR_BREAK_PARTICLE_KEY_03 = "Particle_3_";
	const UINT ARMOR_BREAK_MAX_FRAME = 15;
	const std::string ARMOR_BREAK_SMALL_PARTICLE_KEY_01 = "ParticleS_1_";
	const std::string ARMOR_BREAK_SMALL_PARTICLE_KEY_02 = "ParticleS_2_";
	const std::string ARMOR_BREAK_SMALL_PARTICLE_KEY_03 = "ParticleS_3_";
	const std::string ARMOR_BREAK_SMALL_PARTICLE_KEY_04 = "ParticleS_4_";	
	const UINT ARMOR_BREAK_SMALL_MAX_FRAME = 8;

	//=======================================================================
	// EXPLOSION PARTICLE LIST
	//=======================================================================

	const std::string EXPLOSION_PARTICLE_KEY_01 = "he0-explode-";
	const std::string EXPLOSION_PARTICLE_KEY_02 = "he1-explode-";
	const std::string EXPLOSION_PARTICLE_KEY_03 = "he2-explode-";
	const std::string EXPLOSION_PARTICLE_KEY_04 = "he3-explode-";
	const UINT EXPLOSION_PARTICLE_MAX_FRAME = 12;

	//=======================================================================
	// SPARK PARTICLE LIST
	//=======================================================================

	const std::string SPARK_AP_PARTICLE_KEY_01 = "ap0-spark-";
	const std::string SPARK_AP_PARTICLE_KEY_02 = "ap1-spark-";
	const std::string SPARK_AP_PARTICLE_KEY_03 = "ap2-spark-";
	const std::string SPARK_AP_PARTICLE_KEY_04 = "ap3-spark-";
	const UINT SPARK_AP_PARTICLE_MAX_FRAME = 5;
	const std::string SPARK_COLLISION_KEY_01 = "Particlecolli_1_";
	const std::string SPARK_COLLISION_KEY_02 = "Particlecolli_2_";
	const UINT SPARK_COLLISION_MAX_FRAME = 5;

	//=======================================================================
	// WATER PARTICLE LIST
	//=======================================================================

	const std::string WATER_AP_IMPACT_PARTICLE_KEY_01 = "1ap-impact-";
	const std::string WATER_HE_IMPACT_PARTICLE_KEY_01 = "1he-impact-";
	const UINT WATER_AP_01_MAX_FRAME = 18;
	const UINT WATER_HE_01_MAX_FRAME = 24;
	const std::string WATER_AP_IMPACT_PARTICLE_KEY_02 = "2ap-impact-";
	const std::string WATER_HE_IMPACT_PARTICLE_KEY_02 = "2he-impact-";
	const UINT WATER_AP_02_MAX_FRAME = 20;
	const UINT WATER_HE_02_MAX_FRAME = 26;
	const std::string WATER_AP_IMPACT_PARTICLE_KEY_03 = "3ap-impact-";
	const std::string WATER_HE_IMPACT_PARTICLE_KEY_03 = "3he-impact-";
	const UINT WATER_AP_03_MAX_FRAME = 22;
	const UINT WATER_HE_03_MAX_FRAME = 30;
	const std::string WATER_AP_IMPACT_PARTICLE_KEY_04 = "4ap-impact-";
	const std::string WATER_HE_IMPACT_PARTICLE_KEY_04 = "4he-impact-";
	const UINT WATER_AP_04_MAX_FRAME = 24;
	const UINT WATER_HE_04_MAX_FRAME = 32;
	const std::string WATER_AA_IMPACT_PARTICLE_KEY_01 = "aaw-impact-";
	const std::string WATER_AA_IMPACT_PARTICLE_KEY_02 = "aaw-impact-";
	const UINT WATER_AA_MAX_FRAME = 9;
	const std::string WATER_BUBBLE_IMPACT_PARTICLE_KEY_01 = "Bubble_A_";
	const std::string WATER_BUBBLE_IMPACT_PARTICLE_KEY_02 = "Bubble_B_";
	const std::string WATER_BUBBLE_IMPACT_PARTICLE_KEY_03 = "Bubble_C_";
	const UINT WATER_BUBBLE_01_MAX_FRAME = 16;
	const UINT WATER_BUBBLE_02_MAX_FRAME = 14;
	const UINT WATER_BUBBLE_03_MAX_FRAME = 13;
}

//=======================================================================
// ENUM CLASS - PARTICLE TYPE
//  + PARTICLE_TYPE_WATER		: WATER IMPACT PARTICLE
//  + PARTICLE_TYPE_EXPLOSION	: EXPLOSION PARTICLE
//  + PARTICLE_TYPE_SPARK		: SPARK PARTICLE
//  + PARTICLE_TYPE_ARMORBREAK	: ARMOR BREAK PARTICLE
//=======================================================================
enum class PARTICLE_TYPE
{
	PARTICLE_TYPE_NONE,
	PARTICLE_TYPE_WATER, PARTICLE_TYPE_EXPLOSION, PARTICLE_TYPE_SPARK, PARTICLE_TYPE_ARMORBREAK
};

class CBattle_Particle
{
protected:
	bool			m_bUsing;
	int				m_nMaxFrame;
	int				m_nCurrentFrame;
	float			m_x, m_y;
	float			m_animeTime;
	std::string		m_strSpriteKey;
	Image*			m_pParticle;
	PARTICLE_TYPE	m_enParticleType;
public:
	CBattle_Particle();
	~CBattle_Particle();

	virtual bool initialize(Graphics* g, std::string particleKey) PURE;
	virtual void update(float frameTime) PURE;
	virtual void draw() PURE;
};

