#include "stdafx.h"
#include "gameObject.h"
#include "componentBase.h"

GameObject::GameObject(const go_id_type &id)
{
	m_Id = id;
}

ComponentBase * GameObject::getGOC(const go_id_type & familyId)
{
	for (auto iter : m_Components)
	{
		if (iter.first.compare(familyId) == 0)
			return iter.second;
	}

	return nullptr;
}

ComponentBase * GameObject::setGOC(ComponentBase * newGOC)
{
	for (auto iter : m_Components)
	{
		if (iter.first.compare(newGOC->componentID()) == 0)
			return iter.second;
	}

	m_Components.emplace(newGOC->componentID(), newGOC);

	return m_Components.find(newGOC->componentID())->second;
}

void GameObject::clearGOCs()
{
	m_Components.clear();
}

void GameObject::HandleMessage(GOCMessage message)
{
	for (auto iter : m_Components)
	{
		iter.second->HandleMessage(message);
	}
}
