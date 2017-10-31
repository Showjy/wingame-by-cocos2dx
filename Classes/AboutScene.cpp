#include "HelloWorldScene.h"
#include "AboutScene.h"

USING_NS_CC;

Scene* About::createScene()
{
	auto scene = Scene::create();
	auto layer = About::create();
	scene->addChild(layer);
	return scene;
}

bool About::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto size = Director::getInstance()->getWinSize();
	auto label = Label::createWithTTF("About", "fonts/Marker Felt.ttf", 36);
	auto label1 = Label::createWithTTF("1.Copyright @ 2015 All Rights Reserved Powered by OpenBlack Team", "fonts/Marker Felt.ttf", 24);
	auto label2 = Label::createWithTTF("2.Some pictures come from the Internet.","fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(size.width / 2, size.height - 200));
	label1->setPosition(Vec2(size.width / 2, size.height - 300));
	label2->setPosition(Vec2(size.width / 2, size.height - 350));
	this->addChild(label);
	this->addChild(label1);
	this->addChild(label2);


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//return menu
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(About::back_Callback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	
	return true;
}
void About::back_Callback(cocos2d::Ref* pSender)
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}