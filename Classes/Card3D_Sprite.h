#ifndef _CARD3D_SPRITE_H_
#define  _CARD3D_SPRITE_H_
#include "cocos2d.h"
USING_NS_CC;
class Card3D_Sprite :public Sprite
{
public:
	static Card3D_Sprite* create(const std::string path);
	Card3D_Sprite();
	~Card3D_Sprite();
	virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags);
	inline	void setClockwise(bool isClockwise) { _isClockwise = isClockwise; };
private:
	bool _isClockwise;
};

#endif

