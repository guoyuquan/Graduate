#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

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
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);

    auto closeItem = static_cast<ui::Button*>(rootNode->getChildByName("Button_1"));
    closeItem->addTouchEventListener(CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    /*auto red = LayerColor::create(Color4B(255, 100, 100, 128), 800, 600);
    auto green = LayerColor::create(Color4B(100, 255, 100, 128), 400, 300);
    red->addChild(green);
    this->addChild(red);*/
    auto red = LayerColor::create(Color4B(255, 100, 100, 128), 800, 600);
    red->ignoreAnchorPointForPosition(true);
    //red->setAnchorPoint(Point(0.5, 0.5));
    red->setPosition(300, 200);
    auto green = LayerColor::create(Color4B(100, 255, 100, 128), 600, 300);
    green->ignoreAnchorPointForPosition(true);
    //green->setAnchorPoint(Point(0, 0));
    red->addChild(green);
    this->addChild(red);
    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
