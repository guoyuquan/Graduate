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
    auto _emitter = ParticleSystemQuad::createWithTotalParticles(50);
    scene->addChild(_emitter, 10);
    _emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("Close.png"));
    _emitter->setAnchorPoint(Point(0,0));
    _emitter->setDuration(ParticleSystem::DURATION_INFINITY);
    _emitter->setEmitterMode(ParticleSystem::Mode::RADIUS);
    _emitter->setStartRadius(4);
    _emitter->setStartRadiusVar(1);
    _emitter->setEndRadius(ParticleSystem::START_RADIUS_EQUAL_TO_END_RADIUS);
    _emitter->setEndRadiusVar(0);
    
    _emitter->setRotatePerSecond(100);
    _emitter->setRotatePerSecondVar(0);
    
    _emitter->setAngle(90);
    _emitter->setAngleVar(0);
    
    auto size = Director::getInstance()->getWinSize();
    _emitter->setPosVar(Point::ZERO);
    
    _emitter->setLife(0.5);
    _emitter->setLifeVar(0);
    
    _emitter->setStartSpin(0);
    _emitter->setStartSpinVar(0);
    _emitter->setEndSpin(0);
    _emitter->setEndSpinVar(0);
    
    Color4F startColor(0.0f, 0.8f, 0.9f, 1.0f);
    _emitter->setStartColor(startColor);
    
    Color4F startColorVar(0, 0, 0, 1.0f);
    _emitter->setStartColorVar(startColorVar);
    
    Color4F endColor(1.0f, 1.0f, 1.0f, 0.1f);
    _emitter->setEndColor(endColor);
    
    Color4F endColorVar(0, 0, 0, 0.1f);
    _emitter->setEndColorVar(endColorVar);
    
    _emitter->setStartSize(20);
    _emitter->setStartSizeVar(1);
    _emitter->setEndSize(0);
    
    _emitter->setEmissionRate(_emitter->getTotalParticles()/_emitter->getLife());
    
    _emitter->setBlendAdditive(false);
    
    _emitter->setPosition(Point(200, 200));
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
