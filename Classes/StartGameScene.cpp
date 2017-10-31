#include "HelloWorldScene.h"
#include "StartGameScene.h"
#include "GameOver.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"

#include<iostream>


USING_NS_CC;

Scene* StartGame::createScene()
{

    auto scene = Scene::createWithPhysics();
	
	
	/*auto hudLayer = HUDLayer::create();
	scene->addChild(hudLayer);*/
	
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto layer = StartGame::create();
	layer->setPhyWorld(scene->getPhysicsWorld());
	scene->getPhysicsWorld()->setGravity(Vec2(0, -1500));
	scene->addChild(layer);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(body);
	scene->addChild(edgeNode);

	return scene;
}


bool StartGame::init()
{

	if (Velocity == 0)
		return true;
	if (!Layer::init())
	{
		return false;
	}
	//create physics world
	/*Size visibleSize = Director::getInstance()->getVisibleSize();
	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(body);
	scene->addChild(edgeNode);*/
	//play backgroud music
	/*CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("III. Rondo (Allegro).mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("III. Rondo (Allegro).mp3", true);
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.05);*/
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("getpoint.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("changebody.mp3");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//return menu
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(StartGame::back_Callback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	//cocos2d::experimental::AudioEngineImpl::play2d("III.Rondo(Allegro).mp3", true, 20);
	size = Director::getInstance()->getWinSize();
	//move background
	backgroud1 = Sprite::create("forest.png");
	float scaleX1 = size.width / backgroud1->getContentSize().width;
	float scaleY1 = size.height / backgroud1->getContentSize().height;

	backgroud1->setScaleX(scaleX1);
	backgroud1->setScaleY(scaleY1);

	backgroud1->setAnchorPoint(Vec2(0, 0));
	backgroud1->setPosition(Vec2(0, 0));
	this->addChild(backgroud1, 0);

	backgroud2 = Sprite::create("forest.png");
    float scaleX2 = size.width / backgroud2->getContentSize().width;
	float scaleY2 = size.height / backgroud2->getContentSize().height;

	backgroud2->setScaleX(scaleX2);
	backgroud2->setScaleY(scaleY2);

	backgroud2->setAnchorPoint(Vec2(0, 0));
	backgroud2->setPosition(Vec2(size.width, 0));
	this->addChild(backgroud2, 0);
   
	//black tape
	auto bottom_tape = LayerColor::create(Color4B(0, 0, 0, 255), size.width, 100);
	auto top_tape = LayerColor::create(Color4B(0, 0, 0, 255), size.width, 100);
	bottom_tape->setPosition(Vec2(0, 0));
	top_tape->setPosition(Vec2(0, size.height-100));
	this->addChild(bottom_tape);
	this->addChild(top_tape);
	//HUD
	ScoreLabel = Label::createWithTTF("Your Score is 0", "fonts/Marker Felt.ttf", 36);
	ScoreLabel->setAnchorPoint(Vec2(0, 0));
	ScoreLabel->setPosition(Vec2(0, size.height - 50));
	this->addChild(ScoreLabel);

	auto sunpic = Sprite::create("sun.png");
	float sety = Director::getInstance()->getWinSize().height - 200;
	float setx = Director::getInstance()->getWinSize().width;
	sunpic->setScaleY(sety / sunpic->getContentSize().height / 12);
	sunpic->setScaleX(setx / sunpic->getContentSize().width / 24);
	sunpic->setPosition(Vec2(setx - 150, sety + 150));
	this->addChild(sunpic);

    SunLabel = Label::createWithTTF("X 0", "fonts/Marker Felt.ttf", 24);
	SunLabel->setPosition(Vec2(setx-100, size.height - 50));
	this->addChild(SunLabel);
   

	auto operator1 = Sprite::create("operator.png");
	auto fadein = FadeIn::create(2);
	auto fadeout = FadeOut::create(2);
	operator1->setAnchorPoint(Vec2(0, 0));
	operator1->setPosition(Vec2(500,50));
	this->addChild(operator1,4);
	operator1->runAction(Sequence::create(fadein, fadeout, fadein, fadeout, fadein, fadeout, NULL));
	//player
	player = Sprite::create("player.png");
	player->setTag(1);
	player->setAnchorPoint(Vec2(0, 0));
	player->setScaleY((sety-2) / player->getContentSize().height / 16);
	player->setScaleX((setx-2) / player->getContentSize().width / 24);
	player->setPosition(Vec2(300, sety/2+100));

	auto body = PhysicsBody::createCircle(player->getContentSize().width / 2);
	player->setPhysicsBody(body);

	this->addChild(player);
	//listener
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(StartGame::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(StartGame::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	//schedule(schedule_selector(StartGame::tick),0.1);
	schedule(schedule_selector(StartGame::moveBackgroud));
	schedule(schedule_selector(StartGame::addtimeConsumed),1);
	schedule(schedule_selector(StartGame::initObstacle),1/Velocity);
	schedule(schedule_selector(StartGame::collisionPlayerAndObstacle), 0.1);
	schedule(schedule_selector(StartGame::initSun), 12);
	
	return true;
}

void StartGame::moveBackgroud(float dt)
{
	float dif = getVelocity();
	backgroud1->setPosition(Vec2(backgroud1->getPositionX() - dif, backgroud1->getPositionY()));
	backgroud2->setPosition(Vec2(backgroud2->getPositionX() - dif, backgroud2->getPositionY()));
	if (backgroud2->getPositionX() < 0)
	  {
		  float temp = backgroud2->getPositionX() + size.width;
		  backgroud1->setPosition(temp, 0);
      }
	if (backgroud1->getPositionX() < 0)
	{
		float temp = backgroud1->getPositionX() + size.width;
		backgroud2->setPosition(temp, 0);
	}
}
void StartGame::back_Callback(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}
float StartGame::getVelocity()
{
	return Velocity;
}
void StartGame::changeVelocity(float v=2.0)
{
	Velocity = v;
}
void StartGame::initObstacle(float dt)
{   float v = getVelocity();
	auto obstacle = Sprite::create("Obstacle.png");
	obstacle->setAnchorPoint(Vec2(0, 0));
	float temp = rand()%4;
	float sety = Director::getInstance()->getWinSize().height-200;
	float setx = Director::getInstance()->getWinSize().width;
	obstacle->setScaleY(sety / obstacle->getContentSize().height/16);
	obstacle->setScaleX(setx / obstacle->getContentSize().width/24);
	obstacle->setPosition(Vec2(setx, sety/4*temp+100));
	this->addChild(obstacle);
	team.pushBack(obstacle);
	float time = setx/v/50;
	auto moveBy = MoveBy::create(time, Vec2(-setx-obstacle->getContentSize().width, 0));
	auto rm = CallFunc::create(CC_CALLBACK_0(StartGame::removeObstacle, this, obstacle));
	obstacle->runAction(Sequence::create(
		moveBy, 
		/*[](Object *o){Sprite* sprite = (Sprite*)o;sprite->removeFromParent(); },
		team.eraseObject(obstacle),*/
		rm,
	    NULL)
		);

	
}
void StartGame::collisionPlayerAndObstacle(float dt)
{
	if (isCollision)
	{
		for (auto ob : team)
			if (player->getBoundingBox().intersectsRect(ob->getBoundingBox())
				|| player->getPosition().y <= 100
				|| player->getPosition().y >= Director::getInstance()->getWinSize().height - 100
				)

			{
				CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
				CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("crash.wav");

				Scene* scene = Scene::create();
				GameOver * layer = GameOver::create();
				scene->addChild(layer);
				layer->changetimeConsumed(timeConsumed);
				layer->init();
				Director::getInstance()->replaceScene(scene);
			}
	}
}


void StartGame::initSun(float dt)
{
	sun = Sprite::create("sun.png");
	float temp = rand() % 4;
	float sety = Director::getInstance()->getWinSize().height - 200;
	float setx = Director::getInstance()->getWinSize().width;
	sun->setScaleY(sety / sun->getContentSize().height / 6);
	sun->setScaleX(setx / sun->getContentSize().width / 12);
	sun->setAnchorPoint(Vec2(0, 0));
	sun->setPosition(Vec2(1200, (Director::getInstance()->getWinSize().height - 200) / 4*(rand() % 4)+100));
	this->addChild(sun);
    moveby = MoveBy::create(6, Vec2(-1200,0));
	auto hide = Hide::create();
	auto show = Show::create();
	auto rm = CallFunc::create(CC_CALLBACK_0(StartGame::removeSun, this, sun));
	sun->runAction(Sequence::create(show, moveby, rm, NULL));
	
	schedule(schedule_selector(StartGame::collisionPlayerAndSun), 0.1);
}

void StartGame::collisionPlayerAndSun(float dt)
{
	if (sun)
	{
	if (player->getBoundingBox().intersectsRect(sun->getBoundingBox()))
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("getpoint.mp3");
		removeSun(sun);
		//sun->runAction(Sequence::create(Hide::create(),Place::create(Vec2(Director::getInstance()->getWinSize().height + 20, Director::getInstance()->getWinSize().height / 2))));
		sunNum++;
		if (sunNum == 3)
		{
			sunNum = 0;
			isCollision = false;
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("changebody.mp3");
			auto blink = Blink::create(6, 10);
			player->runAction(blink);
			scheduleOnce(schedule_selector(StartGame::ChangeisCollision), 6);
		}
		
			__String *str = __String::createWithFormat("X %d", sunNum);
			SunLabel->setString(str->getCString());
		
	}
	}

}

void StartGame::ChangeisCollision(float dt)
{
	isCollision = true;
}

int StartGame::gettimeConsumed()
{
	return timeConsumed;
}

void StartGame::removeObstacle(Sprite* s)
{
	s->removeFromParentAndCleanup(true);
	team.eraseObject(s);
}
void StartGame::removeSun(Sprite* s)
{
	s->removeFromParentAndCleanup(true);
	sun = nullptr;
}
void StartGame::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event)
{
	//player->runAction(Action::stop());
	/*auto moveto1 = MoveTo::create(4, Vec2(300, Director::getInstance()->getWinSize().height-100));
	auto ease1 = EaseSineIn::create(moveto1);
	auto moveto2 = MoveTo::create(4, Vec2(300, 100));
	auto ease2 = EaseSineIn::create(moveto2);*/
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_SPACE:
		//player->runAction(moveto1);
		player->getPhysicsBody()->setVelocity(Vec2(0, getVelocity()*120));
		break;
	/*case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		player->runAction(moveto2);
		break;*/
	default:
		break;
	}
}

void StartGame::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
	/*auto moveto = MoveTo::create(3, Vec2(player->getContentSize().width, 100));
	auto ease = EaseExponentialIn::create(moveto);
	player->runAction(moveto);*/

}
void StartGame::addtimeConsumed(float dt)
{
	
	timeConsumed += 1;
	__String *str = __String::createWithFormat("Your Score is %d", gettimeConsumed());
	ScoreLabel->setString(str->getCString());
}