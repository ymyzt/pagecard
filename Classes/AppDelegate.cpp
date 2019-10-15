#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("HelloCpp", Rect(0, 0, 960, 640));
        director->setOpenGLView(glview);
    }

    director->getOpenGLView()->setDesignResolutionSize(960, 640, ResolutionPolicy::SHOW_ALL);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    FileUtils::getInstance()->addSearchPath("res");

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();
// 	Sprite *sp = Sprite::create("res/pkbg.png");
// 	scene->addChild(sp);
// 	auto ss3 = sp->getPosition();
// 	auto s3 = sp->convertToWorldSpace(Vec2(0, 0));
// 	auto sss3 = sp->convertToWorldSpaceAR(Vec2(0, 0));
// 	log("ss23:%f, %f", ss3.x, ss3.y);
// 	log("s23:%f, %f", s3.x, s3.y);
// 	log("sss23:%f, %f", sss3.x, sss3.y);
	
	//Sprite *sp = Sprite::create("res/pkbg.png");

	//scene->addChild(sp);
	//auto size = sp->getContentSize();

	//auto ss3 = sp->getPosition();
	//auto s3 = sp->convertToWorldSpace(Vec2(0, 0));
	//auto sss3 = sp->convertToWorldSpaceAR(Vec2(0, 0));
	//log("ss23:%f, %f", ss3.x, ss3.y);
	//log("s23:%f, %f", s3.x, s3.y);
	//log("sss23:%f, %f", sss3.x, sss3.y);




	//auto size2 = Director::getInstance()->getWinSizeInPixels();
	//scene->setPosition(480, 320);
    // run
	log("sssssss==%f",director->getContentScaleFactor());
    director->runWithScene(scene);
// 	auto ss  = scene->getPosition();
// 	auto s = scene->convertToWorldSpace(Vec2(0, 0));
// 	log("ss:%f, %f", ss.x, ss.y);
// 	log("s:%f, %f", s.x, s.y);
	//log("s:%f, %f", size.width, size.height);
// 	log("s:%f, %f", size2.width, size2.height);
	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
