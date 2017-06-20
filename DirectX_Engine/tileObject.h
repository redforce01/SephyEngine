#ifndef _TILEOBJECT_H
#define _TILEOBJECT_H

class TileObject;

#include "image.h"

namespace TileNS
{
	const UINT TYPE_NONE = 0x00000000;
	const UINT TYPE_A = 0x00000001;
	const UINT TYPE_B = 0x00000010;
	const UINT TYPE_C = 0x00000100;
	const UINT TYPE_D = 0x00001000;
	const UINT TYPE_E = 0x00010000;
	const UINT TYPE_F = 0x00100000;
	const UINT TYPE_G = 0x01000000;
	const UINT TYPE_H = 0x10000000;
}

enum class TILEFEATURE : UINT
{
	SQUARE,
	ISOMETRIC,
	CIRCLE
};

class TileObject : public Image
{
private:
	UINT number;
	UINT type;
	TILEFEATURE feature;

	
public:
	TileObject();
	~TileObject();

	bool initialize(UINT PID, int startX, int startY,
		Graphics* g, int width, int height, int nCols, TextureManager* texture);
	void update(float frameTime);
	void render();

	// Draw This Tile Object's Border
	// ( Square / Isometric / Circle )
	void renderSketch();

	void setFeature(TILEFEATURE f) { feature = f; }
	TILEFEATURE getFeature() { return feature; }
};

#endif // !_TILEOBJECT_H