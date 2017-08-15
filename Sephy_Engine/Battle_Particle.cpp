#include "stdafx.h"
#include "Battle_Particle.h"


CBattle_Particle::CBattle_Particle()
{
	m_bUsing			= false;
	m_nMaxFrame			= -1;
	m_nCurrentFrame		= -1;
	m_x = m_y			= 0;
	m_animeTime			= 0.f;
	m_pParticle			= nullptr;
	m_enParticleType	= PARTICLE_TYPE::PARTICLE_TYPE_NONE;
}


CBattle_Particle::~CBattle_Particle()
{
}
