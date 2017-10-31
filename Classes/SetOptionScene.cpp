#include "HelloWorldScene.h"
#include "SetOptionScene.h"

USING_NS_CC;

Scene* Setoption::createScene()
{
	auto scene = Scene::create();
	auto layer = Setoption::create();
	scene->addChild(layer);
	return scene;
}
bool Setoption::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//return menu
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(Setoption::back_Callback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	auto size = Director::getInstance()->getWinSize();
	auto label = Label::createWithTTF("Velocity", "fonts/Marker Felt.ttf", 36);

	auto label1 = Label::createWithTTF("Easy", "fonts/Marker Felt.ttf", 24);
	auto label2 = Label::createWithTTF("Hard", "fonts/Marker Felt.ttf", 24);

	label->setPosition(Vec2(size.width / 2, size.height - 200));
	
	auto item1 = MenuItemLabel::create(label1,CC_CALLBACK_1(Setoption::class1,this));
	auto item2 = MenuItemLabel::create(label2,CC_CALLBACK_1(Setoption::class2,this));

	auto menu1 = Menu::create(item1, item2, NULL);
	menu1->alignItemsHorizontallyWithPadding(50);

	this->addChild(label);
	this->addChild(menu1);

	return true;
}
void Setoption::back_Callback(Ref* pSender)
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}
void Setoption::class1(Ref* pSender)
{
	Scene* scene = Scene::create();
	HelloWorld *layer = HelloWorld::create();
	layer->changeVelocity(2.0);
	scene->addChild(layer);
	Director::getInstance()->replaceScene(TransitionPageTurn::create(1, scene, true));
}
void Setoption::class2(Ref* pSender)
{
	Scene* scene = Scene::create();
	HelloWorld *layer = HelloWorld::create();
	layer->changeVelocity(4.0);
	scene->addChild(layer);
	Director::getInstance()->replaceScene(TransitionPageTurn::create(1, scene, true));
}