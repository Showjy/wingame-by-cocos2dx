#include "HelloWorldScene.h"
#include "GameOver.h"

USING_NS_CC;

Scene* GameOver::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOver::create();
	scene->addChild(layer);
	return scene;
}

bool GameOver::init()
{
	if (timeConsumed == 0)
		return true;
	if (!Layer::init())
	{
		return false;
	}
	auto size = Director::getInstance()->getWinSize();
	auto label = Label::createWithTTF("Game Over", "fonts/Marker Felt.ttf", 36);
	auto label1 = Label::createWithTTF("","fonts/Marker Felt.ttf", 36);
	__String *str = __String::createWithFormat("Your Score is %d", timeConsumed);
	label1->setString(str->getCString());
	label->setPosition(Vec2(size.width / 2, size.height - 200));
	label1->setPosition(Vec2(size.width / 2, size.height - 300));
	this->addChild(label);
	this->addChild(label1);



	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//return menu
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameOver::back_Callback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	
	return true;
}
void GameOver::back_Callback(cocos2d::Ref* pSender)
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}
void GameOver::changetimeConsumed(int time)
{
	timeConsumed = time;
}