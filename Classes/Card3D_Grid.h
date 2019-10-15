#ifndef _CARD3D_GRID_H_
#define  _CARD3D_GRID_H_
#include "cocos2d.h"
USING_NS_CC;
class Card3D_Grid :public Grid3D
{
public:
	static Card3D_Grid* create(const Size& gridSize);
	Card3D_Grid();
	~Card3D_Grid();
	
	virtual void blit();

};

#endif

