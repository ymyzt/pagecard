#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
typedef struct {
	float Position[3];
	float Color[4];
} Vertex;
struct Line
{
	float A;
	float B;
	float C;
};
class HelloWorld : public cocos2d::Layer
{
	
public:
	
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	void updateUniform();
private:
	Vec2 beganPos = Vec2::ZERO;
	GLProgramState * glstate;
	float offx;
	Vec2 getPoint(float x, float y,Line line);
};

#endif // __HELLOWORLD_SCENE_H__
