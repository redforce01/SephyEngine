#ifndef _COMPONENTBASE_H
#define _COMPONENTBASE_H
#define WIN32_LEAN_AND_MEAN

class ComponentBase;

#include "gocMessage.h"

class GameObject;
class ComponentBase
{
protected:
	GameObject* mOwnerGO;
	bool mComponentSwitch;

public:
	typedef std::string goc_id_type;

	ComponentBase() : mOwnerGO(NULL), mComponentSwitch(true) {}
	virtual ~ComponentBase() {}

	virtual const goc_id_type& componentID() const = 0;
	virtual const goc_id_type& familyID() const = 0;

	void setOwnerGO(GameObject* go) { mOwnerGO = go; }
	GameObject* getOwnerGO() const { return mOwnerGO; }

	virtual void start();
	virtual void update(float frameTime);
	virtual void render();
	virtual void ai();
	virtual void collision();
	virtual void communicate();

	virtual void HandleMessage(GOCMessage message) = 0;

	void setSwapSwitch() { mComponentSwitch = !mComponentSwitch; }
};

#endif // !_COMPONENTBASE_H
