#include "HelloWorldScene.h"
#include "StartGameScene.h"
#include "SetOptionScene.h"
#include "AboutScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
   
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
 
    // super init first
    if ( !Layer::init() )
    {
        return false;
    }
	//play backgroud music
	/*CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("III. Rondo (Allegro).mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("III. Rondo (Allegro).mp3", true);
	*/
	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //  exit

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    //  menu label
    auto label = Label::createWithTTF("Menu", "fonts/Marker Felt.ttf", 36);
  
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/2+100));

    this->addChild(label, 1);

  
    //backgroud picture
	auto bg_sprite = Sprite::create("treehouse.jpg");
	auto size = Director::getInstance()->getWinSize();
    bg_sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bg_sprite, 0);

	float scaleX = size.width / bg_sprite->getContentSize().width;
	float scaleY = size.height / bg_sprite->getContentSize().height;

	bg_sprite->setScaleX(scaleX);
	bg_sprite->setScaleY(scaleY);


	//the menu

	auto start = Label::createWithTTF("Start Game", "fonts/Marker Felt.ttf", 24);
	auto item1 = MenuItemLabel::create(start,CC_CALLBACK_1(HelloWorld::start_Callback,this));
	auto set = Label::createWithTTF("Set Option", "fonts/Marker Felt.ttf", 24);
	auto item2 = MenuItemLabel::create(set, CC_CALLBACK_1(HelloWorld::set_Callback, this));
	auto about = Label::createWithTTF("About", "fonts/Marker Felt.ttf", 24);
	auto item3 = MenuItemLabel::create(about, CC_CALLBACK_1(HelloWorld::about_Callback, this));
	auto menu_choice = Menu::create(item1,item2,item3, NULL);
	menu_choice->alignItemsVerticallyWithPadding(20);
	this->addChild(menu_choice);
    return true;
}
void HelloWorld::start_Callback(Ref* pSender)
{
	auto scene = Scene::createWithPhysics();
	//Scene* scene = Scene::create();
	StartGame *layer = StartGame::create();
	layer->changeVelocity(HelloWorld::getVelocity());
	layer->setPhyWorld(scene->getPhysicsWorld());
	scene->getPhysicsWorld()->setGravity(Vec2(0, -getVelocity()*500));
	scene->addChild(layer);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(body);
	scene->addChild(edgeNode);

	layer->init();
	Director::getInstance()->replaceScene(TransitionPageTurn::create(1, scene, true));
}

void HelloWorld::set_Callback(Ref* pSender)
{
	auto scene = Setoption::createScene();
	Director::getInstance()->replaceScene(TransitionPageTurn::create(1, scene, true));
}

void HelloWorld::about_Callback(Ref* pSender)
{
	auto scene = About::createScene();
	Director::getInstance()->replaceScene(TransitionPageTurn::create(1, scene, true));
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

float HelloWorld::getVelocity()
{
	return Velocity;
}
void HelloWorld::changeVelocity(float v = 2.0)
{
	Velocity = v;
}