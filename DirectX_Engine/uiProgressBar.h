#ifndef _UIPROGRESSBAR_H
#define _UIPROGRESSBAR_H
#define WIN32_LEAN_AND_MEAN

class UIProgressBar;

#include "uiParent.h"

enum class UIPROGRESSBAR_TYPE
{
	UIPROGRESSBAR_DEFAULT,
	UIPROGRESSBAR_RECT,
	UIPROGRESSBAR_CIRCLE,
	UIPROGRESSBAR_CUSTOM
};

class UIProgressBar : public UIParent
{
private:
	float	barMaxGauge;
	float	barCurrentGauge;
	bool	bHasBack;

	TextureManager* barTexture;		// ProgressBar Bar Texture
	TextureManager* backTexture;	// ProgressBar Back Texture
	Image	bar;
	Image	background;
	
	UIPROGRESSBAR_TYPE barType;

public:
	UIProgressBar();
	~UIProgressBar();

	bool initialize(
		UIPROGRESSBAR_TYPE type,
		const char * textureName,
		bool ninePatch, COLOR_ARGB color,
		float maxGauge, float currentGauge,
		float startX, float startY, float width, float height
	);

	bool initialize(
		UIPROGRESSBAR_TYPE type,
		const char * textureName, const char * backTextureName,
		bool ninePatch, COLOR_ARGB color,
		float maxGauge, float currentGauge,
		float startX, float startY, float width, float height
	);

	void update(float frameTime) override;
	void render() override;

	void release() override;
	void releaseAll() override;
	void resetAll() override;

	void setGauge(float currentGauge);
};

#endif // !_UIPROGRESSBAR_H
