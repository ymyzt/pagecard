#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Card3D.h"
USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
	//scene->setPosition(70, 70);
    // 'layer' is an autorelease object
   auto layer = HelloWorld::create();
	//layer->setPosition(480, 320);
    //add layer as a child to scene
    scene->addChild(layer);
	auto card3d = Card3D::create("res/pkbg.png", "res/pk1.png",Size(50,50));
	layer->addChild(card3d);
	card3d->setPosition(480, 320);
	card3d->initSize();


	//card3d->init2("res/pkbg.png", "res/pk1.png");
	// return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
       return false;
    }
 	auto rootNode = CSLoader::createNode("scene/MainScene.csb");
	addChild(rootNode);
	

	//auto sp = rootNode->getChildByName("pkbg");
	//auto ss = rootNode->getPosition();
	//auto s = rootNode->convertToWorldSpace(Vec2(0, 0));
	//auto sss = rootNode->convertToWorldSpaceAR(Vec2(0, 0));
	//log("ss2:%f, %f", ss.x, ss.y);
	//log("s2:%f, %f", s.x, s.y);
	//log("sss2:%f, %f", sss.x, sss.y);
	//Size winsize = Director::getInstance()->getWinSize();
	//Sprite *sp = Sprite::create("res/pkbg.png");
	//addChild(sp);
	//auto card3d = Card3D::create("res/pkbg.png", "res/pk1.png");
	//addChild(card3d);

	//card3d->addChild(rootNode);
// 	auto ss3 = sp->getPosition();
// 	auto s3 = sp->convertToWorldSpace(Vec2(0, 0));
// 	auto sss3 = sp->convertToWorldSpaceAR(Vec2(0, 0));
// 	log("ss23:%f, %f", ss3.x, ss3.y);
// 	log("s23:%f, %f", s3.x, s3.y);
// 	log("sss23:%f, %f", sss3.x, sss3.y);

	//card3d->setPosition(winsize.width/2, winsize.height/2);

	auto listener1 = EventListenerTouchOneByOne::create();
	// trigger when you push down
	listener1->onTouchBegan = [=](Touch* touch, Event* event){
	
		return true; // if you are consuming it
	};
	// trigger when moving touch
	listener1->onTouchMoved = [=](Touch* touch, Event* event){
		// your code
		/*auto pos = touch->getLocation();
		Size size = pkbg->getContentSize();
		Vec2 position = pkbg->getPosition();
		CCLOG("position x:%f,y:%f", position.x, position.y);
		if (beganPos.x != 0){
			offx = ((pos.x - beganPos.x) / 960 -0.5 )* size.width + position.x;
			updateUniform();
		}*/
		//CCLOG("onTouchMoved x:%f,y:%f", pos.x, pos.y);
	};
	// trigger when you let up
	listener1->onTouchEnded = [=](Touch* touch, Event* event){
		// your code
		//auto pos = touch->getLocation();
		//beganPos = Vec2::ZERO;
		//CCLOG("onTouchEnded x:%f,y:%f", pos.x, pos.y);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

	
  
    return true;
}
void HelloWorld::updateUniform(){
	//GLint localx = glstate->getGLProgram()->getUniformLocation("x");
	glstate->setUniformFloat("x",offx);
	CCLOG("x::::%f", offx);
	//glstate->setUniformTexture("CC_Texture1", tx.getName());
	//glstate->setUniformTexture("CC_Texture1", tx.getName());
	//gl->setUniformLocationWith1f(localx, offx);
}
Vec2 HelloWorld::getPoint(float x, float y,Line line) {
	float A = line.A;
	float B = line.B;
	float C = line.C;
	auto f = [=](float xx, float yy) {
		return	A*xx + B*yy + C;
	};
	float x1 = x - 2 * A*f(x, y)*(A*A + B * B);
	float y1 = x - 2 * B*f(x, y)*(A*A + B * B);
	return Vec2(x1, y1);
}
