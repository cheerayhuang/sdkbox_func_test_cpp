#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "MyPluginsMgr.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    float delayTime = 2;
    /*Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(MyPluginsMgr::adcolonyFunc),
                                                      MyPluginsMgr::getInstance(),
                                                      0, 0, delayTime, false);*/
    delayTime += 2;
    Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(MyPluginsMgr::chartboostFunc),
                                                      MyPluginsMgr::getInstance(),
                                                      0, 0, delayTime, false);
    delayTime += 2;
    Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(MyPluginsMgr::vungleFunc),
                                                      MyPluginsMgr::getInstance(),
                                                      0, 0, delayTime, false);

    delayTime += 2;
    Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(MyPluginsMgr::flurryFunc),
                                                      MyPluginsMgr::getInstance(),
                                                      0, 0, delayTime, false);

    delayTime += 2;
    Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(MyPluginsMgr::googleFunc),
                                                      MyPluginsMgr::getInstance(),
                                                      0, 0, delayTime, false);

    delayTime += 2;
    Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(MyPluginsMgr::iapFunc),
                                                      MyPluginsMgr::getInstance(),
                                                      0, 0, delayTime, false);

    delayTime += 2;
    Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(MyPluginsMgr::kochavaFunc),
                                                      MyPluginsMgr::getInstance(),
                                                      0, 0, delayTime, false);

    delayTime += 2;
    Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(MyPluginsMgr::tuneFunc),
                                                      MyPluginsMgr::getInstance(),
                                                      0, 0, delayTime, false);

    delayTime += 2;
    Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(MyPluginsMgr::agecheqFunc),
                                                      MyPluginsMgr::getInstance(),
                                                      0, 0, delayTime, false);

    delayTime += 2;
    Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(MyPluginsMgr::facebookFunc),
                                                      MyPluginsMgr::getInstance(),
                                                      0, 0, delayTime, false);

    /*delayTime += 2;
    Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(MyPluginsMgr::fyberFunc),
                                                      MyPluginsMgr::getInstance(),
                                                      0, 0, delayTime, false);*/

    delayTime += 2;
    Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(MyPluginsMgr::reviewFunc),
                                                      MyPluginsMgr::getInstance(),
                                                      0, 0, delayTime, false);

    return true;
}
