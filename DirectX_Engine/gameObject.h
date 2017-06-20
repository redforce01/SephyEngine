#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H
#define WIN32_LEAN_AND_MEAN

class GameObject;

#include <map>
#include "entity.h"
#include "gocMessage.h"

typedef std::string go_id_type;

// GO : Game Object
// GOC : Game Object Component

class ComponentBase;
class GameObject : public Entity
{
private:
	typedef std::map<const go_id_type, ComponentBase*> component_table_t;

private:
	go_id_type m_Id;
	component_table_t m_Components;

public:
	GameObject( const go_id_type &id );

	const go_id_type& getID() const { return m_Id; }
	void setID(const go_id_type& id) { m_Id = id; }

	ComponentBase* getGOC(const go_id_type& familyId);
	ComponentBase* setGOC(ComponentBase* newGOC);
	void clearGOCs();

public:

	void HandleMessage(GOCMessage message);
};

#endif // !_GAMEOBJECT_H