#pragma once

namespace battleParticleNS
{
	//=======================================================================
	const std::string ARMOR_BREAK_PARTICLE_KEY_01 = "Particle_1_";
	const std::string ARMOR_BREAK_PARTICLE_KEY_02 = "Particle_2_";
	const std::string ARMOR_BREAK_PARTICLE_KEY_03 = "Particle_3_";
	const std::string ARMOR_BREAK_SMALL_PARTICLE_KEY_01 = "ParticleS_1_";
	const std::string ARMOR_BREAK_SMALL_PARTICLE_KEY_02 = "ParticleS_2_";
	const std::string ARMOR_BREAK_SMALL_PARTICLE_KEY_03 = "ParticleS_3_";
	const std::string ARMOR_BREAK_SMALL_PARTICLE_KEY_04 = "ParticleS_4_";	
	const UINT ARMOR_BREAK_MAX_FRAME = 15;
	const UINT ARMOR_BREAK_SMALL_MAX_FRAME = 8;
	//=======================================================================
	const std::string EXPLOSION_PARTICLE_KEY_01 = "";

}

enum class PARTICLE_TYPE
{
	PARTICLE_TYPE_WATER, PARTICLE_TYPE_EXPLOSION, PARTICLE_TYPE_SPARK, PARTICLE_TYPE_ARMORBREAK
};

class CBattle_Particle
{
public:
	CBattle_Particle();
	~CBattle_Particle();
};

